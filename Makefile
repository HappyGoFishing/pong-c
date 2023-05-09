

windows:
	gcc *.c -Wall -std=c99 -Wno-missing-braces -L lib/libraylib.a -lraylib -lopengl32 -lgdi32 -lwinmm -o "bin/pong-c-win"
linux:
	gcc *.c -Wall -std=c99 -Wno-missing-braces  -L lib/libraylib.a -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11 -o "bin/pong-c-linux"


mac:
	clang --std=c99 *.c -L lib/ -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/libraylib.a -o "bin/pong-c-mac"

clean:
	rm bin/*

