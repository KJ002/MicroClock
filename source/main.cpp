#include "MicroBit.h"
#include <cmath>
#include <vector>

#define MAP_X 5
#define MAP_Y 5
#define power2(x) (x*x)

int _round(float x){
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

int Vec2Position(Vec2 position, Vec2 matrix){
	int result = 0;

	result += (round(position.y) - 1) * round(matrix.x);
	result += round(position.x) - 1;
	return result;
}

MicroBitImage Vec2uBitImage(Vec2 start, Vec2 end){

	Vec2 delta = {(end.x - start.x)+1, (start.y - end.y)+1};
	float length = std::sqrt(power2(delta.x)+power2(delta.y));
	Vec2 gradient = delta/(Vec2){length, length};
	gradient = {(float)round(gradient.x), (float)round(gradient.y)};

	uint8_t matrix[MAP_X*MAP_Y] = {};

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;

	matrix[Vec2Position(start, (Vec2){MAP_X, MAP_Y})] = 1;
	matrix[Vec2Position(end, (Vec2){MAP_X, MAP_Y})] = 1;

	int x;
	int y;

	for (int i = 1; i < std::floor(length)-1; i++){
		x = start.x + (gradient.x * i);
		y = start.y - (gradient.y * i);
		matrix[Vec2Position((Vec2){(float)x, (float)y}, (Vec2){MAP_X, MAP_Y})] = 1;
	}

	MicroBitImage result(MAP_X, MAP_Y, matrix);
	return result;
}

int main()
{
	uBit.init();
	while (true){
		uBit.display.print(Vec2uBitImage((Vec2){3, 3}, (Vec2){3, 5}));
		uBit.sleep(500);
	}

	release_fiber();
	return 0;
}
