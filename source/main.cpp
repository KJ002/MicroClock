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
	//float gradient = (end.y - start.y) / (end.x - start.x);
	//float gradient = 1.f;
	//bool negativeGradient = (gradient < 0.f) ? true : false;

	Vec2 delta{end.x-start.x, end.y-start.y};
	float length = std::sqrt(power2(delta.x)+power2(delta.y));
	Vec2 gradient = delta/(Vec2){length, length};
	gradient = {(float)round(delta.x), (float)round(delta.y)};

	std::vector<Vec2> positions;

	uint8_t matrix[MAP_X*MAP_Y] = {};

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;


	/*
	for (int i = 1; i < std::abs((end.x - start.x)); i++){
		//x = (negativeGradient) ? -i : i;
		x = i+start.x;
		y = (i * gradient)-start.y;

		matrix[Vec2Position((Vec2){(float)x, (float)y}, (Vec2){MAP_X, MAP_Y}) % 25] = 1;
	}*/

	matrix[Vec2Position(start, (Vec2){MAP_X, MAP_Y})] = 1;
	matrix[Vec2Position(end, (Vec2){MAP_X, MAP_Y})] = 1;

	for (int i = 1; i < round(length)-1; i++)
		matrix[Vec2Position(gradient*(Vec2){(float)i, (float)i}, (Vec2){MAP_X, MAP_Y})] = 1;

	int z[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	for (int i = 0; i < sizeof(z)/sizeof(z[0]); i++)
		matrix[i] = z[i];


	MicroBitImage result(MAP_X, MAP_Y, matrix);
	return result;
}

int main()
{
	uBit.init();
	const uint8_t heart[] = { 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0}; // a cute heart
	MicroBitImage i(5,5,heart);
	while (true){
		uBit.display.print(Vec2uBitImage((Vec2){3, 3}, (Vec2){5, 5}));
		//uBit.display.print(i);
		uBit.sleep(500);
	}

	release_fiber();
	return 0;
}
