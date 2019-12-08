#ifndef HID_REMOTE_H
#define HID_REMOTE_H

#include "HID.h"

#define HID_REMOTE_PLAY 1
#define HID_REMOTE_PAUSE 2
#define HID_REMOTE_RECORD 4
#define HID_REMOTE_FAST_FORWARD 8
#define HID_REMOTE_REWIND 0x10
#define HID_REMOTE_NEXT 0x20
#define HID_REMOTE_PREVIOUS 0x40
#define HID_REMOTE_STOP 0x80
#define HID_REMOTE_EJECT 0x100
#define HID_REMOTE_RANDOM 0x200
#define HID_REMOTE_VOLUME_UP 0x400
#define HID_REMOTE_VOLUME_DOWN 0x800
#define HID_REMOTE_SLEEP 0x1000
#define HID_REMOTE_REPEAT 0x2000
#define HID_REMOTE_PLAY_PAUSE 0x4000
#define HID_REMOTE_MUTE 0x8000

#define REMOTE_REPORT_LENGTH 2

typedef struct {
    uint8_t keys[REMOTE_REPORT_LENGTH];
} RemoteReport;

class HIDRemote_
{
private:
    RemoteReport report;
    void sendReport(RemoteReport* report);
    void sendReport(void);
public:
  HIDRemote_(void);
    void begin(void);
    void end(void);
    void press(uint16_t key);
    void release(uint16_t key);
    void pressAndRelease(uint16_t key);

    // Send an empty report to prevent repeated actions
    void releaseAll(void);
};
extern HIDRemote_ HIDRemote;

#endif // HID_REMOTE_H
