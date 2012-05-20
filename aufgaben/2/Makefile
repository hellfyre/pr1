MEASUREDIR = /home/y0025529

CC = mpicc
CFLAGS = -O3 -Wall -std=gnu99 -I$(MEASUREDIR) -g
LDFLAGS = -lrt

ex4: ex4.o $(MEASUREDIR)/measure_processtime.o
	$(CC) $(LDFLAGS) $^ -o $@

ex4.o: ex4.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex3: ex3.o $(MEASUREDIR)/measure_processtime.o
	$(CC) $(LDFLAGS) $^ -o $@

ex3.o: ex3.c
	$(CC) $(CFLAGS) -o $@ -c $<

ex2: ex2.o $(MEASUREDIR)/measure_processtime.o
	$(CC) $(LDFLAGS) $^ -o $@

ex2.o: ex2.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(MEASUREDIR)/measure_processtime.o: $(MEASUREDIR)/measure_processtime.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

cleanall: clean
	rm -f ex2
	rm -f ex3
	rm -f ex4

cleanmeasure:
	rm $(MEASUREDIR)/measure_processtime.o
