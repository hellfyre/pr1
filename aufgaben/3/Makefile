MEASUREDIR = /home/y0025529

CC = mpicc
CFLAGS = -O3 -Wall -std=gnu99 -I$(MEASUREDIR) -g
LDFLAGS = -lrt -lm

ex1d: ex1d.o
	$(CC) $(LDFLAGS) $^ -o $@

ex1d.o: ex1d.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex1c: ex1c.o
	$(CC) $(LDFLAGS) $^ -o $@

ex1c.o: ex1c.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex1b: ex1b.o
	$(CC) $(LDFLAGS) $^ -o $@

ex1b.o: ex1b.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex1a: ex1a.o
	$(CC) $(LDFLAGS) $^ -o $@

ex1a.o: ex1a.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

cleanall: clean
	rm -f ex1c
	rm -f ex1b
	rm -f ex1a

cleanmeasure:
	rm $(MEASUREDIR)/measure_processtime.o
