default:
	cc -std=c11 -I./raylib/include  *.c -o bin/pong_c  -L lib/*  lib/* -lglfw -lGL -lm -lpthread -ldl -lrt -lX11
run:
	./pong_c

clean:
	rm bin/*

