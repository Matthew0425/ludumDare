#include "boxCollision.h"

void move_x(struct box * b, float dx) 
{
	b->x += dx;
}

void move_y(struct box * b, float dy) 
{
	b->y += dy;
}

void move_vector(struct box * b, float dx, float dy) 
{
	float c = sqrt((dx*dx) + (dy*dy));
	float s_x = dx / c;
	float s_y = dy / c;
	b->x += s_x;
	b->y += s_y;
}

void load_sprite(struct box * b, char * path, SDL_Renderer * r) 
{
	SDL_Surface * dummy = IMG_Load(path);
	b->sprite = SDL_CreateTextureFromSurface(r, dummy);
	SDL_FreeSurface(dummy);
}

void free_sprite(struct box * b) 
{
	SDL_DestroyTexture(b->sprite);
}

void draw_box(struct box * a, SDL_Renderer * r) 
{
	SDL_Rect dummy;
	SDL_Rect dummy2;
	dummy.x = 0;
	dummy.y = 0;
	dummy.w = a->w;
	dummy.h = a->h;
	dummy2.x = a->x;
	dummy2.y = a->y;
	dummy2.w = a->w;
	dummy2.h = a->h;
	
	SDL_RenderCopy(r, a->sprite, &dummy, &dummy2);
}

bool collisionDetect(struct box * a, struct box * b) 
{
	float awCoord = a->x + a->w;
	float ahCoord = a->y + a->h;
	float bwCoord = b->x +  b->w;
	float bhCoord = b->y + b->h;
	if ((a->x > b->x && a->x < bwCoord) && (a->y > b->y && a->y < bhCoord)) 
	{
		return true;
	}
	if ((awCoord > b->x && awCoord < bwCoord) && (a->y > b->y && a->y < bhCoord)) 
	{
		return true;
	}
	if ((a->x > b->x && a->x < bwCoord) && (ahCoord > b->y && ahCoord < bhCoord)) 
	{
		return true;
	}
	if ((awCoord > b->x && awCoord < bwCoord) && (ahCoord > b->y && ahCoord < bhCoord)) 
	{
		return true;
	}
	if (a->ref_check % 2 == 0) 
	{
		a->ref_x = a->x;
		a->ref_y = a->y;
		a->ref_check = 0;
	}
	return false;
}


bool handleCollision(struct box * a, struct box * b) 
{
	if (collisionDetect(a, b)) 
	{
		a->ref_check = 0;
		
		/*printf("%s", "ref x: ");
		printf("%f\n", a->ref_x);
		printf("%s", "ref y: ");
		printf("%f\n", a->ref_y);
		
		printf("%s", "x: ");
		printf("%f\n", a->x);
		printf("%s", "y: ");
		printf("%f\n", a->y);*/
		
		if (a->x > a->ref_x && a->y == a->ref_y) 
		{
			move_x(a, -1*a->v_i);
			a->grav_flag = false;
			//a->x = b->x - b->w;
		}
		else if (a->x < a->ref_x && a->y == a->ref_y) 
		{
			move_x(a, a->v_i);
			a->grav_flag = false;
			//a->x = b->x + b->w;
		}
		else if (a->y > a->ref_y && a->x == a->ref_x) 
		{
			move_y(a, -1*a->v_j);
			a->grav_flag = false;
		}
		else if (a->y < a->ref_y && a->x == a->ref_x) 
		{
			move_y(a, a->v_j);
			a->grav_flag = false;
		}
		else if (a->x > a->ref_x && a->y > a->ref_y) 
		{
			move_vector(a, -1*a->v_i, -1*a->v_j);
			a->grav_flag = false;
		}
		else if (a->x > a->ref_x && a->y < a->ref_y) 
		{
			move_vector(a, -1*a->v_i, a->v_j);
			a->grav_flag = false;
		}
		else if (a->x < a->ref_x && a->y > a->ref_y) 
		{
			move_vector(a, a->v_i, -1*a->v_j);
			a->grav_flag = false;
		}
		else if (a->x < a->ref_x && a->y < a->ref_y) 
		{
			move_vector(a, a->v_i, a->v_j);
			a->grav_flag = false;
		}
		//printf("%s", "does it get here?");
		return true;
	}
	return false;
}

void applyGravity(struct box * b) 
{
	if (b->grav_flag) 
	{
		b->y += .01*(b->grav_ticks)*(b->grav_ticks);
		if (b->grav_ticks <= 1) 
		{
			b->grav_ticks += 1;
		}
	}
}

void addBox(struct boxGroup * bb, SDL_Renderer * r) 
{
	bb->numBoxes += 1;
	struct box a;
	a.w = 32;
	a.h = 32;
	load_sprite(&a, "brick.png",r);
	struct box * dummy = (struct box *)(malloc(bb->numBoxes * sizeof(a)));
	for (int i = 0;i < bb->numBoxes - 1;i++) 
	{
		dummy[i] = bb->boxes[i];
	}
	dummy[bb->numBoxes - 1] = a;
	free(bb->boxes);
	bb->boxes = dummy;
}