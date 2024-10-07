#define SDL_MAIN_HANDLED
#include "stdbool.h"
#include "stdio.h"
#include "generateWorld.h"

int main(int argc, char* args[]) 
{
	SDL_Window * w = SDL_CreateWindow("Spider Grand Prix", (1920 / 2 - 400), (1080 / 2) - 400, 800, 800, SDL_WINDOW_SHOWN);
	SDL_Renderer * r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
	
	char a;
	
	struct box background;
	background.x = 0;
	background.y = 0;
	background.w = 800;
	background.h = 800;
	load_sprite(&background, "background.png", r);
	
	struct box lifeGauge;
	lifeGauge.x = 50;
	lifeGauge.y = 750;
	lifeGauge.w = 128;
	lifeGauge.h = 32;
	load_sprite(&lifeGauge, "life_gauge.png", r);
	
	struct box life;
	life.x = 50;
	life.y = 750;
	life.w = 128;
	life.h = 32;
	load_sprite(&lifeGauge, "life.png", r);
	
	struct box finish_line;
	finish_line.x = 8300;
	finish_line.y = 600;
	finish_line.w = 32;
	finish_line.h = 32;
	load_sprite(&finish_line, "checkeredFlag.png", r);
	
	struct spider s;
	s.life = 1000;
	s.bounding.x = 20;
	s.bounding.y = 20;
	s.bounding.w = 16;
	s.bounding.h = 16;
	s.bounding.v_i = 5;
	s.bounding.v_j = 5;
	s.numWebs = 0;
	s.webs = NULL;
	s.bounding.grav_ticks = 1;
	s.bounding.grav_flag = true;
	load_sprite(&s.bounding, "spider.png", r);
	
	struct fly flea;
	flea.bounding.x = 400;
	flea.bounding.y = 100;
	flea.bounding.w = 8;
	flea.bounding.h = 8;
	load_sprite(&flea.bounding, "fly.png", r);
	
	struct flyGroup ff;
	ff.numFlies = 0;
	ff.flies = NULL;
	struct boxGroup bb;
	bb.boxes = NULL;
	bb.numBoxes = 0;
	
	generateWorld(&s, &ff, &bb, r);
	
	
	struct box h;
	h.x = 50;
	h.y = 50;
	h.w = 20;
	h.h = 20;
	h.v_i = 5;
	h.v_j = 5;
	h.ref_check = 0;
	
	struct box floor;
	floor.x = 0;
	floor.y = 600;
	floor.w = 800;
	floor.h = 32;
	load_sprite(&floor, "floor.png", r);
	
	struct box f[3];
	for (int q = 0;q < 3;q++) 
	{
		f[q].x = 0 + (q*64);
		f[q].y = 300;
		f[q].w = 32;
		f[q].h = 32;
		load_sprite(&f[q], "default_texture.png", r);
	}
	
	load_sprite(&h, "default_texture.png", r);
	SDL_Event e;
	
	bool stop = false;
	while (!stop) 
	{
        while( SDL_PollEvent( &e ) != 0 )
        {
			if (e.type == SDL_KEYDOWN) 
			{
				if (e.key.keysym.sym == SDLK_w) 
				{
					move_spider(&s, 0, -1*s.bounding.v_j);
					s.bounding.grav_flag = true;
					//MOVE_UP = true;
				}
				if (e.key.keysym.sym == SDLK_a)
				{
					move_spider(&s, -1*s.bounding.v_i, 0);
					//MOVE_LEFT = true;
				}
				if (e.key.keysym.sym == SDLK_s) 
				{
					move_spider(&s, 0, s.bounding.v_j);
					//MOVE_DOWN = true;
				}
				if (e.key.keysym.sym == SDLK_d) 
				{
					move_spider(&s, s.bounding.v_i, 0);
					//MOVE_RIGHT = true;
				}
				if (e.key.keysym.sym == SDLK_ESCAPE) 
				{
					stop = true;
				}
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) 
			{
				if (e.button.button == SDL_BUTTON_LEFT) 
				{
					shootWeb(&s, r);
				}
			}
        }
		
		SDL_RenderClear(r);
		
		draw_box(&background, r);
		
		handleCollision(&s.bounding, &floor);
		draw_box(&floor, r);
		
		for (int i = 0;i < s.numWebs;i++) 
		{
			draw_box(&s.webs[i].bounding, r);
			handleWebCollision(&s.bounding, &s.webs[i]);
		}
		
		for (int j = 0;j < ff.numFlies;j++) 
		{
			flyPath(&ff.flies[j]);
			draw_fly(&ff.flies[j], r);
			eatFly(&s, &ff.flies[j]);
			handleCollision(&ff.flies[j].bounding, &bb.boxes[j]);
		}
		
		for (int q = 0;q < bb.numBoxes;q++) 
		{
			draw_box(&bb.boxes[q], r);
			handleCollision(&s.bounding, &bb.boxes[q]);
		}
		
		applyGravity(&s.bounding);
		draw_box(&s.bounding, r);
		
		draw_box(&finish_line, r);
		
		if (collisionDetect(&s.bounding, &finish_line)) 
		{
			printf("%s", "You won!");
			stop = true;
		}
		
		//showLife(&life, &s, r);
		draw_box(&lifeGauge, r);
		
		if (s.life <= 0) 
		{
			printf("%s", "You died!");
			stop = true;
		}
		
		scroll(&s, &bb, &ff, &finish_line);
		
		SDL_RenderPresent(r);
		s.bounding.ref_check += 1;
	}
	free_sprite(&h);
	cleanupSpider(&s);
	for (int q = 0;q < 3;q++) 
	{
		free_sprite(&f[q]);
	}
	SDL_DestroyWindow(w);
	SDL_DestroyRenderer(r);
	
	scanf("%c", a);
}