WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
VAL = valgrind --dsymutil=yes --tool=memcheck --leak-check=full --verbose --show-leak-kinds=all --track-origins=yes
GCC = gcc -g -std=c99 $(WARNINGFLAGS)

SRCS = packing.c pa3.c
OBJS = $(SRCS:%.c=%.o)

pa3: $(OBJS) 
	$(GCC) $(OBJS) -o pa3

.c.o: 
	$(GCC) -c $*.c 

testall: test1 test2 test4 test5 test6

test1: pa3
	./pa3 examples/3.po 3Outputpr 3Outputdi 3Outputpc
	diff examples/3.pr 3Outputpr 

test2: pa2
	./pa2 original/woods freqOutput2 headOutput2 codeOutput2 treeOutput2
	diff count/woods.count freqOutput2

test3: pa2
	./pa2 original/binary1 freqOutput3 headOutput3 codeOutput3 treeOutput3
	diff count/binary1.count freqOutput3

test4: pa2
	./pa2 original/stone freqOutput4 headOutput4 codeOutput4 treeOutput4
	diff count/stone.count freqOutput4

test5: pa2
	./pa2 original/lorum freqOutput5 headOutput5 codeOutput5 treeOutput5
	diff count/lorum.count freqOutput5

test6: pa2
	./pa2 original/empty freqOutput6 headOutput6 codeOutput6 treeOutput6
	diff count/empty.count freqOutput6

clean: # remove all machine generated files
	rm -f pa1 *.o ????Output?