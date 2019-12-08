# Arduino-HID-Remote
The Arduino library already has support for acting as keyboard or mouse, but not media control buttons like play/pause and volume control. This Arduino skectch is about the simplest way to add such functionality. (A USB-capable Arduino like the Leonardo is obviously required.) Other libraries provide more flexibility, but are also more complicated to use and may generate larger code. The file `hid_remote.ino` contains a fully working example, using a simple keyboard matrix. (The random-seeming row and column pin assignments are just because that's what routing I happened to use on my board.)

Due to the way the USB HID specifies how multimedia buttons works, support for them can't be trivially incorporated into a keyboard device. Instead, you have to add a new report and descriptor. Fortunately, at some point the Arduino USB library got rewritten to make doing that quite easy.

This code is inspired by [this Stefan Jones blog post.](https://www.stefanjones.ca/blog/arduino-leonardo-remote-multimedia-keys/) However, his example predates the rewrite of the Arduino USB HID API, so I had to modify it to work with the new API. Ultimately, I ended up pretty much rewriting all the code completely. Even my descriptor is completely different. 

### Usage

Add the `HIDRemote.h` and `HIDRemote.cpp` files to you sketch folder and place `#include "HIDRemote.h"` at the top of your sketch.

In your `setup()` routine, add `HIDRemote.begin();` at some point.

The actual API mirrors the usage of the `Keyboard` library. There are `HIDRemote.press()` and `HIDRemote.release()` routines to simulate pressing and releasing keys, as well as `HIDRemote.releaseAll()` and `HIDRemote.pressAndRelease()`.

The following constants can be passed to `press` or `release`. Some or all of these may have no effect on your particular operating system or application. **Note that they are 16-bit** i.e. use `uint16_t`.

* `HID_REMOTE_PLAY` Play button; if media is already playing, should have no effect.
* `HID_REMOTE_PAUSE` Pause button; if no media is playing, should have no effect.
* `HID_REMOTE_RECORD` Record key, to start recording
* `HID_REMOTE_FAST_FORWARD` Fast-forward
* `HID_REMOTE_REWIND` Rewind
* `HID_REMOTE_NEXT` Skip to next track
* `HID_REMOTE_PREVIOUS` Skip to previous track
* `HID_REMOTE_STOP` Stop media playback
* `HID_REMOTE_EJECT` Eject media
* `HID_REMOTE_RANDOM` Select randomized track playback order
* `HID_REMOTE_VOLUME_UP` Increment volumne
* `HID_REMOTE_VOLUME_DOWN` Decrement volumne
* `HID_REMOTE_SLEEP` Enter sleep mode
* `HID_REMOTE_REPEAT` Activate track or playlist repeating
* `HID_REMOTE_PLAY_PAUSE` Play/pause button; if media playing, pause playback; if media is paused, resume playback
* `HID_REMOTE_MUTE` Mute/unmute volumne

You can change what buttons are available by changing the descriptor in `HIDRemote.cpp`. Remember to change the constants in `HIDRemote.h` to match.
