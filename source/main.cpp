#include "MicroBit.h"
#include <cmath>

#define MAP_X 5
#define MAP_Y 5
#define MAP0_X 4
#define MAP0_Y 4

#define power2(x) (x*x)

float _round(float x){
	return floor(x+0.5);
}

struct Vec2{
	float x;
	float y;

	Vec2 operator+(const Vec2& other) const{
		return (Vec2){x+other.x, y+other.y};
	}

	Vec2 operator-(const Vec2& other) const{
		return (Vec2){x-other.x, y-other.y};
	}

	Vec2 operator*(const Vec2& other) const{
		return (Vec2){x*other.x, y*other.y};
	}

	Vec2 operator/(const Vec2& other) const{
		return (Vec2){x/other.x, y/other.y};
	}

	bool operator>(const Vec2& other) const{
		if ((x*y) > (other.x*other.y))
			return true;
		return false;
	}

	bool operator<(const Vec2& other) const{
		return !operator>(other);
	}

	double dotProduct(const Vec2& other) const{
		return x*other.x+y*other.y;
	}

	double crossProduct(const Vec2& other) const{
		return x+other.x*y+other.y;
	}

	Vec2 rotate(const double th) const{
		Vec2 result;

		result.x = cos(th) * this->x - sin(th) * this->y;
		result.y = sin(th) * this->x + sin(th) * this->y;

		return result;
	}

	Vec2 rotate(const double th, const Vec2& origin) const{
		Vec2 newPoint = *this - origin;

		return newPoint.rotate(th);
	}

	float length() const{
		return std::sqrt(power2(x) + power2(y));
	}
};

MicroBit uBit;

int Vec2Position(Vec2 position){

	int result;

	position = {(float)round(position.x+1), (float)round(position.y+1)};

	int deltaY = MAP_Y - position.y;
	deltaY *= MAP_Y;

	result = deltaY + position.x - 1;

	return result;
}

uint8_t * Vec2uBitImage(Vec2 start, Vec2 end){
	static uint8_t matrix[MAP_X*MAP_Y] = {};

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;

	Vec2 delta = end - start;
	float gradient = delta.y / delta.x;
	float y = start.y - (gradient * start.x);

	for (float x = start.x; x <= end.x; x+=0.25){
		matrix[Vec2Position((Vec2){x, std::floor((gradient * x) + y)})] = 1;
	}

	return matrix;

}

int main()
{
	uBit.init();

	uint8_t x[25] = {};

	const uint8_t * data = Vec2uBitImage((Vec2){2, 4}, (Vec2){3, 0});

	for (int i = 0; i < 25; i++)
		x[i] = *(data + i);

	MicroBitImage k(5, 5, x);
	while (true){
		uBit.display.print(k);
		uBit.sleep(500);
	}

	release_fiber();
	return 0;
}
