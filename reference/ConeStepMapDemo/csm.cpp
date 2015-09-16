/*
	Jonathan Dummer ("lonesock")
	Cone Step Mapping demo

	this uses the Irrlicht engine
	(0.14.0 modified with mandrav's patch)

	This source released under the MIT license
*/

/*
This tutorial shows how to use one of the built in more complex materials in irrlicht:
Per pixel lighted surfaces using normal maps and parallax mapping. It will also show
how to use fog and moving particle systems. And don't panic: You dont need any
experience with shaders to use these materials in Irrlicht.

At first, we need to include all headers and do the stuff we always do, like
in nearly all other tutorials.
*/

#include <irrlicht.h>
#include <iostream>

using namespace irr;

#pragma comment(lib, "Irrlicht.lib")

//  Global (ich) variables
IrrlichtDevice* device = 0;
s32 shaderCSMMaterialType = 0;
s32 shaderReliefMaterialType = 0;
s32 texture_size = 256;
core::stringc app_dir;
float depth = 0.05;
float csm_gain = 1.0;
float csm_offset = 0.0;
int num_steps = 20;
bool flag_refresh = true;
bool mouse_control = false;
core::array <video::E_MATERIAL_TYPE> ShaderMaterials;
core::array <core::stringc> ShaderNames;

class MyShaderCallBack : public video::IShaderConstantSetCallBack
{
public:

  virtual void OnSetConstants(video::IMaterialRendererServices* services, s32 userData)
  {
    /*
		Here's what I need to have set

		Vertex Shader:
			attribute vec3 tangent;
			attribute vec3 binormal;

		Pixel Shader:
			uniform vec4 ambient;
			uniform vec4 diffuse;
			uniform float depth;
			uniform float texsize;
			uniform int conesteps;

		Extras for the Relief Mapping Pixel Shader:
			uniform vec4 specular;
			uniform float shine;
			uniform float tile;
			uniform int linear_search_steps;
			uniform int binary_search_steps;
	*/
	f32 v[4];

	//	I got this from the Irrlicht forum: mandrav, of Code::Blocks fame!
	// set 2 texture units for ConeStepMapping
	int c[] = { 0, 2, 1 }; // sampler2d IDs
	//int c[] = { 4, 6, 5 }; // sampler2d IDs
	//	the plain base ambient texture
	services->setPixelShaderConstant("texmap", (float*)&c[0], 1);
	//	bot the relief map and step map are the same (I modified relief mapping to save space)
	services->setPixelShaderConstant("stepmap", (float*)&c[1], 1);
	services->setPixelShaderConstant("reliefmap", (float*)&c[1], 1);
	services->setPixelShaderConstant("normalmap", (float*)&c[2], 1);

	v[0] = 0.2; v[1] = 0.2; v[2] = 0.2; v[3] = 1.0;
	services->setPixelShaderConstant("ambient", v, 4);

	v[0] = 0.99; v[1] = 0.99; v[2] = 0.99; v[3] = 1.0;
	services->setPixelShaderConstant("diffuse", v, 4);

	v[0] = depth; v[1] = 0.0; v[2] = 0.0; v[3] = 0.0;
	services->setPixelShaderConstant("depth", v, 1);

	v[0] = static_cast<float>(texture_size); v[1] = 0.0; v[2] = 0.0; v[3] = 0.0;
	services->setPixelShaderConstant("texsize", v, 1);

	//	and for my loop version, and Parallax Occlusion Mapping
	services->setPixelShaderConstant("conesteps", (float*)&num_steps, 1);

	//	and for my LOD versions
	v[0] = csm_gain; v[1] = 0.0; v[2] = 0.0; v[3] = 0.0;
	services->setPixelShaderConstant("csm_gain", v, 1);
	v[0] = csm_offset; v[1] = 0.0; v[2] = 0.0; v[3] = 0.0;
	services->setPixelShaderConstant("csm_offset", v, 1);

	//	extras for Relief Mapping
	v[0] = 0.85; v[1] = 0.85; v[2] = 0.85; v[3] = 1.0;
	services->setPixelShaderConstant("specular", v, 4);
	v[0] = 128.0; v[1] = 0.0; v[2] = 0.0; v[3] = 0.0;
	services->setPixelShaderConstant("shine", v, 1);
	v[0] = 1.0; v[1] = 0.0; v[2] = 0.0; v[3] = 0.0;
	services->setPixelShaderConstant("tile", v, 1);
	//	used in relief mapping
	services->setPixelShaderConstant("linear_search_steps", (float*)&num_steps, 1);
	int bs = 5;
	services->setPixelShaderConstant("binary_search_steps", (float*)&bs, 1);
    }
};


/*
For this example, we need an event receiver, to make it possible for the user
to switch between the three available material types. In addition, the event
receiver will create some small GUI window which displays what material is
currently being used. There is nothing special done in this class, so maybe
you want to skip reading it.
*/
class MyEventReceiver : public IEventReceiver
{
public:

	MyEventReceiver(scene::ISceneNode* room,
		gui::IGUIEnvironment* env, video::IVideoDriver* driver)
	{
		int pix_hi = 20 * ShaderNames.size();
		int pix_wide = 0;

		for (unsigned int i = 0; i < ShaderNames.size(); ++i)
		{
			if (ShaderNames[i].size() > pix_wide)
				pix_wide = ShaderNames[i].size();
		}
		pix_wide *= 10;

		// store pointer to room so we can change its drawing mode
		Room = room;
		Driver = driver;

		// set a nicer font
		gui::IGUISkin* skin = env->getSkin();
		gui::IGUIFont* font = env->getFont((app_dir + "fonthaettenschweiler.png").c_str());
		if (font)
			skin->setFont(font);

		ListBox = env->addListBox(
			core::rect<s32>(10,10,pix_wide,pix_hi));//, window);

		//	add all the shaders in my list
		for (unsigned int i = 0; i < ShaderNames.size(); ++i)
			ListBox->addItem(((core::stringw)(ShaderNames[i].c_str())).c_str());
		ListBox->setSelected(0);

		// create problem text
		ProblemText = env->addStaticText(
			L"Your hardware or this renderer is not able to use the "\
			L"needed shaders for this material. Using fall back materials.",
			core::rect<s32>(pix_wide+40,20,470,60));
		ProblemText->setOverrideColor(video::SColor(100,255,255,255));

		// create Help text
		HelpText = env->addStaticText(
			L"Demo Hot Keys:\n"\
			L" F1   -  Toggle this help screen\n"\
			L"ESC  -  Reset steps, gain, offset\n"\
			L"E,R   -  Change shader\n"\
			L"Q,W  -  Change Depth\n"\
			L"A,S   -  Change # steps\n"\
			L"*,/    -  Change csm_gain\n"\
			L"+,-    -  Change csm_offset\n"\
			L" M     -  Enable/Disable mouse input",
			core::rect<s32>(pix_wide+40,20,470,pix_hi*7));
		HelpText->setOverrideColor(video::SColor(100,255,255,255));
		HelpText->setVisible (false);

		// set the material which is selected in the listbox
		setMaterial();
	}

	bool OnEvent(SEvent event)
	{
		// check if user presses the key 'E' or 'R'
		if (event.EventType == irr::EET_KEY_INPUT_EVENT &&
			!event.KeyInput.PressedDown && Room && ListBox)
		{
			// change selected item in listbox


			int sel = ListBox->getSelected();
			if (event.KeyInput.Key == irr::KEY_F1)
			{
				HelpText->setVisible(!HelpText->isVisible());
				return false;
			}
			if (event.KeyInput.Key == irr::KEY_KEY_R)
				++sel;
			else
			if (event.KeyInput.Key == irr::KEY_KEY_E)
				--sel;
			else
			if (event.KeyInput.Key == irr::KEY_KEY_Q)
			{
				depth /= 1.5;
				if (depth < 0.005) depth = 0.005;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_KEY_W)
			{
				depth *= 1.5;
				if (depth > 0.25) depth = 0.25;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_KEY_A)
			{
				flag_refresh = true;
				num_steps -= 5;
				if (num_steps < 5) num_steps = 5;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_KEY_S)
			{
				flag_refresh = true;
				num_steps += 5;
				if (num_steps > 200) num_steps = 200;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_ADD)
			{
				flag_refresh = true;
				csm_offset += 0.1;
				if (csm_offset > 5.0) csm_offset = 5.0;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_SUBTRACT)
			{
				flag_refresh = true;
				csm_offset -= 0.1;
				if (csm_offset < 0.0) csm_offset = 0.0;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_MULTIPLY)
			{
				flag_refresh = true;
				csm_gain += 0.1;
				if (csm_gain > 5.0) csm_gain = 5.0;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_DIVIDE)
			{
				flag_refresh = true;
				csm_gain -= 0.1;
				if (csm_gain < 0.0) csm_gain = 0.0;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_ESCAPE)
			{
				//	a simple reset
				flag_refresh = true;
				csm_gain = 1.0;
				csm_offset = 0.0;
				num_steps = 20;
				return false;
			}
			else
			if (event.KeyInput.Key == irr::KEY_KEY_M)
			{
				flag_refresh = true;
				mouse_control = !mouse_control;
				//	show the mouse
				device->getCursorControl()->setVisible(mouse_control);
				//	and have the default amera ignore inputs
				device->getSceneManager()->getActiveCamera()->setInputReceiverEnabled(!mouse_control);
				return false;
			}
			else
				return false;

            //  wrap in both directions
			if (sel >= (int)ShaderMaterials.size()) sel = 0;
			if (sel < 0) sel = (int)ShaderMaterials.size()-1;

            ListBox->setSelected(sel);

			// set the material which is selected in the listbox
			setMaterial();
		}

		return false;
	}

private:

	// sets the material of the room mesh the the one set in the
	// list box.
	void setMaterial()
	{
		video::E_MATERIAL_TYPE type = video::EMT_SOLID;

		// change material setting (after a little error checking)
		if ((ListBox->getSelected() >= 0) && (ListBox->getSelected() < (int)ShaderMaterials.size()))
			type = ShaderMaterials[ListBox->getSelected()];

		Room->setMaterialType(type);

		/*
		We need to add a warning if the materials will not be able to be
		displayed 100% correctly. This is no problem, they will be renderered
		using fall back materials, but at least the user should know that
		it would look better on better hardware.
		We simply check if the material renderer is able to draw at full
		quality on the current hardware. The IMaterialRenderer::getRenderCapability()
		returns 0 if this is the case.
		*/
		video::IMaterialRenderer* renderer = Driver->getMaterialRenderer(type);

		// display some problem text when problem
		if (!renderer || renderer->getRenderCapability() != 0)
			ProblemText->setVisible(true);
		else
			ProblemText->setVisible(false);
	}

private:

	gui::IGUIStaticText* ProblemText;
	gui::IGUIStaticText* HelpText;
	gui::IGUIListBox* ListBox;

	scene::ISceneNode* Room;
	video::IVideoDriver* Driver;
};

/*
Now for the real fun. We create an Irrlicht Device and start to setup the scene.
*/
int main(int argc, char **argv)
{
	//	I may need this
	io::IFileList *fileList;
	video::E_DRIVER_TYPE driverType = video::EDT_OPENGL;

	//	set up the default images
	//*
	core::stringc base_file = "collage_base.jpg";
	core::stringc height_file = "collage_height.jpg";
	core::stringc step_file = "collage_step.png";
	//*/
	/*
	core::stringc base_file = "wall3_base.jpg";
	core::stringc height_file = "wall3_height.jpg";
	core::stringc step_file = "wall3_step.png";
	//*/


	//	create the device
	device = createDevice(driverType, core::dimension2d<s32>(640, 480));
	//device = createDevice(driverType, core::dimension2d<s32>(320,240));	//	for FRAPS
	if (device == 0)
		return 1; // could not create selected driver.
    device->setResizeAble(true);

    //	and I want extreme logging!
    device->getLogger()->setLogLevel(irr::ELL_INFORMATION);
    //device->getLogger()->setLogLevel(irr::ELL_WARNING);
    //device->getLogger()->setLogLevel(irr::ELL_ERROR);
    //device->getLogger()->setLogLevel(irr::ELL_NONE);

	//	find the apps directory
	app_dir = argv[0];
	app_dir = app_dir.subString (0, 1+app_dir.findLast ('\\'));

	//	update the files to include the directory
	base_file = app_dir + base_file;
	height_file = app_dir + height_file;
	step_file = app_dir + step_file;

    //	did the user pass me some files?
    if (argc > 1)
    {
		for (int i = 1; i < argc; ++i)
		{
			core::stringc tmps = argv[i];
			int loc = tmps.findLast ('_');
			if ((tmps[loc+1] == 'b') || (tmps[loc+1] == 'B'))
				base_file = tmps;
			if ((tmps[loc+1] == 'h') || (tmps[loc+1] == 'H'))
				height_file = tmps;
			if ((tmps[loc+1] == 's') || (tmps[loc+1] == 'S'))
				step_file = tmps;
		}
    }

	//	reset my shaders list
	ShaderMaterials.clear();
	ShaderNames.clear();
	//*
	//	and add the built-ins
	ShaderNames.push_back ("dot3");
	ShaderMaterials.push_back (video::EMT_NORMAL_MAP_SOLID);
	ShaderNames.push_back ("parallax");
	ShaderMaterials.push_back (video::EMT_PARALLAX_MAP_SOLID);
	//*/

	/*
	Before we start with the interesting stuff, we do some simple things:
	Store pointers to the most important parts of the engine (video driver,
	scene manager, gui environment) to safe us from typing too much,
	add an irrlicht engine logo to the window and a user controlled
	first person shooter style camera.
	*/

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();
	video::IGPUProgrammingServices* gpu = driver->getGPUProgrammingServices();

    /*
        Also, we let the engine now	that it should store all
        textures in 32 bit. This necessary because for parallax
        mapping, we need 32 bit textures.
    */
    driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);

	// disable mouse cursor
	device->getCursorControl()->setVisible(false);

	/*
	To be able to display something interesting, we load a mesh from a .3ds file
	which is a room I modeled with anim8or. It is the same room as
	from the specialFX example. Maybe you remember from that tutorial,
	I am no good modeler at all and so I totally messed up the texture
	mapping in this model, but we can simply repair it with the
	IMeshManipulator::makePlanarTextureMapping() method.
	*/

	device->getFileSystem()->changeWorkingDirectoryTo (app_dir.c_str());

	/*
	device->getFileSystem()->addZipFileArchive ("sample.pk3");
	scene::IAnimatedMesh* roomMesh = smgr->getMesh("maps/nemesis.bsp");
	//*/

	scene::IAnimatedMesh* roomMesh = smgr->getMesh((app_dir + "myroom.obj").c_str());

	scene::ISceneNode* room = 0;

	if (roomMesh)
	{
		//	only do this if there is no texturing already
		//*
		smgr->getMeshManipulator()->makePlanarTextureMapping(
				roomMesh->getMesh(0), 0.001f);
		//*/

		/*
		Now for the first exciting thing: If we successfully loaded the mesh
		we need to apply textures to it. Because we want this room to be
		displayed with a very cool material, we have to do a little bit more
		than just set the textures. Instead of only loading a color map as usual,
		we also load a height map which is simply a grayscale texture. From this
		height map, we create a normal map which we will set as second texture of the
		room. If you already have a normal map, you could directly set it, but I simply
		didn´t find a nice normal map for this texture.
		The normal map texture is being generated by the makeNormalMapTexture method
		of the VideoDriver. The second parameter specifies the height of the heightmap.
		If you set it to a bigger value, the map will look more rocky.
		*/

		//	load the textures I need (or the user selected
		//	(set the flags for each [new addition!])
		driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
		driver->setTextureCreationFlag(video::ETCF_USE_DXT5, true);
		driver->setTextureCreationFlag(video::ETCF_USE_2_CHANNEL, false);
		video::ITexture* colorMap = driver->getTexture(base_file.c_str());

		driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
		driver->setTextureCreationFlag(video::ETCF_USE_DXT5, false);
		driver->setTextureCreationFlag(video::ETCF_USE_2_CHANNEL, false);
		video::ITexture* normalMap = driver->getTexture(height_file.c_str());

		driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, false);
		driver->setTextureCreationFlag(video::ETCF_USE_DXT5, false);
		driver->setTextureCreationFlag(video::ETCF_USE_2_CHANNEL, false);
		video::ITexture* stepMap = driver->getTexture(step_file.c_str());

		driver->makeNormalMapTexture(normalMap, 9.0f);
		texture_size = stepMap->getSize().Width;

		//  and my shader stuff
		//	Note: GLSL seems to ignore the shader type (e.g. EVST_VS_1_1, EPST_PS_2_0)
		MyShaderCallBack* mc = new MyShaderCallBack();
		//	real all shaders present
		fileList = device->getFileSystem()->createFileList ();

		//	add and local shaders to my list
		for (int i = 0; i < fileList->getFileCount(); ++i)
		{
			//	get this filename
			core::stringc shaderFileName = fileList->getFileName (i);
			int sl = shaderFileName.size();
			//	is it a shader file (ends in ".frag")?
			if ((sl > 5) && (shaderFileName.subString (sl-5, 5) == ".frag"))
			{
				//	yep, save this name
				ShaderNames.push_back (shaderFileName.subString (0,sl-5));
				//	and read it in
				s32 shaderID = gpu->addHighLevelShaderMaterialFromFiles(
						(app_dir + "shared.vert").c_str(),	"vertexMain", video::EVST_VS_1_1,
						(fileList->getFullFileName (i)), "pixelMain", video::EPST_PS_1_1,
						mc, video::EMT_SOLID);
				//	and add it to the list
				ShaderMaterials.push_back ((video::E_MATERIAL_TYPE)shaderID);

				if (shaderID < 0)
				{
					//	that wasn't particularly great
					device->getLogger()->log ("The offending shader was:");
					device->getLogger()->log (shaderFileName.c_str());
					device->getLogger()->log ("");
				}
			}
		}
		fileList->drop();

		/*
		But just setting color and normal map is not everything. The material we want to
		use needs some additional informations per vertex like tangents and binormals.
		Because we are too lazy to calculate that information now, we let Irrlicht do
		this for us. That's why we call IMeshManipulator::createMeshWithTangents(). It
		creates a mesh copy with tangents and binormals from any other mesh.
		After we've done that, we simply create a standard mesh scene node with this
		mesh copy, set color and normal map and adjust some other material settings.
		Note that we set EMF_FOG_ENABLE to true to enable fog in the room.
		*/

		scene::IMesh* tangentMesh = smgr->getMeshManipulator()->createMeshWithTangents(
			roomMesh->getMesh(0));

		room = smgr->addMeshSceneNode(tangentMesh);
		//*
		room->setMaterialTexture(0,	colorMap);
		room->setMaterialTexture(1,	normalMap);
		room->setMaterialTexture(2, stepMap);
		//*/
		/*
		int matNum = room->getMaterialCount();
		std::cout << "I already have " << matNum << std::endl;
		room->setMaterialTexture(matNum++, colorMap);
		room->setMaterialTexture(matNum++, normalMap);
		room->setMaterialTexture(matNum++, stepMap);
		//*/

		room->getMaterial(0).EmissiveColor.set(0,0,0,0);

		//room->setMaterialFlag(video::EMF_FOG_ENABLE, true);
		room->setMaterialType(video::EMT_PARALLAX_MAP_SOLID);
		room->getMaterial(0).MaterialTypeParam = 0.035f; // adjust height for parallax effect

		// drop mesh because we created it with a create.. call.
		tangentMesh->drop();
	}
	else
	{
		system ("pause");
		return (1);
	}

	// add camera
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0,100.0f,300.0f);
		//smgr->addCameraSceneNodeFPS(0,100.0f,100.0f);	//	slower for FRAPS
	camera->setPosition(core::vector3df(-200,200,-200));

	//	and collision detection
	scene::ITriangleSelector* selector = 0;
	selector = smgr->createTriangleSelector (roomMesh->getMesh(0), room);
	scene::ISceneNodeAnimator* anim =
    smgr->createCollisionResponseAnimator(
		selector, camera, core::vector3df(20,20,20),
		core::vector3df(0,0,0),
		core::vector3df(0,0,0));
	camera->addAnimator(anim);
	anim->drop();

	/*
	Per pixel lighted materials only look cool when there are moving lights. So we
	add some. And because moving lights alone are so boring, we add billboards
	to them, and a whole particle system to one of them.
	We start with the first light which is red and has only the billboard attached.
	*/

	// add light 1 (white)
	scene::ILightSceneNode* light1 =
		smgr->addLightSceneNode(0, core::vector3df(0,0,0),
		video::SColorf(1.0f, 1.0f, 1.0f, 0.0f), 500.0f);

	// set ambient light (not working)
	//driver->setAmbientLight(video::SColor(0,100,100,100));

	// add fly circle animator to light 1
	//scene::ISceneNodeAnimator*
	anim =
		//smgr->createFlyCircleAnimator (core::vector3df(50,300,0),190.0f, -0.003f);
		smgr->createFlyCircleAnimator (core::vector3df(50,300,0),190.0f, -0.001f);	//	for FRAPS
	light1->addAnimator(anim);
	anim->drop();

	//*
	// attach billboard to the light
	scene::ISceneNode* bill =
		smgr->addBillboardSceneNode(light1, core::dimension2d<f32>(60, 60));

	bill->setMaterialFlag(video::EMF_LIGHTING, false);
	bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	driver->setTextureCreationFlag(video::ETCF_CREATE_MIP_MAPS, true);
	driver->setTextureCreationFlag(video::ETCF_USE_DXT5, true);
	driver->setTextureCreationFlag(video::ETCF_USE_2_CHANNEL, false);
	bill->setMaterialTexture(0, driver->getTexture("particlered.png"));
	//*/

	MyEventReceiver receiver(room, env, driver);
	device->setEventReceiver(&receiver);

	//	some user info
	std::cout << "beginning the render" << std::endl;

	/*
	Finally, draw everything. That's it.
	*/

	int lastFPS = -1;

	while(device->run())
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, 0);

		smgr->drawAll();
		env->drawAll();

		driver->endScene();

		int fps = driver->getFPS();

		if ((lastFPS != fps) || flag_refresh)
		{
		  core::stringw str = L"CSM Demo  [FPS ";
		  str += fps;
		  str += "]  F1=Help  (steps=";
		  str += num_steps;
		  str += ", gain=";
		  str += static_cast<int>(csm_gain);
		  str += ".";
		  str += static_cast<int>(csm_gain*10.0 + 0.5) % 10;
		  str += ", offset=";
		  str += static_cast<int>(csm_offset);
		  str += ".";
		  str += static_cast<int>(csm_offset*10.0 + 0.5) % 10;
		  str += ")";

		  device->setWindowCaption(str.c_str());
		  lastFPS = fps;

		  flag_refresh = false;
		}

	}

	device->drop();

	return 0;
}

