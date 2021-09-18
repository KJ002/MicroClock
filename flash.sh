echo Building...
yt build
echo Built

echo Uploading...
sudo cp ./build/bbc-microbit-classic-gcc/source/microclock-combined.hex /media/microbit
echo Uploaded

echo Remounting
sudo mount -o remount,rw /dev/sdd /media/microbit
echo Remounted

echo Success!
