// Archivo DLL principal.
#include "nvmeshmender.h"

#include "DotNetAttributesSDK.h"
#include <math.h>

using namespace ShaderDesigner;
using namespace System::Collections;
/*
void Msg(char *fmt, ...)
{
	char buffer[2048];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(buffer, fmt, ap);
	va_end(ap);


	MessageBox(NULL, buffer, NULL, MB_OK);
}
*/

//-------------------------------------------------------------------------
String *DotNetDllAttributeInterface::GetPluginDescription()
{
  return  S"MeshMender tangents & binormals computation plugin (fixed by yooyo).\r\nUsage:\r\nattribute vec3 tangent;\r\nattribute vec3 binormal;";  
}
//-------------------------------------------------------------------------
DotNetAttributeData *DotNetDllAttributeInterface::RunPlugin(const DotNetMeshData *meshData,DotNetMeshData *outmeshData)
{
	unsigned int i;

	if(meshData->type==0) return 0;
//	Msg("DotNetDllAttributeInterface::RunPlugin\n 1");

	unsigned int size = meshData->vertexCount; 
//	return attribData;
//	Msg("DotNetDllAttributeInterface::RunPlugin\n meshData->vertexCount = %d ", meshData->vertexCount*3);
	std::vector< MeshMender::Vertex > theVerts;
	std::vector< unsigned int > theIndices;
	std::vector< unsigned int > mappingNewToOld;

//	theVerts.clear();
//	theIndices.clear();
//	mappingNewToOld.clear();


	//fill up the vectors with your mesh's data
	for(i = 0; i < size; i++)
	{
		MeshMender::Vertex v;
		
		v.pos.x = meshData->Vertices[3*i+0];
		v.pos.y = meshData->Vertices[3*i+1];
		v.pos.z = meshData->Vertices[3*i+2];
		v.s = meshData->TexCoord[2*i+0];
		v.t = meshData->TexCoord[2*i+1];
		//meshmender will computer normals, tangents, and binormals, no need to fill those in.
		//however, if you do not have meshmender compute the normals, you _must_ pass in valid
		//normals to meshmender
		theVerts.push_back(v);
	}

	unsigned int indsize = meshData->indexCount; 
//	Msg("DotNetDllAttributeInterface::RunPlugin\n meshData->indexCount = %d", meshData->indexCount);

	for(DWORD ind= 0 ; ind< indsize; ++ind)
	{
		theIndices.push_back(meshData->Indices[ind]);
	}
	bool m_MENDER_OPT_computeNormals				= true;
	float m_MENDER_OPT_minNormalsCreaseCosAngle		= 0.30f;
	float m_MENDER_OPT_minTangentsCreaseCosAngle	= 0.30f;
	float m_MENDER_OPT_minBinormalsCreaseCosAngle	= 0.30f;
	float m_MENDER_OPT_weightNormalsByArea			= 0.0f;
	bool m_MENDER_OPT_respectExistingSplits			= false;
	bool m_MENDER_OPT_fixCylindricalWrapping		= false;

//	Msg("DotNetDllAttributeInterface::RunPlugin\n Before Mend");

	MeshMender Mender;

	Mender.Mend( theVerts,  theIndices, mappingNewToOld,
		m_MENDER_OPT_minNormalsCreaseCosAngle,
		m_MENDER_OPT_minTangentsCreaseCosAngle,
		m_MENDER_OPT_minBinormalsCreaseCosAngle,
		m_MENDER_OPT_weightNormalsByArea,
		MeshMender::CALCULATE_NORMALS,
		MeshMender::DONT_RESPECT_SPLITS,
		MeshMender::DONT_FIX_CYLINDRICAL);
//	Msg("DotNetDllAttributeInterface::RunPlugin\n After Mend");


	//outmeshData->ParentName = meshData->ParentName;
	//outmeshData->type = meshData->type;

	DotNetAttributeData *attribData = new DotNetAttributeData;

	outmeshData->vertexCount = theVerts.size();
//	Msg("DotNetDllAttributeInterface::RunPlugin\n outmeshData->vertexCount= %d ", outmeshData->vertexCount*3);


//	MessageBox(NULL, "DotNetDllAttributeInterface::RunPlugin\n Vertices", NULL, MB_OK);

	outmeshData->Vertices = new float[outmeshData->vertexCount*3];
	for (i=0; i<outmeshData->vertexCount; i++)
	{
		outmeshData->Vertices[3*i +0] = theVerts[i].pos[0];
		outmeshData->Vertices[3*i +1] = theVerts[i].pos[1];
		outmeshData->Vertices[3*i +2] = theVerts[i].pos[2];
	} // for (i=0; i<outmeshData->vertexCount; i++)


//	Msg("DotNetDllAttributeInterface::RunPlugin\n Normals");

	outmeshData->Normals = new float[outmeshData->vertexCount*3];

	for (i=0; i<outmeshData->vertexCount; i++)
	{
		outmeshData->Normals[3*i +0] = theVerts[i].normal[0];
		outmeshData->Normals[3*i +1] = theVerts[i].normal[1];
		outmeshData->Normals[3*i +2] = theVerts[i].normal[2];
	} // for (i=0; i<outmeshData->vertexCount; i++)


//	Msg("DotNetDllAttributeInterface::RunPlugin\n TexCoord");

	outmeshData->TexCoord = new float[outmeshData->vertexCount*2];

	for (i=0; i<outmeshData->vertexCount; i++)
	{
		outmeshData->TexCoord[2*i +0] = theVerts[i].s;
		outmeshData->TexCoord[2*i +1] = theVerts[i].t;
	} // for (i=0; i<outmeshData->vertexCount; i++)

//	Msg("DotNetDllAttributeInterface::RunPlugin\n tangents");

	float tangents  __gc[] = new float __gc[outmeshData->vertexCount*3];  
	for(i=0; i<outmeshData->vertexCount; i++)
	{
		tangents[3*i + 0] = theVerts[i].tangent[0];
		tangents[3*i + 1] = theVerts[i].tangent[1];
		tangents[3*i + 2] = theVerts[i].tangent[2];
	}
	attribData->PushAttribArray(S"tangent",S"GL_FLOAT",3,tangents);

//	Msg("DotNetDllAttributeInterface::RunPlugin\n binormals");

	float binormals  __gc[] = new float __gc[outmeshData->vertexCount*3];  
	for(i=0; i<outmeshData->vertexCount; i++)
	{
		binormals[3*i + 0] = theVerts[i].binormal[0];
		binormals[3*i + 1] = theVerts[i].binormal[1];
		binormals[3*i + 2] = theVerts[i].binormal[2];
	}
	attribData->PushAttribArray(S"binormal",S"GL_FLOAT",3,binormals);

//	Msg("DotNetDllAttributeInterface::RunPlugin\n outmeshData->indexCount = %d", outmeshData->indexCount);

	outmeshData->indexCount = theIndices.size();
	outmeshData->Indices = new unsigned int[outmeshData->indexCount];
	for (i=0; i<outmeshData->indexCount; i++)
		outmeshData->Indices[i] = theIndices[i];

//	Msg("DotNetDllAttributeInterface::RunPlugin\n return attribData");

	return attribData;
}

/*
DotNetAttributeData *DotNetDllAttributeInterface::RunPlugin(const DotNetMeshData *meshData,DotNetMeshData *outmeshData)
{
  if(meshData->type==0)
    return 0;
  unsigned int size = meshData->vertexCount*3; 
  NVMeshMender aMender;  
  NVMeshMender::VAVector input; 
  NVMeshMender::VAVector output;
  NVMeshMender::VertexAttribute att;  

  att.Name_ = "position";
  for (unsigned int p = 0; p<size;p++)
    att.floatVector_.push_back(meshData->Vertices[p]);
  input.push_back(att);
  att.floatVector_.clear();

  att.Name_ = "normal";
  for(unsigned int p = 0; p < size;p++)
    att.floatVector_.push_back(meshData->Normals[p]);
  input.push_back(att);
  att.floatVector_.clear();

  att.Name_ = "indices";
  for(unsigned int p = 0; p <meshData->indexCount;p++)
    att.intVector_.push_back(meshData->Indices[p]);    
  input.push_back(att);
  att.intVector_.clear();

  att.Name_ = "texcoord";
  for(unsigned int p = 0; p < meshData->vertexCount*2;p+=2)
  {
    att.floatVector_.push_back(meshData->TexCoord[p]);
    att.floatVector_.push_back(meshData->TexCoord[p+1]);
    att.floatVector_.push_back(0);
  }
  input.push_back(att);

  att.floatVector_.clear();
  att.Name_ = "position";
  output.push_back(att);
  att.Name_ = "indices";
  output.push_back(att);
  att.Name_ = "texcoord";
  output.push_back(att);
  att.Name_ = "normal";
  output.push_back(att);
  att.Name_ = "tangent";
  output.push_back(att);
  att.Name_ = "binormal";
  output.push_back(att);
  
  
  DotNetAttributeData *attribData = new DotNetAttributeData;
  if (aMender.Munge(input,output,3.141592654f / 3.0f,	0,
                    NVMeshMender::FixTangents,NVMeshMender::FixCylindricalTexGen, 
                    NVMeshMender::WeightNormalsByFaceSize))
  {
    for(unsigned int i=0;i<output.size();i++)
    {      
      if(output[i].Name_ == "position")
      {
        outmeshData->vertexCount = output[i].floatVector_.size()/3;
        outmeshData->Vertices = new float[outmeshData->vertexCount*3];
        for(unsigned long p=0;p<outmeshData->vertexCount*3;p++)
          outmeshData->Vertices[p] = output[i].floatVector_[p];
      }
      else if(output[i].Name_ == "indices")
      {        
        outmeshData->indexCount = output[i].intVector_.size();
        outmeshData->Indices= new unsigned int[outmeshData->indexCount];
        for(unsigned int p=0;p<outmeshData->indexCount;p++)
          outmeshData->Indices[p] = output[i].intVector_[p];
      }
      else if(output[i].Name_ == "normal")
      {        
        outmeshData->Normals = new float[outmeshData->vertexCount*3];
        for(unsigned long p=0;p<outmeshData->vertexCount*3;p++)
          outmeshData->Normals[p] = output[i].floatVector_[p];
      }
      else if(output[i].Name_ == "texcoord")
      {        
        outmeshData->TexCoord= new float[outmeshData->vertexCount*2];
        int k=0;
        for(unsigned long p=0;p<output[i].floatVector_.size();p+=3)
        {
          outmeshData->TexCoord[k++] = output[i].floatVector_[p];
          outmeshData->TexCoord[k++] = output[i].floatVector_[p+1];
        }
      }
      else if(output[i].Name_ == "tangent")
      {       
        float tangents  __gc[] = new float __gc[outmeshData->vertexCount*3];  
        for(unsigned long p=0;p<outmeshData->vertexCount*3;p++)
          tangents[p] = output[i].floatVector_[p];
        attribData->PushAttribArray(S"tangent",S"GL_FLOAT",3,tangents);
      }
      else if(output[i].Name_ == "binormal")
      {        
        float binormals __gc[] = new float __gc[outmeshData->vertexCount*3];
        for(unsigned long p=0;p<outmeshData->vertexCount*3;p++)
          binormals[p] = output[i].floatVector_[p];
        attribData->PushAttribArray(S"binormal",S"GL_FLOAT",3,binormals);
      }
    }
    return attribData;
  }
  else 
    return 0;
  
}
*/
//-------------------------------------------------------------------------
bool DotNetDllAttributeInterface::Clean()
{
  return true;
}
//-------------------------------------------------------------------------
