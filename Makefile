default:
	echo "make windows or make linux"

windows:
	gcc main.c -o bin/pong_c-win64 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 lgdi32 lwinmn
linux:
	gcc main.c -o bin/pong_c-linux64 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11

clean:
	rm bin/*

