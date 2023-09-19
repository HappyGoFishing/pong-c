BUILD_DIR=bin

windows:
	gcc *.c -Wall -std=c99 -Wno-missing-braces -L lib/ms-windows -lraylib -lopengl32 -lgdi32 -lwinmm -o $(BUILD_DIR)/pong-c-windows

linux:
	mkdir -p $(BUILD_DIR)
	gcc *.c -Wall -std=c99 -Wno-missing-braces -L lib/gnu-linux -lraylib -lglfw -lGL -lm -lpthread -ldl -lrt -lX11 -o $(BUILD_DIR)/pong-c-linux

mac:
	mkdir -p $(BUILD_DIR)
	clang *.c -Wall --std=c99 -L lib/mac-osx -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL lib/mac-os -o $(BUILD_DIR)pong-c-macos

clean:
	rm $(BUILD_DIR)/*
