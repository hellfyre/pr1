CC = gcc
CFLAGS = -O3 -Wall -std=gnu99 -g
LDFLAGS = -lrt -lm

program: program.o planets.o drawcircle.o gettime.o
	$(CC) $^ -o $@ $(LDFLAGS)

program.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

bitmap.o: bitmap.c
	$(CC) $(CFLAGS) -o $@ -c $<

planets.o: planets.c
	$(CC) $(CFLAGS) -o $@ -c $<

drawcircle.o: drawcircle.c
	$(CC) $(CFLAGS) -o $@ -c $<

gettime.o: gettime.c
	$(CC) $(CFLAGS) -o $@ -c $<

video: images/*.bmp
	~/bin/ffmpeg -b 1800 -r 10 -i images/planets%d00.bmp images/video.mp4

clean:
	rm -f *.o

cleanvideo:
	rm -f images/planets*.bmp images/video.mp4

cleanall: clean cleanvideo
	rm -f executable
