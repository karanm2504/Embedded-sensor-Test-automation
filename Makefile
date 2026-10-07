CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror

SOURCE := firmware_sim/src/sensor_simulator.c
TARGET := build/sensor_simulator

.PHONY: all run test report clean

all: $(TARGET)

$(TARGET): $(SOURCE)
	mkdir -p build
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

run: $(TARGET)
	./$(TARGET) normal

test: $(TARGET)
	python3 -m unittest discover -s automation -p "test_*.py" -v

report: $(TARGET)
	python3 automation/run_tests.py
clean:
	rm -f $(TARGET)