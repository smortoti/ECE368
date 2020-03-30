WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
VAL = valgrind --leak-check=full --leak-check=full --show-leak-kinds=all
GCC = gcc -g -O3 -std=c99 $(WARNINGFLAGS)

SRCS = hbt.c pa4.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS) 
	$(GCC) $(OBJS) -o pa3

.c.o: 
	$(GCC) -c $*.c 

testall: test1 test2 test3

testmemory: pa3
	$(VAL) --log-file=memcheck1.txt ./pa3 examples/empty.po 3Outputpr 3Outputdi 3Outputpc

test1: pa4
	./pa4 examples/3.po 3Outputpr 3Outputdi 3Outputpc
	diff examples/3.pr 3Outputpr 
	diff examples/3.dim 3Outputdi
	diff examples/3.pck 3Outputpc

test2: pa3
	./pa3 examples/8.po 8Outputpr 8Outputdi 8Outputpc
	diff examples/8.pr 8Outputpr 
	diff examples/8.dim 8Outputdi
	diff examples/8.pck 8Outputpc

test3: pa3
	./pa3 examples/1K.po KOutputpr KOutputdi KOutputpc

test4: pa3
	./pa3 examples/empty.po EOutputpr EOutputdi EOutputpc

clean: # remove all machine generated files
	rm -f pa3 *.o ?Output??