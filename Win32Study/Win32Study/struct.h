#pragma once

struct Vector2f
{
	float x;
	float y;

	Vector2f() : x(0.0f), y(0.0f)
	{
	}

	Vector2f(float _x, float _y)
		: x(_x), y(_y)
	{
	}

	Vector2f(int _x, int _y)
		: x((float)_x), y((float)_y)
	{
	}

	Vector2f(POINT _point)
		: x((float)_point.x), y((float)_point.y)
	{
	}

	float Length()
	{
		return sqrt(float(this->x * this->x + this->y * this->y));
	}

	Vector2f& Normalize()
	{
		float length = this->Length();

		assert(length != 0.f);

		this->x /= length;
		this->y /= length;

		return *this;
	}
};