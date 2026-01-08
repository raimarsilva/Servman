CC = gcc
TARGET = servman

GTK_CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0)

SYSTEMD_CFLAGS := $(shell pkg-config --cflags libsystemd)
SYSTEMD_LIBS := $(shell pkg-config --libs libsystemd)

# CFLAGS para usar durante release
#CFLAGS = -Wall -Wextra -std=c11 -Iapp -Igui $(GTK_CFLAGS) $(SYSTEMD_CFLAGS)

# CFLAGS para usar durante desenvolvimento e debuging com ~$gdb [./appname] >>run,s >>bt
CFLAGS = -Wall -Wextra -g -O0 -std=c11 -Iapp -Igui $(GTK_CFLAGS) $(SYSTEMD_CFLAGS)
LDFLAGS = $(GTK_LIBS) $(SYSTEMD_LIBS)


SRC = main.c app/listing.c gui/window.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
