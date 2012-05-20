MEASUREDIR = /home/y0025529

CC = mpicc
CFLAGS = -O3 -Wall -std=gnu99 -I$(MEASUREDIR) -g
LDFLAGS = -lrt

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

cleanmeasure:
	rm $(MEASUREDIR)/measure_processtime.o
