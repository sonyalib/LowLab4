CC = gcc
CFLAGS = -std=c89 -pedantic-errors -Wall -Werror

default: main1.out

main1.out: main1.o linked_list.o
	gcc main1.o linked_list.o -o main1.out

main2.out: main2.o linked_list.o higher_order.o
	gcc main2.o linked_list.o higher_order.o -o main2.out

run: main1.out
	./main1.out

clean:
	rm -f *.o *.out

%.o: %.c
	$(CC) $(CFLAGS) $*.c -c -o $*.o
