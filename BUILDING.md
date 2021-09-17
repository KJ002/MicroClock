# Building

Building the hex for the uBit from source will require you to setup the offline development toolchain from the lancaster university, compile the code with yotta and flash the hex to the uBit.

- Setup the [offline development toolchain](https://lancaster-university.github.io/microbit-docs/offline-toolchains/)
- Running `yt build` will compile the code into a hex file located under `MicroClock/build/bbc-microbit-classic-gcc/source/microclock-combined.hex`
- Assuming the uBit is mounted on `/media/microbit` you may run the following command to flash the hex to the uBit `sudo cp ./MicroClock/build/bbc-microbit-classic-gcc/source/microclock-combined.hex /media/microbit`
- You may have to remount the uBit for the changes to take effect, this can be done with the following command `sudo mount -o remount,rw /dev/sde /media/microbit`
