#include "stdio.h"
#include "stdbool.h"
#include "time.h"
#include "stdlib.h"
#include "math.h"
#include "SDL2\include\SDL.h"
#include "SDL2\include\SDL_image.h"

struct box {
	float x;
	float y;
	float w;
	float h;
	int ref_check;
	float v_i;
	float v_j;
	float ref_x;
	float ref_y;
	float grav_ticks;
	bool grav_flag;
	SDL_Texture * sprite;
};

struct boxGroup 
{
	struct box * boxes;
	int numBoxes;
};

void move_x(struct box * b, float dx);
void move_y(struct box * b, float dy);
void move_vector(struct box * b, float dx, float dy);
void load_sprite(struct box * b, char * path, SDL_Renderer * r);
void free_sprite(struct box * b);
void draw_box(struct box * a, SDL_Renderer * r);
bool collisionDetect(struct box * a, struct box * b);
bool handleCollision(struct box * a, struct box * b);
void applyGravity(struct box * b);
void addBox(struct boxGroup * boxes, SDL_Renderer * r);

