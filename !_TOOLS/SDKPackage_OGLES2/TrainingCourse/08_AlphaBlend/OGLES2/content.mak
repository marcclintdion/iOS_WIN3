#--------------------------------------------------------------------------
# Name         : content.mak
# Title        : Makefile to build content files
#
# Copyright    : Copyright (C)  Imagination Technologies Limited.
#              : No part of this software, either material or conceptual 
#              : may be copied or distributed, transmitted, transcribed,
#              : stored in a retrieval system or translated into any 
#              : human or computer language in any form by any means,
#              : electronic, mechanical, manual or other-wise, or 
#              : disclosed to third parties without the express written
#              : permission of VideoLogic Limited, Unit 8, HomePark
#              : Industrial Estate, King's Langley, Hertfordshire,
#              : WD4 8LZ, U.K.
#
# Description  : Makefile to build content files for demos in the PowerVR SDK
#
# Platform     :
#
#--------------------------------------------------------------------------

#############################################################################
## Variables
#############################################################################
PVRTEXTOOL 	= ..\..\..\Utilities\PVRTexTool\PVRTexToolCL\Windows_x86_32\PVRTexTool.exe
FILEWRAP 	= ..\..\..\Utilities\Filewrap\Windows_x86_32\Filewrap.exe
PVRUNISCO 	= ..\..\..\Utilities\PVRUniSCo\OGLES\Windows_x86_32\glslcompiler_sgx535.exe

MEDIAPATH = ../Media
CONTENTDIR = Content

#############################################################################
## Instructions
#############################################################################

TEXTURES = \
	Background.pvr \
	Foreground.pvr

BIN_SHADERS = \
	FragShader.fsc \
	VertShader.vsc

RESOURCES = \
	$(CONTENTDIR)/Background.cpp \
	$(CONTENTDIR)/Foreground.cpp \
	$(CONTENTDIR)/FragShader.cpp \
	$(CONTENTDIR)/VertShader.cpp

all: resources
	
help:
	@echo Valid targets are:
	@echo resources, textures, binary_shaders, clean
	@echo PVRTEXTOOL, FILEWRAP and PVRUNISCO can be used to override the default paths to these utilities.

clean:
	-rm $(RESOURCES)
	-rm $(BIN_SHADERS)
	-rm $(TEXTURES)

resources: 		$(CONTENTDIR) $(RESOURCES)
textures: 		$(TEXTURES)
binary_shaders:	$(BIN_SHADERS)

$(CONTENTDIR):
	-mkdir $@

Background.pvr: $(MEDIAPATH)/backgrnd.png
	$(PVRTEXTOOL) -nt -fOGL565 -i$(MEDIAPATH)/backgrnd.png -o$@

Foreground.pvr: $(MEDIAPATH)/forgrnd.png $(MEDIAPATH)/tforgrnd.png
	$(PVRTEXTOOL) -nt -fOGL8888 -i$(MEDIAPATH)/forgrnd.png -a$(MEDIAPATH)/tforgrnd.png -o$@

$(CONTENTDIR)/Background.cpp: Background.pvr
	$(FILEWRAP)  -o $@ Background.pvr

$(CONTENTDIR)/Foreground.cpp: Foreground.pvr
	$(FILEWRAP)  -o $@ Foreground.pvr

$(CONTENTDIR)/FragShader.cpp: FragShader.fsh FragShader.fsc
	$(FILEWRAP)  -s  -o $@ FragShader.fsh
	-$(FILEWRAP)  -oa $@ FragShader.fsc

$(CONTENTDIR)/VertShader.cpp: VertShader.vsh VertShader.vsc
	$(FILEWRAP)  -s  -o $@ VertShader.vsh
	-$(FILEWRAP)  -oa $@ VertShader.vsc

FragShader.fsc: FragShader.fsh
	$(PVRUNISCO) FragShader.fsh $@  -f 

VertShader.vsc: VertShader.vsh
	$(PVRUNISCO) VertShader.vsh $@  -v 

############################################################################
# End of file (content.mak)
############################################################################
