/*
 Jonathan Dummer ("lonesock")
 Cone Step Mapping pre-processor

 this uses the Corona image library

 This source released under the MIT license
*/

// Theirs
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>

// in-between
#include <corona.h>

// mine
// none yet

using namespace std;

// Where does each component go?
// Define offsets for Red Green Blue Alpha

//*
// Standard
#define OFF_HEIGHT 0
#define OFF_CONERATIO 1
#define OFF_NORMALX 2
#define OFF_NORMALY 3
//*/
/*
// for DXT5
#define OFF_NORMALX 0
#define OFF_CONERATIO 1
#define OFF_NORMALY 2
#define OFF_HEIGHT 3
//*/

/*
 basically, 99% of all pixels will fall in under 2.0
 (most of the time, on the heightmaps I've tested)
 the question:
  Is reduced resolution worth missing
  the speedup of the slow ones?
*/
const float max_ratio = 1.0;
/*
 do I want to sqrt my cone value (better
 spread, a bit more work in shader)?
*/
const bool sqrt_cone_ratio = true;
/*
 do I want to invert the heightmap
 (make it a depthmap)?
 It removes 1 op in the shader
*/
const bool invert_heightmap = true;
/*
 I need to have safety because of the linear
 interpolation of the Cone Ratios, inside the
 shader.  So safety values:
 1.0 = fully safe (slower)
 0.0 = possibly unsafe (faster)

 changed my mind...always safe
*/
/*
  Do I want the textures to be computed
  as tileable?  This makes the Cone Step
  Mapping safer if the texture actually
  is tiled.  Slower processing, though.
  I auto-detect these after image load.

  I'm changing my mind...ALWAYS TILE!
*/

inline int xy2index (int x, int y, const int width, const int height, const int chans)
{
    // take the info and compute the array index

    // x-tile
    while (x < 0)
        x += width;
    while (x >= width)
        x -= width;

    // y-tile
    while (y < 0)
        y += height;
    while (y >= height)
        y -= height;

    // OK, it's valid, compute it
    return ( (x + y * width) * chans );
}

int main(int argc, char *argv[])
{
    char OutName[4096];
    int FileCounter;
    long TheSize, ScanWidth;
    long width, height;
    float iwidth, iheight;
    long chans;
    corona::Image *image, *outimage;
    unsigned char *Data;
    long tin;
    int *intData;

    cout << "********** Height Map Processor **********" << endl;
    cout << "Storing the sqrt of Cone Ratio is set to " << sqrt_cone_ratio << endl;
    cout << "Cone Ratio Max is set to " << max_ratio << endl;
    cout << "Inverting the heightmap is set to " << invert_heightmap << endl;
    cout << "Map tiling is on" << endl;
    cout << "Final pass safety is on" << endl;
    cout << "******************************************" << endl;
    cout << endl;

    // Did I get a file name?
    if (argc < 2)
    {
        // Oops, no file to convert
        cout << "usage: HeightProc input_file [input_file2] ... [input_fileN]" << endl << endl;
        system ("pause");
        return (0);
    }

    for (FileCounter = 1; FileCounter < argc; ++FileCounter)
    {
        //cout << "Converting file #" << FileCounter << endl;
        // OK, open the image file
        image = corona::OpenImage (argv[FileCounter], corona::PF_R8G8B8A8);
        if (!image)
        {
            cout << "I could not open " << argv[FileCounter] << endl << endl;
            system ("pause");
            return (0);
        }

        //cout << "Loaded image : " << argv[FileCounter] << " : " << image->getDescription() << endl;

        width = image->getWidth ();
        height = image->getHeight ();
        chans = 4; // forced for now (by corona)
        ScanWidth = chans * width;
        TheSize = ScanWidth * height;
        Data = (unsigned char *)(image->getPixels());
        intData = new int [width * height];

        iheight = 1.0 / height;
        iwidth = 1.0 / width;

        cout << endl << "Image #" << (argc - FileCounter) << ":   '" << argv[FileCounter];
        cout << "'   (" << width << " x " << height << ")" << endl;
        //cout << endl << "Computing:" << endl;

        //  warning message if the texture is not square
        if (width != height)
        {
            cout << endl << "Warning: The image is not square!  Step-Map may not be optimum!" << endl;
            system ("pause");
        }

        // load the image data into BRF
        tin = clock ();

        // copy the Red value into all other slots too
        // (because I'm not sure into which slot I'll
        // assign each component.
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
            {
                unsigned char val;
                val = Data[y*ScanWidth + chans*x + 0];
                Data[y*ScanWidth + chans*x + 1] = val;
                Data[y*ScanWidth + chans*x + 2] = val;
                Data[y*ScanWidth + chans*x + 3] = val;
                intData [y*width + x] = val;
            }

        //  OK, do the processing
        cout << "Status:       ------_________";
        for (int y = 0; y < height; ++y)
        {
			printf("%c%c%c%c%c%c", 8,8,8,8,8,8);
			printf("%c%c%c%c%c%c%c%c%c", 8,8,8,8,8,8,8,8,8);

			//	print the % done
            printf("%5.2f%%", y*100.0/(height-1));
            //	print the time elapsed
            printf("  %6.0fs", 0.001*(clock() - tin));

            for (int x = 0; x < width; ++x)
            {
                float min_ratio2, actual_ratio;
                int x1, x2, y1, y2;
                //unsigned char ht;
                int ht;
                float r2, h2;

                //  set up some initial values
                // (note I'm using ratio squared throughout,
                // and taking sqrt at the end...faster)
                //ht = Data[y*ScanWidth + chans*x + OFF_HEIGHT];
                ht = intData [y*width + x];

                // ok, start with the largest area i'm willing to search
                min_ratio2 = max_ratio * max_ratio;

                // scan in outwardly expanding blocks
                // (so I can stop if I reach my minimum ratio)
                for (int rad = 1;
                        rad*rad <= (255-ht)*(255-ht)*min_ratio2*width*height/255/255;
                        ++rad)
                {
                    // do the box for this "radius"
                    // (so for each of these lines...)

                    // West and east
                    x1 = x - rad;
                    x2 = x + rad;
                    {
                        float delx = -rad*iwidth;
                        // y limits
                        // (+- 1 because I'll cover the corners in the X-run)
                        y1 = y - rad + 1;
                        y2 = y + rad - 1;

                        // and check the line
                        for (int dy = y1; dy <= y2; ++dy)
                        {
							//	west
                            int idx = xy2index (x1, dy, width, height, 1);
                            {
                                h2 = (intData[idx] - ht) / 255.0;
                                if (h2 > 0.0)
                                {
                                    float dely = (dy-y)*iheight;
                                    r2 = delx*delx + dely*dely;
                                    h2 *= h2;
                                    if (h2 * min_ratio2 > r2)
                                    {
                                        //  this is the new (lowest) value
                                        min_ratio2 = r2 / h2;
                                    }
                                }
                            }

                            //	east
                            idx = xy2index (x2, dy, width, height, 1);
                            {
                                h2 = (intData[idx] - ht) / 255.0;
                                if (h2 > 0.0)
                                {
                                    float dely = (dy-y)*iheight;
                                    r2 = delx*delx + dely*dely;
                                    h2 *= h2;
                                    if (h2 * min_ratio2 > r2)
                                    {
                                        //  this is the new (lowest) value
                                        min_ratio2 = r2 / h2;
                                    }
                                }
                            }
                        }
                    }

                    // North
                    y1 = y - rad;
                    {
                        float dely = -rad*iheight;
                        // x limits
                        x1 = x - rad;
                        x2 = x + rad;

                        // and check the line
                        for (int dx = x1; dx <= x2; ++dx)
                        {
                            int idx = xy2index (dx, y1, width, height, 1);
                            {
                                h2 = (intData[idx] - ht) / 255.0;
                                if (h2 > 0.0)
                                {
                                    float delx = (dx-x)*iwidth;
                                    r2 = delx*delx + dely*dely;
                                    h2 *= h2;
                                    if (h2 * min_ratio2 > r2)
                                    {
                                        //  this is the new (lowest) value
                                        min_ratio2 = r2 / h2;
                                    }
                                }
                            }
                        }
                    }

                    // South
                    y2 = y + rad;
                    {
                        float dely = rad*iheight;
                        // x limits
                        x1 = x - rad;
                        x2 = x + rad;

                        // and check the line
                        for (int dx = x1; dx <= x2; ++dx)
                        {
                            int idx = xy2index (dx, y2, width, height, 1);
                            {
                                h2 = (intData[idx] - ht) / 255.0;
                                if (h2 > 0.0)
                                {
                                    float delx = (dx-x)*iwidth;
                                    r2 = delx*delx + dely*dely;
                                    h2 *= h2;
                                    if (h2 * min_ratio2 > r2)
                                    {
                                        //  this is the new (lowest) value
                                        min_ratio2 = r2 / h2;
                                    }
                                }
                            }
                        }
                    }

                    // done with the expanding loop
                }

                //  actually I have the ratio squared.  Sqrt
                actual_ratio = sqrt (min_ratio2);
                // scale to 1.0
                actual_ratio /= max_ratio;
                // most of the data is on the low end...sqrting again spreads it better
                // (plus multiply is a cheap operation in shaders!)
                if (sqrt_cone_ratio)
                {
                    actual_ratio = sqrt (actual_ratio);
                }

                //  Red stays height
                //  Green becomes Step-Cone-Ratio
                Data[y*ScanWidth + chans*x + OFF_CONERATIO] = static_cast<unsigned char>(255.0 * actual_ratio);
                // but make sure it is > 0.0, since I divide by it in the shader
                if (Data[y*ScanWidth + chans*x + OFF_CONERATIO] < 1)
                    Data[y*ScanWidth + chans*x + OFF_CONERATIO] = 1;
                // Blue stays df/dx
                // Alpha stays df/dy

            } // done with the column

        } // done with the row
        cout << endl;

        delete [] intData;

        // post-calculate the derivatives
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
            {
                float der, dx, dy;

                //  the slope in x
                if (x == 0)
                {
                    der = (Data[y*ScanWidth + chans*(1) + OFF_HEIGHT] - Data[y*ScanWidth + chans*(width-1) + OFF_HEIGHT]);
                }
                else if (x == width - 1)
                {
                    der = (Data[y*ScanWidth + chans*(0) + OFF_HEIGHT] - Data[y*ScanWidth + chans*(width-2) + OFF_HEIGHT]);
                }
                else
                {
                    der = Data[y*ScanWidth + chans*(x+1) + OFF_HEIGHT] - Data[y*ScanWidth + chans*(x-1) + OFF_HEIGHT];
                }
                dx = der;


                //  the slope in y
                if (y == 0)
                {
                    der = (Data[(1)*ScanWidth + chans*x + OFF_HEIGHT] - Data[(height-1)*ScanWidth + chans*x + OFF_HEIGHT]);
                }
                else if (y == height - 1)
                {
                    der = (Data[(0)*ScanWidth + chans*x + OFF_HEIGHT] - Data[(height-2)*ScanWidth + chans*x + OFF_HEIGHT]);
                }
                else
                {
                    der = (Data[(y+1)*ScanWidth + chans*x + OFF_HEIGHT] - Data[(y-1)*ScanWidth + chans*x + OFF_HEIGHT]);
                }
                dy = der;

                // stuff them into their proper channels
                //*
                // old way
                Data[y*ScanWidth + chans*x + OFF_NORMALX] = (int)(127.5 + dx / 2.0 + 0.5);
                Data[y*ScanWidth + chans*x + OFF_NORMALY] = (int)(127.5 + dy / 2.0 + 0.5);
                //*/
                /*
                // medium way, scale derivatives between (-1, 1)
                dx /= 255.0;
                dy /= 255.0;
                // cube_root (to preserve sign)
                if (dx < 0.0)
                dx = -powf (-dx, 1.0/2.0);
                else
                dx = powf (dx, 1.0/2.0);
                if (dy < 0.0)
                dy = -powf (-dy, 1.0/2.0);
                else
                dy = powf (dy, 1.0/2.0);
                // scale back to (0,255) and save
                Data[y*ScanWidth + chans*x + OFF_NORMALX] = (int)(127.5 + 127.5 * dx + 0.5);
                Data[y*ScanWidth + chans*x + OFF_NORMALY] = (int)(127.5 + 127.5 * dy + 0.5);
                //*/
                /*
                // new way
                dx *= -width / (2.0 * 255.0);
                dy *= -height / (2.0 * 255.0);
                der = 127.0 / sqrt (1.0 + dx*dx + dy*dy);
                Data[y*ScanWidth + chans*x + OFF_NORMALX] = (int)(127.5 + dx * der + 0.5);
                Data[y*ScanWidth + chans*x + OFF_NORMALY] = (int)(127.5 + dy * der + 0.5);
                //*/
            }

        // All of the 3D rendering API's will do
        // interpolation of the cone_ratios. This
        // can be *BAD*
        cout << "Performing the safety pass!" << endl;
        unsigned char *safeCR = new unsigned char [width * height];
        // for each pixel, find the lowest nearby ConeRatio value
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
            {
                int main_idx = y*ScanWidth + chans*x;
                unsigned char LowestCR = Data[main_idx + OFF_CONERATIO];
                unsigned char TheHeight = Data[main_idx + OFF_HEIGHT];
                for (int dy = -1; dy < 2; ++dy)
                    for (int dx = -1; dx < 2; ++dx)
                    {
                        int idx = xy2index (x+dx, y+dy, width, height, chans);
                        {
                            // this is a valid comparison point
                            if ((Data[idx + OFF_HEIGHT] <= TheHeight) &&
                                    (Data[idx + OFF_CONERATIO] < LowestCR))
                            {
                                // this is the lowest CR of interest so far
                                LowestCR = Data[idx + OFF_CONERATIO];
                            }
                        }
                    }
                // OK, I have the replacement CR value, just hold on to it for a while
                safeCR[x+y*width] = LowestCR;
            }
        // now I've done all the computing, update my walues
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
            {
                Data [y*ScanWidth + chans*x + OFF_CONERATIO] = safeCR[x+y*width];
            }
        delete [] safeCR;

        // invert this (used to convert height-map to depth-map)
        cout << "Inverting Heightfield" << endl;
        if (invert_heightmap)
        {
            for (int px = 0; px < width*height; ++px)
                Data[px*chans + OFF_HEIGHT] = 255 - Data[px*chans + OFF_HEIGHT];
        }

        // end my timing after the computation phase
        tin = clock() - tin;
        cout << "Processed in " << tin * 0.001 << " seconds" << endl;

        outimage = corona::CreateImage(width, height, corona::PF_R8G8B8A8, Data);
        if (outimage != NULL)
        {
            // Redo the best, and save it
            // (only writing formats supported: PNG, TGA)
            //  ((and PNG is compressed and has alpha!!))
            tin = clock();
            // once in PNG
            strcpy (OutName, argv[FileCounter]);
            strcat (OutName, "_step.png");
            cout << "Saving: " << OutName << ", result = " <<
            corona::SaveImage (OutName, corona::FF_PNG, outimage) << endl;
            // and again in TGA
            strcpy (OutName, argv[FileCounter]);
            strcat (OutName, "_step.tga");
            cout << "Saving: " << OutName << ", result = " <<
            corona::SaveImage (OutName, corona::FF_TGA, outimage) << endl;
            // done
            tin = clock() - tin;
            delete outimage;
            //cout << "(That took " << tin * 0.001 << " seconds)" << endl;
        }
        else
        {
            cout << "Couldn't create the new image" << endl;
            system("PAUSE");
        }

        delete image;

        // Report
        cout << endl << endl;

    } // and finish all file names passed in

    // And end it
    cout << endl << "Done processing the image";
    if (argc > 2)
		cout << "s";
    cout << "." << endl;
    system("PAUSE");
    return (0);
}
