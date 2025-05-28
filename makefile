CC = gcc
CFLAGS = -Wall -Wextra -I. `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs`

SRC = main.c planet.c
OBJ = $(SRC:.c=.o)
TARGET = solar_system

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
