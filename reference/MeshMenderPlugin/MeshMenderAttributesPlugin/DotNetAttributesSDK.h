#pragma once

using namespace System;
using namespace NPluginBridge;

namespace ShaderDesigner
{
	public __gc class DotNetDllAttributeInterface
	{
  public:   
    virtual String *GetPluginDescription();
    virtual DotNetAttributeData *RunPlugin(const DotNetMeshData *inmeshData,DotNetMeshData *outmeshData);
    virtual bool Clean();

  private:
    DotNetAttributeData *attribData;		
	};
}
