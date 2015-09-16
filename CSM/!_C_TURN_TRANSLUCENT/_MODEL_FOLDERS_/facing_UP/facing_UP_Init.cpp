     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      facing_UP_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_facing_UP =                                                                                                        

      "    #define highp                                                                                                   \n"                           

      "    uniform highp vec4  light_POSITION_01;                                                                          \n"                           
      "    uniform       mat4  mvpMatrix;                                                                                  \n"                           
      "    uniform       mat4  mvMatrix;                                                                                   \n"        
      "    uniform       mat4  lightMatrix;                                                                                \n"                                                             
      "    uniform       mat4  textureMatrix;                                                                              \n"         
      "    uniform highp float shininess;                                                                                  \n"                       
      //--------------------------------------------
      "    attribute     vec4  position;                                                                                   \n"                           
      "    attribute     vec3  normal;                                                                                     \n"         
      "    attribute     vec3  tangent;                                                                                    \n"             
      "    attribute     vec2  texture;                                                                                    \n"                           
      
      "    uniform highp vec4  offset;                                                                                     \n" 
    
      "    varying highp vec4  lightPosition_PASS;                                                                         \n"                           
      "    varying highp vec4  shadowTexcoord;                                                                             \n"       

      "    varying highp vec2  varTexcoord;                                                                                \n"                           
     
      "            highp vec4  TEMP_shadowTexcoord;                                                                        \n" 
       
//-----------------------------------------------------------------------------------------------------------------
      "    varying highp vec3  vertex_pos;                                                                                  \n" 
//-----------------------------------------------------------------------------------------------------------------      
      "    void main()                                                                                                      \n"                           
      "    {                                                                                                                \n"                           
        
      "            vec3 eyeSpaceVert     =  (mvMatrix * position).xyz;                                                      \n"
                   //----------------
      "            vec3 eyeSpaceNormal   =  (mvMatrix * vec4(normal, 0.0));                                                 \n"  
      "            vec3 eyeSpaceTangent  =  (mvMatrix * vec4(tangent, 0.0));                                                \n"  
      "            vec3 eyeSpaceBinormal =   cross(eyeSpaceNormal, eyeSpaceTangent);                                        \n"  
                   //---------------------------------------------------------------------------------------------------------    
      "            vertex_pos            =   vec3 ( dot (eyeSpaceTangent,  eyeSpaceVert),                                   \n" 
      "                                             dot (eyeSpaceBinormal, eyeSpaceVert),                                   \n" 
      "                                             dot (eyeSpaceNormal,   eyeSpaceVert));                                  \n" 
      
                   //---------------------------------------------------------------------------------------------------------     
     
      "            TEMP_shadowTexcoord   =   textureMatrix * mvpMatrix * position + mvMatrix[3][3] * 1.0;                   \n" 
      "            shadowTexcoord        =   TEMP_shadowTexcoord + offset;                                                  \n"    
                   //---------------------------------------------------------------------------------------------------------
                   "            lightPosition_PASS    =   normalize(lightMatrix * light_POSITION_01);                       \n"                           
   
      "            varTexcoord           =   texture;                                                                       \n"                           
      "            gl_Position           =   mvpMatrix * position;                                                          \n"                           


      "    }\n";                                                                                                                             
      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################        
   
   
      //---------------------------------------------------------------------                                                                   
      facing_UP_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(facing_UP_SHADER_VERTEX, 1, &vertexSource_facing_UP, NULL);                                                                        
      glCompileShader(facing_UP_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_facing_UP =                                                                                                            

      " #ifdef GL_ES                                                                                                              \n"                       
      " #else                                                                                                                     \n"                       
      " #define highp                                                                                                             \n"                       
      " #endif                                                                                                                    \n"                       

      "    uniform sampler2D   Texture1;                                                                                          \n"                       
      "    uniform sampler2D   NormalMap;                                                                                         \n"                       
      "    uniform sampler2D   HeightMap;                                                                                         \n"        
      "    uniform sampler2DShadow   ShadowTexture;                                                                               \n"     
      "    uniform highp float shininess;                                                                                         \n"                       
      //--------------------------------------------
      "    uniform highp vec4  light_POSITION_01;                                                                                 \n"    
      "    varying highp vec4  lightPosition_PASS;                                                                                \n"                       

      "    varying highp vec4  shadowTexcoord;                                                                                    \n"         
      "    varying highp vec2  varTexcoord;                                                                                       \n"                       
      //--------------------------------------------
      "   varying vec3 vertex_pos;                                                                                                \n" 
      "   float depth = 0.5;                                                                                                      \n" 
      //-------------------------
      "            highp float   NdotL2;                                                                                          \n"                       
      
      "            highp vec4    shadow;                                                                                          \n"     
        
      "            highp vec3    normal_2;                                                                                        \n"                       
      "            highp vec3    NormalTex;                                                                                       \n"                       
      //-----------------------------------
      //-----------------------------------      
      //=============================================================================================================================     
      "    void intersect_square_cone_3step (inout vec3 dp, in vec3 ds);                                                          \n" 
      "    void ray_intersect_cone(inout vec3 p, inout vec3 v);                                                                   \n" 
      "    void setup_ray_ps(in vec2 texCoordinates, out vec3 rayPos, out vec3 rayVec);                                           \n"       
      //=============================================================================================================================     

      "     void main()                                                                                                           \n"                       
      "     {                                                                                                                     \n"                       
   
      "              vec3 s;                                                                                                      \n"
      "              vec3 pt_eye;                                                                                                 \n"
      "              float a;                                                                                                     \n"

      "              float depth = .3;                                                                                            \n"      
      "              a           = -depth / vertex_pos.z;                                                                         \n"
      "              s           = vertex_pos * a * 0.5;                                                                          \n"
      "              s.z         = 1.0;                                                                                           \n"
      "              s           = s;                                                                                             \n"  
      
      "              pt_eye      = vec3 (varTexcoord, 0.0);                                                                       \n"
      
      "              intersect_square_cone_3step (pt_eye, s);                                                                     \n"               
      //-----------------------------------------------------------------------------------------------------------------------------     
      
      " 		         vec4  shadowCoordinateWdivide    =  shadowTexcoord / shadowTexcoord.w;                                   \n" 
      " 		               shadowCoordinateWdivide.z +=  -0.2855;                                                             \n" 
      " 		         float distanceFromLight          =  shadow2DProj(ShadowTexture, shadowTexcoord).r;                       \n" 
     
      " 		         float shadow                     =  1.0;                                                                 \n" 
      " 		         if (shadowTexcoord.w             >  0.0)                                                                 \n" 
      " 		      		  shadow = distanceFromLight  <  shadowCoordinateWdivide.z ? 0.6 : 1.0 ;                              \n"   
                         //-------------------------------------------------------------------------------------    
      
      
      //-----------------------------------------------------------------------------------------------------------------------------     
      "         vec4 c                 =  texture2D(Texture1,pt_eye.xy);                                                          \n" 
      //------------------------------------------------------------------------------------   
      "         NormalTex              =  texture2D(NormalMap,  pt_eye.xy).xyz;                                                   \n"                       
      "         NormalTex              = (NormalTex - 0.5);                                                                       \n"        
      "         normal_2               =  normalize(NormalTex);                                                                   \n"      
      "         NdotL2                 =  max(dot(normal_2, lightPosition_PASS.xyz), 0.0);                                        \n"      
      "         float shiny            =  pow(NdotL2,60.0);                                                                       \n"      
      //-----------------------------------------------------------------------------------------------------------------------------
      "         gl_FragColor           = (c * NdotL2 + c *vec4(1.0, 1.0, 1.0, 1.0) * shiny * c) * shadow;    \n"
      
      
      //"////|TextureMapSpace|////   gl_FragColor           = vec4((varTexcoord.x+.5)/2.0, (varTexcoord.y +.5)/2.0, 0.0, 0.0); \n"
      
      "    }\n"                                                                                                                                   

//=====================================================================================================================================
//=====================================================================================================================================
//=====================================================================================================================================


"void intersect_square_cone_3step (inout vec3 dp, in vec3 ds)                                                                   \n"
"{                                                                                                                              \n"

"   float iz = max(abs(ds.x),abs(ds.y));                                                                                        \n"

"   float w  = .28;                                                                                                            \n"
//"   float w  = constantAttenuation;                                                                                           \n"

"   vec4 t;                                                                                                                     \n"
//============================================================
"   dp += 0.261004 * ds;                                                                                                        \n"
//"   dp += shininess * ds;                                                                                                     \n"

//-------------------------------------------------------------
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                         \n"

//--------------------------------
//_________________________________constantAttenuation  =  1.02
//_________________________________shininess            =  0.43
//============================================================  
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                         \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.46
//_________________________________shininess            =  0.2
//============================================================   
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                         \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.46
//_________________________________shininess            =  0.2
//============================================================  




"   return;                                                                                                                     \n"
"}                                                                                                                              \n"

//===========================================================================================================================
/*
"   void ray_intersect_cone(inout vec3 p, inout vec3 v)                                                                         \n"
"   {                                                                                                                           \n"
"   	float dist = length(v.xy);                                                                                              \n"
	
"   	for(int i=0; i < 4; i++)                                                                                                \n"
"   	{                                                                                                                       \n"
"   		vec4 tex = texture2D(HeightMap, p.xy);                                                                              \n"
"   		float height = clamp((tex.w - p.z), 0.0, 1.0);;                                                                     \n"

"   		float cone_ratio = tex.z*tex.z;                                                                                     \n"
		
		         //float stepDist = height * cone_ratio / (v.z*cone_ratio + dist);                                              \n"
"   		float stepDist = height * cone_ratio / (cone_ratio + dist);                                                         \n"
"   		p += v * stepDist;                                                                                                  \n"
		
		        //===========================================================
		        //float4 tex = tex2D(cone_map, p.xy);                                                                           \n"
		        //float height = max(0, tex.w - p.z);                                                                           \n"
		        //float stepDist = height * 0.2;                                                                                \n"
		        //p += v * stepDist;                                                                                            \n"
		        //--------------------------------------------------------
		        //float stepDist = height * cone_ratio / (cone_ratio + 0.1);                                                    \n"
		        //--------------------------------------------------------
		        //p += v * height * cone_ratio / (v.z*cone_ratio + dist);                                                       \n"
		        //===========================================================
"   	}                                                                                                                       \n"
"     return;                                                                                                                   \n"

"    }                                                                                                                          \n"
*/
//===========================================================================================================================
/*"   void setup_ray_ps(in vec3 texCoordinates, out vec3 rayPos, out vec3 rayVec)                                               \n"
//"   {                                                                                                                         \n"
"   	rayPos = float3(IN.uv0, 0.0);                                                                                           \n"
	
"   	rayVec = normalize(IN.eyeVec);                                                                                          \n"
"   	rayVec.z = abs(rayVec.z);                                                                                               \n"


//"   	if (DEPTH_BIAS) //Depth bias used by Fabio Policarpo                                                                                              \n"
//"   	{                                                                                                                       \n"
//"   		float db = 1.0 - rayVec.z;                                                                                          \n"
//"   		db *= db;                                                                                                           \n"
//"   		db = 1.0 - db*db;                                                                                                   \n"
//"   		rayVec.xy *= db;                                                                                                    \n"
//"   	}                                                                                                                       \n"
	
"   	rayVec.xy *= depth;                                                                                                     \n"
"   }                                                                                                                           \n"
*/
//===========================================================================================================================
/*
vec4 bump_ps(vec2 uv0, vec3 eyeVec, vec3 lightVec)
{
	if (BORDER_CLAMP)
	{
		if (uv0.x < 0.0) discard;
		if (uv0.x > tile) discard;
		if (uv0.y < 0.0) discard;
		if (uv0.y > tile) discard;
	}

	// View and light vectors
	float3 v = normalize(eyeVec);
	float3 l1 = normalize(lightVec);
	
	// Diffuse texture color
	float3 color = tex2D(color_map, uv0).xyz;

	// Bump map
	float3 n = tex2D(cone_map, uv0);
	n.xy = n.xy * 2.0 - 1.0;
	n.y = -n.y;
	n.z = sqrt(1.0 - dot(n.xy, n.xy));
	
	return phongShading(n, l1, -v, color);
}
*/
//===========================================================================================================================



;



      //---------------------------------------------------------------------                                                                         
      facing_UP_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(facing_UP_SHADER_FRAGMENT, 1, &fragmentSource_facing_UP, NULL);                                                                          
      glCompileShader(facing_UP_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(facing_UP_SHADER, facing_UP_SHADER_VERTEX);                                                                                              
      glAttachShader(facing_UP_SHADER, facing_UP_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(facing_UP_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(facing_UP_SHADER, 1, "normal");       
      glBindAttribLocation(facing_UP_SHADER, 2, "tangent");  
      glBindAttribLocation(facing_UP_SHADER, 3, "texture");                                                                                             
      //------------------------------------------------                                                                                              
      glLinkProgram(facing_UP_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(facing_UP_SHADER, facing_UP_SHADER_VERTEX);                                                                                              
      glDetachShader(facing_UP_SHADER, facing_UP_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(facing_UP_SHADER_VERTEX);                                                                                                            
      glDeleteShader(facing_UP_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_facing_UP                   = glGetUniformLocation(facing_UP_SHADER,   "mvpMatrix");                                              
      UNIFORM_MODELVIEW_facing_UP                       = glGetUniformLocation(facing_UP_SHADER,   "mvMatrix");        
      UNIFORM_LIGHT_MATRIX_facing_UP                    = glGetUniformLocation(facing_UP_SHADER,   "lightMatrix");                                            
      UNIFORM_textureMatrix_facing_UP                   = glGetUniformLocation(facing_UP_SHADER,   "textureMatrix");       
      UNIFORM_offset_facing_UP                          = glGetUniformLocation(facing_UP_SHADER,   "offset");      
      //-------------------------------------
      UNIFORM_LIGHT_POSITION_01_facing_UP               = glGetUniformLocation(facing_UP_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_facing_UP                       = glGetUniformLocation(facing_UP_SHADER,   "shininess");                                              
      //-------------------------------------
      UNIFORM_TEXTURE_SHADOW_facing_UP                  = glGetUniformLocation(facing_UP_SHADER,   "ShadowTexture");        
      UNIFORM_TEXTURE_HEIGHT_facing_UP                  = glGetUniformLocation(facing_UP_SHADER,   "HeightMap");                                                      
      UNIFORM_TEXTURE_DOT3_facing_UP                    = glGetUniformLocation(facing_UP_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_facing_UP                         = glGetUniformLocation(facing_UP_SHADER,   "Texture1");                                               
      //------------------------------------------------------------------------------------------------------------//___LOAD_TEXTURES                
      //------------------------------------------------------------------------------------------                                              
      #ifdef __APPLE__                                                                                                                          
      filePathName = [[NSBundle mainBundle] pathForResource:@"facing_UP_DOT3" ofType:@"bmp"];                                                  
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &facing_UP_NORMALMAP);                                                                                                     
      glBindTexture(GL_TEXTURE_2D, facing_UP_NORMALMAP);                                                                                          
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      //---------------------                                                                                                                   
      filePathName = [[NSBundle mainBundle] pathForResource:@"facing_UP" ofType:@"png"];                                                       
      image = imgLoadImage([filePathName cStringUsingEncoding:NSASCIIStringEncoding]);                                                   
      glGenTextures(1, &facing_UP_TEXTUREMAP);                                                                                                       
      glBindTexture(GL_TEXTURE_2D, facing_UP_TEXTUREMAP);                                                                                            
      ConfigureAndLoadTexture(image->data,  image->width, image->height );                                                                      
      imgDestroyImage(image);                                                                                                                   
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------                                              
      #ifdef WIN32                                                                                                                            
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP_step.png",             facing_UP_HEIGHT);         
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP_DOT3.bmp",          facing_UP_NORMALMAP);                                                      
      loadTexture("_MODEL_FOLDERS_/facing_UP/facing_UP.png",               facing_UP_TEXTUREMAP);                                                        
      #endif                                                                                                                                    
      //------------------------------------------------------------------------------------------------------------//___LOAD_VBO               
      #include    "facing_UP.cpp"                                                                                                                
      glGenBuffers(1,              &facing_UP_VBO);                                                                                                
      glBindBuffer(GL_ARRAY_BUFFER, facing_UP_VBO);                                                                                                
      glBufferData(GL_ARRAY_BUFFER, sizeof(facing_UP), facing_UP, GL_STATIC_DRAW);                                                                    
      glBindBuffer(GL_ARRAY_BUFFER, 0);                                                                                                         
      //--------------------------------------------------------------------------------------------------------------------     
      #include    "facing_UP_INDICES.cpp" 
      glGenBuffers(1, &facing_UP_INDEX_VBO);                       
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facing_UP_INDEX_VBO);                   
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(facing_UP_INDICES), facing_UP_INDICES, GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);      
      //=================================================================================================================================       




