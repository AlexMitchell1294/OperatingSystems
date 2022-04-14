object = generation prolific

all: $(object)

prolific: prolific.c
	gcc -g -o prolific prolific.c

generation: generation.c
	gcc -g -o generation generation.c

.PHONY: clean

clean:
	-rm $(object)
