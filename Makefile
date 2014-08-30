CC=g++
CFLAGS=-g -ggdb -Wall
LDFLAGS=-framework OpenCL
OBJECTS=main.o platform.o

all: devices

devices: $(OBJECTS)
	$(CC) -o devices $(LDFLAGS) $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -rf $(OBJECTS)
	rm -rf devices
