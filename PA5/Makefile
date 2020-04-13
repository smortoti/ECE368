WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
VAL = valgrind --leak-check=full --leak-check=full --show-leak-kinds=all
GCC = gcc -O3 -std=c99 $(WARNINGFLAGS)

SRCS = sorting.c pa5.c
OBJS = $(SRCS:%.c=%.o)

pa5: $(OBJS) 
	$(GCC) $(OBJS) -o pa5

.c.o: 
	$(GCC) -c $*.c 

testmerge: test1m test2m test3m

testquick: test1q test2q test3q

testmemorymerge: pa5
	$(VAL) --log-file=memcheck1.txt ./pa5 -m examples/10.b output10

testmemoryquick: pa5
	$(VAL) --log-file=memcheck1.txt ./pa5 -q examples/10.b output10

test1m: pa5
	./pa5 -m examples/10.b output10m

test1q: pa5
	./pa5 -q examples/10.b output10q

test2m: pa5
	./pa5 -m examples/1K.b output1Km

test2q: pa5
	./pa5 -q examples/1K.b output1Kq

test3m: pa5
	./pa5 -m examples/1M.b output1Mm

test3q: pa5
	./pa5 -q examples/1M.b output1Mq

clean: # remove all machine generated files
	rm -f pa5 *.o output???
