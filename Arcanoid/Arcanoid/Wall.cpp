/* implementation of a Wall */

#include "Wall.h"

Wall::Wall(int upper_left_x, int upper_left_y, int down_right_x, int down_right_y) 
			: Sprite(upper_left_x, upper_left_y, down_right_x, down_right_y)
{
	SetVisibility(false);
	spriteType = SPRITE_WALL;
}

void Wall::Collide(Sprite *s){
	//TODO: fill it up
	return;
}


Wall::~Wall(){
	return;
}
