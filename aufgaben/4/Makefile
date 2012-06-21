MEASUREDIR = /home/y0025529

CC = mpicc
CFLAGS = -O3 -Wall -std=gnu99 -I$(MEASUREDIR) -g
LDFLAGS = -lrt -lm

executable: executable.o
	$(CC) $(LDFLAGS) $^ -o $@

executable.o: program.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o

cleanall: clean
	rm -f executable

cleanmeasure:
	rm $(MEASUREDIR)/measure_processtime.o
