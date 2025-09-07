# lsusb for macOS

This is a lightweight macOS implementation of the `lsusb` command, similar to the Linux `usbutils` package.  
It uses Apple's **IOKit** framework to list connected USB devices.

## Features
- Lists USB devices with **Vendor ID**, **Product ID**, and **Product Name**.
- Installs as `lsusb` in `/usr/local/bin` so it behaves like Linux.
- Includes a manual page (`man lsusb`).
- Simple Makefile for build, install, uninstall.

## Build & Install

Clone and build:

```bash
make build
sudo make install
```

Example output:
```
Bus 000 Device 000: ID 05ac:8290 Apple Inc. iPhone
Bus 000 Device 000: ID 0bda:8153 Realtek USB 10/100/1000 LAN
Bus 000 Device 000: ID 046d:c534 Logitech USB Receiver
```


