CC=g++
CFLAGS = \
				-std=c++11 \
				-Wall \
				-Wpedantic \
				-Wextra \
				-g

INCLUDES= -I. \
					-I/usr/include/SDL2

LIBS= -lstdc++ \
			-lSDL2 \
			-lSDL2_ttf \
			-lSDL2_image

DEPS = Enemy.h \
			MovingItem.h \
			SDL_Main.h \
			Utils.h \
			Character.h \
			MenuState.h \
			IState.h

OBJ = Utils.o IState.o Enemy.o MenuState.o MovingItem.o Character.o SDL_Main.o main.o

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

catwalk: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(INCLUDES) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o *~ catwalk core
