#include <vector>
#include "Fizzle\Fizzle.h"

struct sprite
{
	sprite(float _x, float _y, float _a, FzlSpriteHandle _ID) : x(_x), y(_y), a(_a), spriteID(_ID){};

	bool operator==(const sprite& cmp);

	float x;
	float y;
	float a;
	FzlSpriteHandle spriteID;
};


class store
{
public:
	void push_back(sprite);
	bool remove(sprite);
	void draw();
private:
	std::vector<sprite> holder;
};

void store::push_back(sprite push)
{
	holder.push_back(push);
}

bool store::remove(sprite rem)
{
	for (int count = 0; count < holder.size(); count++)
	{
		if (holder[count] == rem)
		{
			holder.erase(holder.begin() + count);
			return true;
		}
	}
	return false;
}

void store::draw()
{
	for (int count = 0; count < holder.size(); count++)
	{
		FzlDrawSprite(holder[count].spriteID, holder[count].x, holder[count].y, holder[count].a);
	}
	
}

bool sprite::operator==(const sprite& cmp)
{
	if (x == cmp.x &&
		y == cmp.y &&
		a == cmp.a &&
		spriteID == cmp.spriteID)
		return true;
	else
		return false;
}
