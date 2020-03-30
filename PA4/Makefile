WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
VAL = valgrind --leak-check=full --leak-check=full --show-leak-kinds=all
GCC = gcc -O3 -std=c99 $(WARNINGFLAGS)

SRCS = hbt.c pa4.c
OBJS = $(SRCS:%.c=%.o)

pa4: $(OBJS) 
	$(GCC) $(OBJS) -o pa4

.c.o: 
	$(GCC) -c $*.c 

testall: test1 test2 test3

testmemory: pa4
	$(VAL) --log-file=memcheck1.txt ./pa4 -b examples-2/ops0.b tree0b

test1b: pa4
	./pa4 -b examples-2/ops0.b tree0b

test1e: pa4
	./pa4 -e examples-2/ops0.b tree0e

test3: pa3
	./pa3 examples/1K.po KOutputpr KOutputdi KOutputpc

test4: pa3
	./pa3 examples/empty.po EOutputpr EOutputdi EOutputpc

clean: # remove all machine generated files
	rm -f pa4 *.o tree??
