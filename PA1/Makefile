WARNINGFLAGS = -Wall -Wshadow -Wvla --pedantic
GCC = gcc -g -std=c99 $(WARNINGFLAGS)
VAL = valgrind --leak-check=full --leak-check=full --show-leak-kinds=all

SRCS = shell_array.c shell_list.c pa1.c
OBJS = $(SRCS:%.c=%.o)

pa1: $(OBJS) 
	$(GCC) $(OBJS) -o pa1

.c.o: 
	$(GCC) -c $*.c 

testmemory: pa1
	$(VAL) --log-file=memcheck1.txt ./pa1 -l examples/1K.b output1Kl

test1a: pa1
	./pa1 -a examples/1K.b output1Ka
	diff output1Ka examples/1Ksa.b

test1l: pa1
	./pa1 -l examples/1K.b output1Kl
	diff output1Kl examples/1Ksl.b

test2a: pa1
	./pa1 -a examples/15.b output15a
	diff output15a examples/15sa.b

test2l: pa1
	./pa1 -l examples/15.b output15l
	diff output15l examples/15sl.b

test3a: pa1
	./pa1 -a examples/1M.b output1Ma

test3l: pa1
	./pa1 -l examples/1M.b output1Ml

clean: # remove all machine generated files
	rm -f pa1 *.o output???
push:
	git push origin master
