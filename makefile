objects := $(patsubst src%, bin%, $(patsubst %.c,%.o,$(wildcard src/*.c)))
headers := $(wildcard src/*.h)

CFLAGS = -Wall -Wextra
LDFLAGS = -Wl,-rpath=/usr/local/lib -Wl,--enable-new-dtags -lSDL2 -lm

notationaloptics : $(objects) $(headers)
	gcc $(objects) $(headers) -o bin/notationaoptics $(LDFLAGS) $(CFLAGS)

bin/%.o : src/%.c
	gcc -c $< -o $@ $(CFLAGS)


