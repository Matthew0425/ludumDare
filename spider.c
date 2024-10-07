#include "spider.h"

void jump(struct spider * s) 
{
	s->jumping = true;
}

void shootWeb(struct spider * s, SDL_Renderer * r) 
{
	s->life - 25;
	int i, j;
	SDL_GetMouseState(&i, &j);
	addWeb(s, r);
	s->webs[s->numWebs - 1].bounding.x = i - ((s->webs[s->numWebs - 1].bounding.w) / 2);
	s->webs[s->numWebs - 1].bounding.y = j - ((s->webs[s->numWebs - 1].bounding.h) / 2);	
}

void eatFly(struct spider * s, struct fly * f) 
{
	if (collisionDetect(&s->bounding, &f->bounding)) 
	{
		s->life += f->life;
		f->draw_flag = false;
	}
}

void addWeb(struct spider * s, SDL_Renderer * r) 
{
	s->numWebs += 1;
	struct web w;
	w.bounding.w = 64;
	w.bounding.h = 64;
	load_sprite(&w.bounding, "web.png",r);
	struct web * dummy = (struct web *)(malloc(s->numWebs * sizeof(w)));
	for (int i = 0;i < s->numWebs - 1;i++) 
	{
		dummy[i] = s->webs[i];
	}
	dummy[s->numWebs - 1] = w;
	free(s->webs);
	s->webs = dummy;
}

void cleanupSpider(struct spider * s) 
{
	free_sprite(&s->bounding);
	free(s->webs);
}

void handleWebCollision(struct box * a, struct web * b) 
{
	if (collisionDetect(a, &b->bounding)) 
	{
		a->grav_flag = false;
	}
	else 
	{
		a->grav_flag = true;
	}
}

void scroll(struct spider * s, struct boxGroup * b, struct flyGroup * f, struct box * finish_line) 
{
	if (s->bounding.x > 700) 
	{
		move_x(&s->bounding, -1*s->bounding.v_i);
		for (int w = 0;w < b->numBoxes;w++) 
		{
			move_x(&b->boxes[w], -1*s->bounding.v_i);
		}
		for (int u = 0;u < f->numFlies;u++) 
		{
			move_x(&f->flies[u].bounding, -1*s->bounding.v_i);
		}
		for (int q;q < s->numWebs;q++) 
		{
			move_x(&s->webs[q].bounding, -1*s->bounding.v_i);
		}
		move_x(finish_line, -1*s->bounding.v_i);
	}
	else if (s->bounding.x < 100) 
	{
		move_x(&s->bounding, s->bounding.v_i);
		for (int w = 0;w < b->numBoxes;w++) 
		{
			move_x(&b->boxes[w], s->bounding.v_i);
		}
		for (int u = 0;u < f->numFlies;u++) 
		{
			move_x(&f->flies[u].bounding, s->bounding.v_i);
		}
		for (int q = 0;q < s->numWebs;q++) 
		{
			move_x(&s->webs[q].bounding, s->bounding.v_i);
		}
		move_x(finish_line, s->bounding.v_i);
	}
}

void move_spider(struct spider * s, float dx, float dy) 
{
	move_vector(&s->bounding, dx, dy);
	s->life - 1;
}

void showLife(struct box * lifeGauge, struct spider * s, SDL_Renderer * r) 
{
	lifeGauge->w = lifeGauge->w * (s->life/1000);
	draw_box(lifeGauge, r);
	printf("%i", s->life);
}