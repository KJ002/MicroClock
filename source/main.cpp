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
	int result;

	result += (_round(position.y) - 1) * _round(matrix.x);
	result += _round(position.x);
	return result;
}

MicroBitImage Vec2uBitImage(Vec2 start, Vec2 end, float th = 0){
	float gradient = (end.y - start.y) / (end.x - start.x);
	bool negativeGradient = (gradient < 0) ? true : false;

	uint8_t matrix[MAP_X*MAP_Y];

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;

	int x;
	int y;

	for (int i = 0; i < std::abs((end.x - start.x)); i++){
		x = (negativeGradient) ? -i : i;
		y = i * gradient;

		matrix[Vec2Position((Vec2){(float)x, (float)y}, (Vec2){MAP_X, MAP_Y})] = 1;
		uBit.serial.send("Add led pos");
	}

	return MicroBitImage(MAP_X, MAP_Y, matrix);
}

int main()
{
	uBit.init();

	 //const uint8_t heart[] = { 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0}; // a cute heart
	 //MicroBitImage i(5,5,heart);

	while (true){
		uBit.display.print(Vec2uBitImage((Vec2){3, 3}, (Vec2){1, 3}));
		uBit.sleep(500);
	}

	release_fiber();
	return 0;
}
