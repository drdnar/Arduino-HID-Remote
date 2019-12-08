#include "HIDRemote.h"

static const uint8_t _hidRemoteReportDescriptor[] PROGMEM =
{
    /* These usage ID's come from the USB HID Usage Tables Consumer Page (0x0C)
     * See USB HID Usage Tables Version 1.12 chapter 15 Consumer Page (page 77)
     * for additional values you could specify. */
    0x05, 0x0c,                    // Usage Page (Consumer Devices)
    0x09, 0x01,                    // Usage (Consumer Control)
    0xa1, 0x01,                    // Collection (Application)
    0x85, 0x04,                    //   REPORT_ID (4)
    0x15, 0x00,                    //   Logical Minimum (0)
    0x25, 0x01,                    //   Logical Maximum (1)

    0x19, 0xb0,                    //   Usage Minimum (Play)
    0x29, 0xb9,                    //   Usage Maximum (Random Play)
    0x75, 0x01,                    //   Report Size (1)
    0x95, 0x0A,                    //   Report Count (10)
    0x81, 0x06,                    //   Input (Data, Variable, Relative)

    0x09, 0xe9,                    //   Usage (Volume Up)
    0x09, 0xea,                    //   Usage (Volume Down)
    0x75, 0x01,                    //   Report Size (1)
    0x95, 0x02,                    //   Report Count (2)
    0x81, 0x06,                    //   Input (Data, Variable, Relative)

    0x09, 0x32,                    //   Usage (Sleep)
    0x95, 0x01,                    //   Report Count (1)
    0x81, 0x06,                    //   Input (Data, Variable, Relative)

    0x09, 0xbc,                    //   Usage (Repeat)
    0x95, 0x01,                    //   Report Count (1)
    0x81, 0x06,                    //   Input (Data, Variable, Relative)

    0x09, 0xcd,                    //   Usage (Play/Pause)
    0x95, 0x01,                    //   Report Count (1)
    0x81, 0x06,                    //   Input (Data, Variable, Relative)

    0x09, 0xe2,                    //   Usage (Mute)
    0x95, 0x01,                    //   Report Count (1)
    0x81, 0x06,                    //   Input (Data, Variable, Relative)

    /* If you have a number of bits that isn't a multiple of eight, you need to add
     * padding.
     * Be careful when adding extra fields to the descriptor, there seems to be a
     * length limit somewhere after 77 bytes. */
    /*0x95, 0x01,                    //   Report Count (1) Number of bits remaining in byte
    0x81, 0x07,                    //   Input (Constant, Variable, Relative) */
    0xc0,                          // End Collection
};

HIDRemote_::HIDRemote_(void)
{
    static HIDSubDescriptor node(_hidRemoteReportDescriptor, sizeof(_hidRemoteReportDescriptor));
    HID().AppendDescriptor(&node);
}
 
void HIDRemote_::begin(void) 
{
    report.keys[0] = 0;
    report.keys[1] = 0;
}
 
void HIDRemote_::end(void) 
{
}

void HIDRemote_::sendReport(RemoteReport* r)
{
    HID().SendReport(4, r, sizeof(RemoteReport));
}

void HIDRemote_::sendReport()
{
    HID().SendReport(4, &report, sizeof(RemoteReport));
}

void HIDRemote_::pressAndRelease(uint16_t key)
{
    press(key);
    release(key);
}

void HIDRemote_::press(uint16_t key)
{
    report.keys[0] |= key;
    report.keys[1] |= (key >> 8);
    sendReport();
}

void HIDRemote_::release(uint16_t key)
{
    report.keys[0] &= ~key;
    report.keys[1] &= ~(key >> 8);
    sendReport();
}

void HIDRemote_::releaseAll(void)
{
    report.keys[0] = 0;
    report.keys[1] = 0;
    sendReport();
}

HIDRemote_ HIDRemote;
