MEASUREDIR = /home/y0025529

CC = mpicc
CFLAGS = -O3 -Wall -std=gnu99 -I$(MEASUREDIR) -g
LDFLAGS = -lrt -lm

executable: executable.o bitmap.o visualize.o gettime.o
	$(CC) $(LDFLAGS) $^ -o $@

executable.o: program.c
	$(CC) $(CFLAGS) -o $@ -c $<

bitmap.o: bitmap.c
	$(CC) $(CFLAGS) -o $@ -c $<

visualize.o: visualize.c
	$(CC) $(CFLAGS) -o $@ -c $<

gettime.o: gettime.c
	$(CC) $(CFLAGS) -o $@ -c $<

video: images/*.bmp
	~/bin/ffmpeg -b 1800 -r 10 -i images/heatmap%d00.bmp images/video.mp4

clean:
	rm -f *.o

cleanvideo:
	rm -f images/heatmap*.bmp images/video.mp4

cleanall: clean cleanvideo
	rm -f executable
