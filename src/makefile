#OBJS specifies which files to compile as part of the project
OBJS = main.cpp commonFunction.cpp Texture.cpp MainObject.cpp map.cpp Time.cpp Button.cpp Text.cpp
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = the_escape

INCLUDE = -IC:\SDL\SDL2-2.26.3\x86_64-w64-mingw32\include\SDL2

LIB = -LC:\SDL\SDL2-2.26.3\x86_64-w64-mingw32\lib

#This is the target that compiles our executable
all : $(OBJS)
	g++ $(OBJS) $(INCLUDE) $(LIB)  -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf  -o  $(OBJ_NAME)