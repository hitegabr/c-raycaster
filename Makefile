CC = gcc
CFLAGS = -Wall
LDFLAGS = -lSDL2 -lm
TARGET = raycaster

all: $(TARGET)

$(TARGET): main.c rng.c map.c raycaster.c rng.h map.h raycaster.h
	$(CC) $(CFLAGS) main.c rng.c map.c raycaster.c -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
