# Add paths to dependency headers here
ExternalIncludes = -I../../../hrengin/include/
ExternalLibraries = -L. -lhrgame -lhrcore -lhraudio -lhrgraphics -lhrplatform -lhrphysics -Wl,-rpath-link,./ -Wl,-R.

# Version
VersionMajor = 0
VersionMinor = 5

# Includes and objects
Objects = awrts.o CMapManager.o ai/CNavigatorWheeled.o ai/CNavigatorGround.o ai/CGhostNavigator.o players/CPlayerHuman.o units/CUnit.o units/CLocomotor.o units/CUnitManager.o

Includes = -I../../include -I. $(ExternalIncludes)

Libraries = $(ExternalLibraries)

# Compiler flags
CompilerFlags  = $(Includes)
CompilerFlags += -g -D_DEBUG
CompilerFlags += -fPIC
CC = cc
CXX = g++ -std=c++11 $(CompilerFlags)

Version = $(VersionMajor).$(VersionMinor)
Executable = awrts

all: awrts

awrts: $(Objects)
	$(CXX) $(Objects) -o $(Executable) $(Libraries)

.PHONY : clean
clean:
	-rm $(Executable) $(Objects)