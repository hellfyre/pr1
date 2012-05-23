MEASUREDIR = /home/y0025529

CC = mpicc
CFLAGS = -O3 -Wall -std=gnu99 -I$(MEASUREDIR) -g
LDFLAGS = -lrt

ex3: ex3.o $(MEASUREDIR)/measure_processtime.o
	$(CC) $(LDFLAGS) $^ -o $@

ex3.o: ex3.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex2: ex2.o $(MEASUREDIR)/measure_processtime.o
	$(CC) $(LDFLAGS) $^ -o $@

ex2.o: ex2.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex1: ex1.o $(MEASUREDIR)/measure_processtime.o
	$(CC) $(LDFLAGS) $^ -o $@

ex1.o: ex1.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(MEASUREDIR)/measure_processtime.o: $(MEASUREDIR)/measure_processtime.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

cleanall: clean
	rm -f ex1
	rm -f ex2
	rm -f ex3

cleanmeasure:
	rm $(MEASUREDIR)/measure_processtime.o
