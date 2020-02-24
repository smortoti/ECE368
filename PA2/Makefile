WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
VAL = valgrind --dsymutil=yes --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all --track-origins=yes
GCC = gcc -g -std=c99 $(WARNINGFLAGS)

SRCS = hufftree.c pa2.c
OBJS = $(SRCS:%.c=%.o)

pa2: $(OBJS) 
	$(GCC) $(OBJS) -o pa2

.c.o: 
	$(GCC) -c $*.c 

test1: pa2
	./pa2  original/gophers freqOutput1 headOutput1 codeOutput1 treeOutput1
	diff count/gophers.count freqOutput1 
	# diff tree/gophers.tree headOutput1 
	diff code/gophers.code codeOutput1

checkFreq:
	diff count/gophers.count freqOutput1

test2: pa2
	./pa1 -l examples/1K.b output1Kl

test2a: pa1
	./pa1 -a examples/15.b output15a
	diff output15a examples/15sa.b

test2l: pa1
	./pa1 -a examples/15.b output15l
	diff output15l examples/15sa.b

test1M: pa1
	./pa1 -a examples/1M.b output1Ma

clean: # remove all machine generated files
	rm -f pa1 *.o ????Output?