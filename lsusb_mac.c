#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>
#include <IOKit/usb/IOUSBLib.h>
#include <IOKit/usb/USB.h>

int main() {
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    io_iterator_t iter;
    io_service_t device;

    if (IOServiceGetMatchingServices(kIOMainPortDefault, matchingDict, &iter) != KERN_SUCCESS) {
        fprintf(stderr, "Failed to get USB devices\n");
        return 1;
    }

    while ((device = IOIteratorNext(iter))) {
        CFNumberRef vendorIdRef = (CFNumberRef)IORegistryEntryCreateCFProperty(device,
                                  CFSTR(kUSBVendorID), kCFAllocatorDefault, 0);
        CFNumberRef productIdRef = (CFNumberRef)IORegistryEntryCreateCFProperty(device,
                                   CFSTR(kUSBProductID), kCFAllocatorDefault, 0);
        CFStringRef productName = (CFStringRef)IORegistryEntryCreateCFProperty(device,
                                   CFSTR(kUSBProductString), kCFAllocatorDefault, 0);

        int vendorId = 0, productId = 0;
        if (vendorIdRef) CFNumberGetValue(vendorIdRef, kCFNumberIntType, &vendorId);
        if (productIdRef) CFNumberGetValue(productIdRef, kCFNumberIntType, &productId);

        char name[256];
        if (productName) {
            CFStringGetCString(productName, name, sizeof(name), kCFStringEncodingUTF8);
        } else {
            snprintf(name, sizeof(name), "Unknown");
        }

        printf("Bus 000 Device 000: ID %04x:%04x %s\n", vendorId, productId, name);

        if (vendorIdRef) CFRelease(vendorIdRef);
        if (productIdRef) CFRelease(productIdRef);
        if (productName) CFRelease(productName);

        IOObjectRelease(device);
    }

    IOObjectRelease(iter);
    return 0;
}

