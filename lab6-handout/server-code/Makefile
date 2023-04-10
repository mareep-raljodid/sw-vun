FLAGS    = -z execstack 
FLAGS_32 = -static -m32
TARGET   = server format-32
 
L = 100

all: $(TARGET)

server: server.c
	gcc -o server server.c

format-32: format.c
	gcc -DBUF_SIZE=$(L) $(FLAGS) $(FLAGS_32) -o $@ format.c

clean:
	rm -f badfile $(TARGET)
	rm -f ../fmt-containers/server
	rm -f ../fmt-containers/format-32

install:
	cp server ../fmt-containers
	cp format-* ../fmt-containers

