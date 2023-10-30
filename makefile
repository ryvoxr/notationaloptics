objects := $(patsubst src%, bin%, $(patsubst %.c,%.o,$(wildcard src/*.c)))
headers := $(wildcard src/*.h)

CFLAGS = -Wall -Wextra
LDFLAGS = -Wl,-rpath=/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lm -lfreetype

notationaloptics : $(objects) $(headers)
	gcc $(objects) $(headers) -o bin/notationaoptics $(LDFLAGS) $(CFLAGS)

bin/text.o : src/text.c
	gcc -c $< -o $@ $(CFLAGS) $(shell pkg-config --cflags freetype2)

bin/%.o : src/%.c
	gcc -c $< -o $@ $(CFLAGS)

clean : 
	rm -f bin/*.o bin/notationaloptics

