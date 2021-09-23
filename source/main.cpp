#include "MicroBit.h"
#include "vec2.hpp"
#include <cmath>

#define MAP_X 5
#define MAP_Y 5
#define MAP0_X 4
#define MAP0_Y 4

#define uMin 166.68
#define uHour 1000


MicroBit uBit;

int Vec2Position(Vec2 position){

	position = {(float)round(position.x+1), (float)round(position.y+1)};

	int deltaY = MAP_Y - position.y;
	deltaY *= MAP_Y;

	return deltaY + position.x - 1;
}

uint8_t * Vec2uBitImage(Vec2 start, Vec2 end, float th = 0){

	start = start.round();
	end = end.round().rotate(th, start);

	static uint8_t matrix[MAP_X*MAP_Y] = {};

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;

	Vec2 delta = end - start;
	float step;

	if (std::abs(delta.x) >= std::abs(delta.y))
		step = std::abs(delta.x);

	else
		step = std::abs(delta.y);

	delta = delta / (Vec2){step, step};

	Vec2 pos = start;

	for (int i = 0; i<=step; i++){
		matrix[Vec2Position(pos)] = 1;
		pos.x += delta.x;
		pos.y += delta.y;
	}

	matrix[Vec2Position(end)] = 1;

	return matrix;
}


int main()
{
	uBit.init();

	float rotation = 0;

	uint8_t * data;

	MicroBitImage k;

	while (true){
		data = Vec2uBitImage((Vec2){2, 2}, (Vec2){2, 4}, rotation);
		k = MicroBitImage(5, 5, data);
		uBit.display.print(k);
		uBit.sleep(uMin);
		rotation++;
	}

	release_fiber();
	return 0;
}
