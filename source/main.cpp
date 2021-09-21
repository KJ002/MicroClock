#include "MicroBit.h"
#include <cmath>

#define MAP_X 5
#define MAP_Y 5
#define MAP0_X 4
#define MAP0_Y 4

#define PI 2*acos(0.0)
#define power2(x) (x*x)


double radToDeg(double rad) { return rad / (PI / 180); }
double degToRad(double deg) { return deg * (PI / 180); }

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

		if (!th%360)
			return *this;

		const double rad = degToRad(360-th);

		Vec2 result;

		result.x = std::cos(rad) * this->x - std::sin(rad) * this->y;
		result.y = std::sin(rad) * this->x + std::cos(rad) * this->y;

		return result;
	}

	Vec2 rotate(const double th, const Vec2& origin) const{
		Vec2 newPoint = *this - origin;

		return newPoint.rotate(th)+origin;
	}

	float length() const{
		return std::sqrt(power2(x) + power2(y));
	}

	Vec2 round() const{
		Vec2 result = {_round(x), _round(y)};

		return result;
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

uint8_t * Vec2uBitImage(Vec2 start, Vec2 end, float th = 0){

	start = start.round();
	end = end.round().rotate(th, start);

	static uint8_t matrix[MAP_X*MAP_Y] = {};

	for (int i = 0; i < MAP_X*MAP_Y; i++)
		matrix[i] = 0;

	if (start.x == end.x){
		float direction = (start.y > end.y) ? -1 : 1;
		int length = std::abs(end.y - start.y);
		for (float i = 0; i <= length; i++)
			matrix[Vec2Position((Vec2){start.x, start.y + (direction * i)})] = 1;

		return matrix;
	}

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

	return matrix;
}


int main()
{
	uBit.init();

	uint8_t * data = Vec2uBitImage((Vec2){2, 0}, (Vec2){1, 4});

	MicroBitImage k(5, 5, data);

	while (true){
		uBit.display.print(k);
		uBit.sleep(250);
	}

	release_fiber();
	return 0;
}
