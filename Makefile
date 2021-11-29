exec = baltoc
srcs = $(wildcard src/*.c)
objs = $(srcs:.c=.o)
flags = -g -Wall -lm -fPIC

$(exec): $(objs)
	gcc $(objs) $(flags) -o $(exec)
%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

clean: 
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.o
	-rm 
