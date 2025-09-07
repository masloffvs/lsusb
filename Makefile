CC = clang
CFLAGS = -Wall -O2
FRAMEWORKS = -framework IOKit -framework CoreFoundation
TARGET = lsusb_mac
PREFIX = /usr/local
MANDIR = $(PREFIX)/share/man/man1

all: $(TARGET)

build: all

$(TARGET): lsusb_mac.c
	$(CC) $(CFLAGS) lsusb_mac.c -o $(TARGET) $(FRAMEWORKS)

install: $(TARGET)
	install -d $(PREFIX)/bin
	install -m 755 $(TARGET) $(PREFIX)/bin/lsusb
	install -d $(MANDIR)
	install -m 644 lsusb.1 $(MANDIR)/lsusb.1
	@echo "Installed lsusb to $(PREFIX)/bin and man page to $(MANDIR)"

uninstall:
	rm -f $(PREFIX)/bin/lsusb
	rm -f $(MANDIR)/lsusb.1
	@echo "Uninstalled lsusb and man page"

clean:
	rm -f $(TARGET)

