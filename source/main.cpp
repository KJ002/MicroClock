#include "MicroBit.h"
#include <cmath>

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
	float gradient = 0.f;
	bool negativeGradient = (gradient < 0.f) ? true : false;

	uint8_t matrix[MAP_X*MAP_Y] = {};

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;

	int x;
	int y;

	for (int i = 0; i < std::abs((end.x - start.x)); i++){
		//x = (negativeGradient) ? -i : i;
		x = i;
		y = i * gradient;

		//matrix[Vec2Position((Vec2){(float)x, (float)y}, (Vec2){MAP_X, MAP_Y}) % 25] = 1;
		matrix[Vec2Position((Vec2){(float)1, (float)1}, (Vec2){MAP_X, MAP_Y}) % 25] = 1;
	}

	//int z[] = { 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	//for (int i = 0; i < sizeof(z)/sizeof(z[0]); i++){
	//	matrix[i] = z[i];
	//}

	MicroBitImage result(MAP_X, MAP_Y, matrix);
	return result;
}

int main()
{
	uBit.init();
	const uint8_t heart[] = { 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0}; // a cute heart
	MicroBitImage i(5,5,heart);
	while (true){
		uBit.display.print(Vec2uBitImage((Vec2){3, 3}, (Vec2){5, 3}));
		//uBit.display.print(i);
		uBit.sleep(500);
	}

	release_fiber();
	return 0;
}
