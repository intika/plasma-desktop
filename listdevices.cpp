#include <iostream>

#include <X11/Xlib.h>
#include <X11/extensions/XInput.h>

int main(void)
{
    Display *display = XOpenDisplay(0);
    int nDevices = 0;
    XDeviceInfo *devices = XListInputDevices(display, &nDevices);
    for (int i = 0; i < nDevices; i++) {
        const char *name = devices[i].name;
        char *type = 0;
        if (devices[i].type) {
            type = XGetAtomName(display, devices[i].type);
        }
        const char *use;
        switch (devices[i].use) {
        case IsXPointer: use = "Pointer"; break;
        case IsXKeyboard: use = "Keyboard"; break;
        case IsXExtensionDevice: use = "Extension Device"; break;
        case IsXExtensionPointer: use = "Extension Pointer"; break;
        case IsXExtensionKeyboard: use = "Extension Keyboard"; break;
        default: use = "Unknown";
        }
        std::cout << "Name: " << name << " Type: " << (type ? type : "unknown")
                  << " Use: " << use << std::endl;
        XFree(type);
    }
    XFreeDeviceList(devices);
    XCloseDisplay(display);
}
