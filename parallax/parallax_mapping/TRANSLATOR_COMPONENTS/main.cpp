
//Author: Damiano Vitulli <info@spacesimulator.net>////__>>>output texture, normal and vertex arrays added by Marc C. Dion, Cornwall, Ont(thank you for the cool tool Damiano)

#ifdef __WIN32__
#include <windows.h>
#endif

#include "glut.h"
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"

#include "fstream.h"
int screen_width=640;
int screen_height=480;

double rotation_x=0, rotation_x_increment=0.1;
double rotation_y=0, rotation_y_increment=0.05;
double rotation_z=0, rotation_z_increment=0.03;
 
int filling=1; //0=OFF 1=ON

GLfloat light_ambient[]= { 0.1f, 0.1f, 0.1f, 0.1f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 100.0f, 0.0f, -10.0f, 1.0f };

GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_diffuse[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_shininess[]= { 1.0f };

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Clear background color to black
    glViewport(0,0,screen_width,screen_height);  

    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f); // We define the "viewing volume"
   
	glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

    glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_specular);
    glMaterialfv (GL_FRONT, GL_POSITION, mat_shininess);    

	glShadeModel(GL_SMOOTH); // Type of shading for the polygons
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Texture mapping perspective correction (OpenGL... thank you so much!)
    glEnable(GL_TEXTURE_2D); // Texture mapping ON
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
	glEnable(GL_CULL_FACE); // Enable the back face culling
    glEnable(GL_DEPTH_TEST); // Enable the depth test (also called z buffer)

	ObjLoad ("longHorns_3.3ds","skull.bmp");
}
void display(void)
{
    glDisable(GL_LIGHTING);
    ofstream outTexture("longHorns_3_TEX.cpp");
    ofstream outNormal("longHorns_3_NORM.cpp");
    ofstream outVertices("longHorns_3_VERT.cpp");
    int j;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity
    glTranslatef(0.0,0.0,-5); // We move the object forward (the model matrix is multiplied by the translation matrix)
    rotation_x = rotation_x + rotation_x_increment;
    rotation_y = rotation_y + rotation_y_increment;
    rotation_z = rotation_z + rotation_z_increment;
    if (rotation_x > 359) rotation_x = 0;
    if (rotation_y > 359) rotation_y = 0;
    if (rotation_z > 359) rotation_z = 0;
    glRotatef(rotation_x,1.0,0.0,0.0); // Rotations of the object (the model matrix is multiplied by the rotation matrices)
    glRotatef(rotation_y,0.0,1.0,0.0);
    glRotatef(rotation_z,0.0,0.0,1.0);
    if (object.id_texture!=-1) 
	{
		glBindTexture(GL_TEXTURE_2D, object.id_texture); // We set the active texture 
	    glEnable(GL_TEXTURE_2D); // Texture mapping ON
	}
	else
	    glDisable(GL_TEXTURE_2D); // Texture mapping OFF

outTexture  << "Texture longHorns_3_TEX[]   = \n" << "{\n"    << "     //number of vertices = " << object.polygons_qty*3 << "\n\n";
outNormal   << "Normals longHorns_3_NORM[]     = \n" << "{\n"    << "     //number of vertices = " << object.polygons_qty*3 << "\n\n";	
outVertices << "Vertices longHorns_3_VERT[] = \n" << "{\n"    << "     //number of vertices = " << object.polygons_qty*3 << "\n\n";
    
    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
	for (j=0;j<object.polygons_qty;j++)
	{
		glTexCoord2f( object.mapcoord[ object.polygon[j].a ].u,
					  object.mapcoord[ object.polygon[j].a ].v);
 outTexture << "" << object.mapcoord[ object.polygon[j].a ].u << ", ";
  outTexture << object.mapcoord[ object.polygon[j].a ].v << ",\n";
        glNormal3f( object.normal[ object.polygon[j].a ].x,
					object.normal[ object.polygon[j].a ].y,
					object.normal[ object.polygon[j].a ].z);
  outNormal << "" << object.normal[ object.polygon[j].a ].x << ", ";
  outNormal << object.normal[ object.polygon[j].a ].y << ", ";
  outNormal << object.normal[ object.polygon[j].a ].z <<  ",\n";
		
		glVertex3f( object.vertex[ object.polygon[j].a ].x,
					object.vertex[ object.polygon[j].a ].y,
					object.vertex[ object.polygon[j].a ].z);

  outVertices << "" << object.vertex[ object.polygon[j].a ].x << ", ";
  outVertices << object.vertex[ object.polygon[j].a ].y << ", ";
  outVertices << object.vertex[ object.polygon[j].a ].z << ",\n";
	
    glTexCoord2f( object.mapcoord[ object.polygon[j].b ].u,
					  object.mapcoord[ object.polygon[j].b ].v);
					  
  outTexture << "" << object.mapcoord[ object.polygon[j].b ].u << ", ";
  outTexture << object.mapcoord[ object.polygon[j].b ].v << ",\n";
        
        //Normal coordinates of the second vertex
		glNormal3f( object.normal[ object.polygon[j].b ].x,
					object.normal[ object.polygon[j].b ].y,
					object.normal[ object.polygon[j].b ].z);

  outNormal << "" << object.normal[ object.polygon[j].b ].x << ", ";
  outNormal << object.normal[ object.polygon[j].b ].y << ", ";
  outNormal << object.normal[ object.polygon[j].b ].z << ",\n";					

		// Coordinates of the second vertex
		glVertex3f( object.vertex[ object.polygon[j].b ].x,
					object.vertex[ object.polygon[j].b ].y,
					object.vertex[ object.polygon[j].b ].z);
					
  outVertices << "" << object.vertex[ object.polygon[j].b ].x << ", ";
  outVertices << object.vertex[ object.polygon[j].b ].y << ", ";
  outVertices << object.vertex[ object.polygon[j].b ].z << ",\n";					
        
		//----------------- THIRD VERTEX -----------------
		// Texture coordinates of the third vertex
		glTexCoord2f( object.mapcoord[ object.polygon[j].c ].u,
					  object.mapcoord[ object.polygon[j].c ].v);
					  
  outTexture << "" << object.mapcoord[ object.polygon[j].c ].u << ", ";
  outTexture << object.mapcoord[ object.polygon[j].c ].v << ",\n\n";
    	
        //Normal coordinates of the third vertex
		glNormal3f( object.normal[ object.polygon[j].c ].x,
					object.normal[ object.polygon[j].c ].y,
					object.normal[ object.polygon[j].c ].z);
  
  outNormal << "" << object.normal[ object.polygon[j].c ].x << ", ";
  outNormal << object.normal[ object.polygon[j].c ].y << ", ";
  outNormal << object.normal[ object.polygon[j].c ].z << ",\n\n";

		// Coordinates of the Third vertex
		glVertex3f( object.vertex[ object.polygon[j].c ].x,
					object.vertex[ object.polygon[j].c ].y,
					object.vertex[ object.polygon[j].c ].z);
					
  outVertices << "" << object.vertex[ object.polygon[j].c ].x << ", ";
  outVertices << object.vertex[ object.polygon[j].c ].y << ", ";
  outVertices << object.vertex[ object.polygon[j].c ].z << ",\n\n";
  					
	}
outTexture << "};\n";
outNormal << "};\n";
outVertices << "};\n";	
	glEnd();
    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}
void resize (int p_width, int p_height)
{
	if (screen_width==0 && screen_height==0) exit(0);
    screen_width=p_width; // We obtain the new screen width values and store it
    screen_height=p_height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,0.1f,100.0f);
glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}

void keyboard(unsigned char p_key, int p_x, int p_y)
{  
    switch (p_key)
    {
        case ' ':
            rotation_x_increment=0;
            rotation_y_increment=0;
            rotation_z_increment=0;
        break;
		case 'r': case 'R':
            if (filling==0)
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
                filling=1;
            }   
            else 
            {
                glPolygonMode (GL_FRONT_AND_BACK, GL_LINE); // Polygon rasterization mode (polygon outlined)
                filling=0;
            }
        break;
		case 27:
			exit(0);
		break;
    }
}
void keyboard_s (int p_key, int p_x, int py)
{
    switch (p_key)
    {
        case GLUT_KEY_UP:
            rotation_x_increment = rotation_x_increment +0.005;
        break;
        case GLUT_KEY_DOWN:
            rotation_x_increment = rotation_x_increment -0.005;
        break;
        case GLUT_KEY_LEFT:
            rotation_y_increment = rotation_y_increment +0.005;
        break;
        case GLUT_KEY_RIGHT:
            rotation_y_increment = rotation_y_increment -0.005;
        break;
    }
}
/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("www.spacesimulator.net - 3d engine tutorials - To exit press ESC");    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
