CC=g++
CFLAGS = -I. \
				-I/usr/include/SDL2 \
				-std=c++0x 

LIBS= -lstdc++ \
			-lSDL2 \
			-lSDL2_ttf \
			-lSDL2_image

DEPS = Enemy.h \
			MovingItem.h \
			SDL_Main.h \
			Character.h

OBJ = Enemy.o MovingItem.o Character.o SDL_Main.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

catwalk: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm -f *.o *~ catwalk core
