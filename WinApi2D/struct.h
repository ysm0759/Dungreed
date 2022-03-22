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

enum class STAT
{
	MAXAD,
	MINAD,
	POWER,
	DEFEND,
	TOUGH,
	BLOCK,
	CRITICAL,
	CRITICAL_DAMAGE,
	EVASION,
	SPEED,
	ATTACK_SPEED,
	RELOADING,
	DASH_DAMAGE,
	TRUE_DAMAGE,
	SIZE,
};

enum class ATTRIBUTE
{
	BURN,
	POSION,
	COLD,
	ELECTRIC_SHOCK,
	STAN,
	SIZE,
};

struct Stat
{
	int maxAD;			//최대 공격력
	int minAD;			//최소 공격력
	int power;			//위력
	int defend;			//방어력
	int tough;			//강인함
	int block;			//막기
	int burn;			//화상
	int critical;		//치명타
	int criticalDamage; //치명타 데미지
	int evasion;		//회피
	int Posion;		    //중독
	int speed;			//이동속도
	int attackSpeed;	//공격속도
	int reloading;		//재장전속도
	int	dashDamage;		//대쉬공격력
	int	trueDamage;		//고정데미지
};