#pragma once

struct iPoint
{
	int x;
	int y;
};

struct fPoint
{
	float x;
	float y;

	fPoint()
	{
		x = 0;
		y = 0;
	}

	fPoint(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	fPoint& operator=(const fPoint& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}

	fPoint operator+(const fPoint& other)
	{
		return fPoint(x + other.x, y + other.y);
	}

	fPoint& operator+=(const fPoint& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	fPoint operator-(const fPoint& other)
	{
		return fPoint(x - other.x, y - other.y);
	}

	template <typename T>
	fPoint operator*(T num)
	{
		return fPoint(x * num, y * num);
	}

	template <typename T>
	fPoint operator/(T num)
	{
		assert(0 != num);

		return fPoint(x / num, y / num);
	}

	fPoint& normalize()
	{
		float length = (float)sqrt((double)x * x + (double)y * y);

		if (0 == length)
		{
			x = 0;
			y = 0;
		}
		else
		{
			x = x / length;
			y = y / length;
		}

		return *this;
	}

	float Length()
	{
		return (float)sqrt((double)x * x + (double)y * y);
	}
};

typedef iPoint iVec2;
typedef fPoint fVec2;