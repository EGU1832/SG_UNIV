OBJECTS = fp1.o
SRC = fp1.c

CC = gcc
CFLAGS = -c -g
LDFLAGS = -g

TARGET = fp1

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

clean:
	rm $(OBJECTS) $(TARGET)
