#include "MicroBit.h"

MicroBit uBit;

int main()
{
	uBit.init();

	 const uint8_t heart[] = { 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0}; // a cute heart
	 MicroBitImage i(5,5,heart);

	while (true){
		uBit.display.print(i);
		uBit.sleep(500);
	}

	release_fiber();
	return 0;
}
