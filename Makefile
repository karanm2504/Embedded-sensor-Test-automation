CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror

SOURCE := firmware_sim/src/sensor_simulator.c
TARGET := build/sensor_simulator

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) normal

clean:
	rm -f $(TARGET)