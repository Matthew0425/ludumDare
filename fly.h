#include "boxCollision.h"

struct fly 
{
	int life;
	struct box bounding;
	float old_x;
	float old_y;
	bool draw_flag;
};

struct flyGroup 
{
	struct fly * flies;
	int numFlies;
};

void flyPath(struct fly * f);
void addFly(struct flyGroup * f, SDL_Renderer * r);
void draw_fly(struct fly * f, SDL_Renderer * r);
