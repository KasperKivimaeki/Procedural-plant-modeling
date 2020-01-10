CC = gcc

LDFLAGS = -g -Wall -Wextra -pthread -Wno-missing-field-initializers -lm
SDL = `sdl2-config --libs`

src = $(wildcard *.c)
obj = $(src:.c=.o)

exe = plants

all : $(exe)

clean :
	rm -f $(exe) *.o

%.o : %.c
	$(CC) $< $(LDFLAGS) $(SDL) -c

$(exe) : $(obj)
	$(CC) -o $@ $^ $(LDFLAGS) $(SDL)
