#include "fly.h"

void flyPath(struct fly * f) 
{
	if (f->draw_flag) 
	{
		move_vector(&f->bounding, f->bounding.v_i, f->bounding.v_j);
		if (abs(f->bounding.x) > abs((100 + f->old_x))) 
		{
			f->old_x = f->bounding.x;
			f->old_y = f->bounding.y;
			
			if (f->bounding.v_i > 0) 
			{
				f->bounding.v_i = 0;
				f->bounding.v_j = f->bounding.v_i;
			}
			else
			{
				f->bounding.v_i = 0;
				f->bounding.v_j = -1*f->bounding.v_i;
			}
		}
		if (abs(f->bounding.y) > abs((100 + f->old_y))) 
		{
			f->old_x = f->bounding.x;
			f->old_y = f->bounding.y;
			
			if (f->bounding.v_j > 0) 
			{
				f->bounding.v_i = -1*f->bounding.v_j;
				f->bounding.v_j = 0;
			}
			else
			{
				f->bounding.v_i = f->bounding.v_j;
				f->bounding.v_j = 0;
			}
		}
	}
}

void draw_fly(struct fly * f, SDL_Renderer * r) 
{
	if (f->draw_flag) 
	{
		draw_box(&f->bounding, r);
	}
}

void addFly(struct flyGroup * f, SDL_Renderer * r) 
{
	f->numFlies += 1;
	struct fly a;
	a.bounding.w = 8;
	a.bounding.h = 8;
	load_sprite(&a.bounding, "fly.png",r);
	struct fly * dummy = (struct fly *)(malloc(f->numFlies * sizeof(a)));
	for (int i = 0;i < f->numFlies - 1;i++) 
	{
		dummy[i] = f->flies[i];
	}
	dummy[f->numFlies - 1] = a;
	free(f->flies);
	f->flies = dummy;
}