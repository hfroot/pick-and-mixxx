# Arduino MIDI

Goals (in order of feasibility/priority):
- an arduino midi deck that can be mapped to mixxx software
- a midi deck with an integrated raspberry pi, making the set more portable
- a pretty case to hold it all together, ideally wooden
- battery-powered integrated mixing deck
- nicely organised library so that anyone can mix and match the arduino code to fit their hardware set up
- nicely documented, tutorialised repo

## What I'm working with

- Linux Fedora
- Arduino software
- Arduino MKR 1010 (chosen for no particular reason other than that was the one I had lying around)
- Mixxx (chosen because I was already using this particular software)

## Photos

https://drive.google.com/drive/folders/1-30mevmbbR7FQFWHTCHeHI3Pf1oLUQ9v?usp=share_link

## Hooking up a button

Example code
Schematic (took a second to figure out the right pins on the switch)
Permission error (wasn't enough to log out then in after user group change, had to restart computer)

www.varal.org/ttymidi/ (download then follow compilation instructions in README)
Fedora's equivalent of the dependent library
 - (sudo) yum install alsa-lib-devel (https://www.reddit.com/r/linuxquestions/comments/pwxa8u/libasound2dev_on_fedora/) (https://yum-info.contradodigital.com/view-package/installed/alsa-lib/)

then I ran in the terminal

`ttymidi -s /dev/ttyACM0 -v` with the code running in the arduino being post 6 https://forum.arduino.cc/t/arduino-and-mixxx-midi-how-to-control-mixxx-with-arduino-solved/577884/5

With that command running, open Mixxx > Options > Preferences > Controllers. Should see a controller there.

When re-uploading code to the arduino, 

- quit mixxx
- kill the ttymidi command

Otherwise I found that the location /dev/ttyACM0 would change and mixxx wouldn't be able to detect the device. It's not the end of the world if it does. Either re run the ttymidi command with the new location, or re-upload once the command is killed and the location will be restored to the original one.

Using the mixxx learning wizard, I mapped the button press to a headphone button. AND IT WORKED. Press 50 million times for extra satisfaction. Save the mapping without adding other controls. If after a reupload of code you lose the functionality, you might have to go back into the mixxx controller settings. You should find your new mapping in the Load mapping menu.

For fun, made a 'button as knob' feature. This allows you to press and hold a button to adjust a slider between 0 and 127. Releasing and then pressing and holding again will change the direction of the slider. Double press-then-hold continues in the direction you were going. Used the terminal for fine tuning in terms of speed, increment of change, double-press time delay..., then moved over to mixxx to map. Needed to restart the program to get it to register the new button type.

Probs took 3.5 hrs to get to this point.

https://www.youtube.com/watch?v=U9olJK3RYXg&list=PL4_gPbvyebyH2xfPXePHtx8gK5zPBrVkg&index=8
https://docs.arduino.cc/tutorials/generic/midi-device?_gl=1*18l1roo*_ga*MTIwMjY4Nzk2MS4xNjY3Mzg4MzMx*_ga_NEXN8H46L5*MTY2NzM4ODMzMS4xLjEuMTY2NzM5MjMwMC4wLjAuMA..
https://manual.mixxx.org/2.3/en/chapters/advanced_topics.html#advanced-controller


## VSCode

As much as I love Arduino, their IDE makes me want to cry, especially now that I am used to the delights of VSCode.

So let's switch to programming the Arduino through VSCode.

- In VSCode, install the Arduino extension
- Make sure C/C++ extension is installed too (for me it was already)
    - Ctrl - shift - p now has lots of Arduino-related commands, all prefixed with `Arduino:`
- If you have errors with your include commands: I had to copy all the paths into `includePath` in `.vscode/c_cpp_properties.json` from the `Arduino` configuration into my `Linux` configuration
- I selected the same Serial port and Programmer that my Arduino IDE used (`/dev/ttyACMO` and `AVRISP mkll` respectively)
- Added to the C properties JSON `"defines": ["USBCON"]` to fix the `Serial` error
- I ignored the error VSCode highlights on `MIDI_CREATE_INSTANCE`
- Verify
- Upload
- Run the midi terminal command
- Open Mixxx