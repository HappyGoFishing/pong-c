CFILES = *.c

LINUX_COMPILER = gcc
LINUX_ARGS = -Wall -std=c99 -Wno-missing-braces -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11
LINUX_BINARY = -o "bin/pongC-linux64"

WINDOWS_COMPILER=gcc
WINDOWS_ARGS =  -Wall -std=c99 -Wno-missing-braces -lraylib -lopengl32 lgdi32 lwinmn
WINDOWS_BINARY = -o "bin/pongC-win64"

MAC_COMPILER = gcc
MAC_ARGS = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
MAC_BINARY = -o "bin/pongC-mac64"


windows:
	$(WINDOWS_COMPILER) $(CFILES) $(WINDOWS_ARGS) $(WINDOWS_BINARY) 

LINUX_ARGS = -Wall -std=c99 -Wno-missing-braces -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11
LINUX_BINARY = -o "bin/pongC-linux64"
linux:
	$(LINUX_COMPILER) $(CFILES) $(LINUX_ARGS) $(LINUX_BINARY)


MAC_ARGS = -Llib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a
MAC_BINARY = -o "bin/pongC-mac64"
mac:
	$(MAC_COMPILER) $(CFILES) $(MAC_ARGS) $(MAC_BINARY)
clean:
	rm bin/*

