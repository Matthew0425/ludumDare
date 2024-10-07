#include "fly.h"

struct web {
	struct box bounding;
};

struct spider {
	int life;
	struct box bounding;
	struct web * webs;
	bool jumping;
	int numWebs;
};

void jump(struct spider * s);
void shootWeb(struct spider * s, SDL_Renderer * r);
void eatFly(struct spider * s, struct fly * f);
void addWeb(struct spider * s, SDL_Renderer * r);
void cleanupSpider(struct spider * s);
void handleWebCollision(struct box * a, struct web * b);
void scroll(struct spider * s, struct boxGroup * b, struct flyGroup * f, struct box * finish_line);
void move_spider(struct spider * s, float dx, float dy);
void showLife(struct box * lifeGauge, struct spider * s, SDL_Renderer * r);