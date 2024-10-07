#include "generateWorld.h"

void generateWorld(struct spider * s, struct flyGroup * f, struct boxGroup * b, SDL_Renderer * r)
{
	s->life = 100;
	s->bounding.x = 20;
	s->bounding.y = 20;
	s->bounding.w = 16;
	s->bounding.h = 16;
	s->bounding.v_i = 5;
	s->bounding.v_j = 5;
	s->numWebs = 0;
	s->webs = NULL;
	s->bounding.grav_ticks = 1;
	s->bounding.grav_flag = true;
	load_sprite(&s->bounding, "spider.png", r);
	
	int dummy_x = 400;
	int dummy_y = 400;
	
	for (int i = 0;i < 10;i++) 
	{
		addFly(f, r);
		f->flies[f->numFlies - 1].bounding.x = dummy_x + (i*400);
		f->flies[f->numFlies - 1].bounding.y = dummy_y;
		f->flies[f->numFlies - 1].draw_flag = true;
		load_sprite(&f->flies[f->numFlies - 1].bounding, "fly.png", r);
	}
	
	srand(time(NULL));
	for (int i = 0;i < 10;i++) 
	{
		int pos = rand();
		pos = pos % 600;
		
		for (int j = 0;j < pos / 32;j++) 
		{
			addBox(b, r);
			b->boxes[b->numBoxes - 1].x = i*600;
			b->boxes[b->numBoxes - 1].y = (568 - (j*32));
		}
		for (int z = (pos / 32);z < (600/32);z++) 
		{
			addBox(b, r);
			b->boxes[b->numBoxes - 1].x = i*600;
			b->boxes[b->numBoxes - 1].y = (568 - (32 + (z*32)));
		}
	}
}