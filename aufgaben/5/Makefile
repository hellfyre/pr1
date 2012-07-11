CC = mpicc
CFLAGS = -O0 -Wall -std=gnu99
LDFLAGS = -lrt -lm

program: program.o planets.o drawcircle.o
	$(CC) $^ -o $@ $(LDFLAGS)

program.o: main.c
	$(CC) $(CFLAGS) -o $@ -c $<

bitmap.o: bitmap.c
	$(CC) $(CFLAGS) -o $@ -c $<

planets.o: planets.c
	$(CC) $(CFLAGS) -o $@ -c $<

drawcircle.o: drawcircle.c
	$(CC) $(CFLAGS) -o $@ -c $<

all: cleanvideo program
	./program
	/usr/bin/ffmpeg -b 1800 -r 3 -i images/planets%03d.bmp images/video.mp4
	mplayer -fs images/video.mp4

video: images/*.bmp
	/usr/bin/ffmpeg -b 1800 -r 3 -i images/planets%03d.bmp images/video.mp4

clean:
	rm -f *.o

cleanvideo:
	rm -f images/planets*.bmp images/video.mp4

cleanall: clean cleanvideo
	rm -f executable
