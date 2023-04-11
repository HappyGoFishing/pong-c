

windows:
	gcc *.c -Wall -std=c99 -Wno-missing-braces -lraylib -lopengl32 lgdi32 lwinmn -o "bin/pongC-win64"

linux:
	gcc *.c -Wall -std=c99 -Wno-missing-braces -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11 -o "bin/pongC-linux64"


mac:
	clang --std=c99 *.c -L lib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a -o "bin/pongC-mac64"

clean:
	rm bin/*

