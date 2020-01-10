SDL = -lGL -lSDL2 -I /usr/include/SDL2/ -D_REENTRANT -L/usr/lib -pthread -lm

plants: main.o ls.o sdl.o
	gcc $(SDL) $? -o plants

main.o : main.c
	gcc $(SDL) -c $^

ls.o: ls.c
	gcc $(SDL) -c $^

sdl.o: sdl.c
	gcc $(SDL) -c $^

clean: 
	rm -f *.o plants
