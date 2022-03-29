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
		return (float)sqrt((float)this->x * (float)this->x + (float)this->y * (float)this->y);
	}

	Vector2f& Normalize()
	{
		float length = this->Length();

		assert(length != 0.f);

		this->x /= length;
		this->y /= length;

		return *this;
	}

	Vector2f& operator = (POINT _point)
	{
		this->x = (float)_point.x;
		this->y = (float)_point.y;
	}

	Vector2f operator + (Vector2f _vector)
	{
		return Vector2f(this->x + _vector.x, this->y + _vector.y);
	}
	Vector2f operator - (Vector2f _vector)
	{
		return Vector2f(this->x - _vector.x, this->y - _vector.y);
	}
	Vector2f operator * (Vector2f _vector)
	{
		return Vector2f(this->x * _vector.x, this->y * _vector.y);
	}
	Vector2f operator / (Vector2f _vector)
	{
		assert (_vector.x == 0.f || _vector.y == 0.f);
		return Vector2f(this->x / _vector.x, this->y / _vector.y);
	}

	Vector2f operator * (int _int)
	{
		return Vector2f(this->x * (float)_int, this->y * (float)_int);
	}
};