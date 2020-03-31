WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
VAL = valgrind --leak-check=full --leak-check=full --show-leak-kinds=all
GCC = gcc -O3 -std=c99 $(WARNINGFLAGS)

SRCS = hbt.c pa4.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS) 
	$(GCC) $(OBJS) -o pa4

.c.o: 
	$(GCC) -c $*.c 

testeval: test1e test2e test3e

testmemory: pa4
	$(VAL) --log-file=memcheck1.txt ./pa4 -b examples-2/ops0.b tree0b

test1b: pa4
	./pa4 -b examples-2/ops3.b tree0b
	diff examples-2/tree0.b tree0b

test1e: pa4
	./pa4 -e examples-2/invalidtree0.b

test2e: pa4
	./pa4 -e examples-2/invalidtree1.b

test3e: pa4
	./pa4 -e examples-2/invalidtree2.b

test: pa3
	./pa3 examples/1K.po KOutputpr KOutputdi KOutputpc

test4: pa3
	./pa3 examples/empty.po EOutputpr EOutputdi EOutputpc

clean: # remove all machine generated files
	rm -f pa4 *.o tree??
