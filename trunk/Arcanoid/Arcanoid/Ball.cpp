/* Implementation of the Ball */

#include "Ball.h"
#include "Brick.h"

#include <iostream>

#include "KeyLogger.h"
#include "Terrain.h"

#define BALL_SPEED	1

using std::cout;
using std::endl;

Ball::Ball(int start_x, int start_y, 
		   AnimationFilm *af, 
		   const char *ball_string) : Sprite(start_x, start_y, af)
{
	old.SetX(start_x);
	old.SetY(start_y);
	spriteType = SPRITE_BALL;
	speedX = BALL_SPEED;
	speedY = BALL_SPEED;
	goingLeft	= false;
	goingUp		= true;
}


void Ball::CheckCoordinates(void){
	int x			= GetPosition().GetX();
	int y			= GetPosition().GetY();
	int startX		= Terrain::coordinates.GetX();
	int startY		= Terrain::coordinates.GetY();
	int terrainW	= Terrain::width;
	int terrainH	= Terrain::height;

	if( ((x+GetWidth()) >= (terrainW+startX)) && goingUp && !goingLeft ){
		goingUp		= true;						//right wall
		goingLeft	= true;
	}
	else if( ((x+GetWidth()) >= (terrainW+startX)) && !goingUp && !goingLeft ){
		goingUp		= false;					//right wall
		goingLeft	= true;
	}
	else if( (y == startY) && goingUp && goingLeft ){
		goingUp		= false;					//up wall
		goingLeft	= true;
	}
	else if( (y == startY) && goingUp && !goingLeft ){
		goingUp		= false;					//up wall
		goingLeft	= false;
	}
	else if( (x <= startX) && !goingUp && goingLeft ){
		goingUp		= false;					//left wall
		goingLeft	= false;
	}
	else if( (x <= startX) && goingUp && goingLeft ){
		goingUp		= true;						//left wall
		goingLeft	= false;
	}
	else if( (y+GetHeight()) >= (terrainH+startY) ){
		goingUp		= true;						//bottom wall
	}
	return;
}

void Ball::Move(const int dx, const int dy){
	CheckCoordinates();
	if(goingLeft)	{ SetPosition(GetPosition().GetX() - speedX, GetPosition().GetY()); }
	else			{ SetPosition(GetPosition().GetX() + speedX, GetPosition().GetY()); }

	if(goingUp)		{ SetPosition(GetPosition().GetX(), GetPosition().GetY() - speedY); }
	else			{ SetPosition(GetPosition().GetX(), GetPosition().GetY() + speedY); }

	return;
}

//TODO na kanw kai alla edw aplos blepw an einai tixos h' bricks kkai to paw sthn arxikh tou 8esh
void Ball::Collide(Sprite *s){
	spritetype_t type = s->GetType();
	
	if( type == SPRITE_BOARD ){			//ok
		if		( StateHolder::IsGoLeft() )	{ goingLeft = true;  }
		else if ( StateHolder::IsGoRight())	{ goingLeft = false; }
		else								{ goingLeft = goingLeft; }		
		goingUp = true;
	}
	else if( type == SPRITE_BRICK ) {
		dynamic_cast<Brick *>(s)->SetIsActive(true);
		int ballX1 = this->GetPosition().GetX(), ballY1 = this->GetPosition().GetY();
		int ballX2 = ballX1 + this->GetWidth(), ballY2 = ballY1 + this->GetHeight();
		int brickX1 = s->GetPosition().GetX(), brickY1 = s->GetPosition().GetY();
		int brickX2 = brickX1 + s->GetWidth(), brickY2 = brickY1 + s->GetHeight();

		//Ball is down, brick is up
		if( (ballX1 >= brickX1-this->GetWidth() || ballX1 <=brickX2) && ballY1 >= brickY2 ){
			ReverseVertical();
			std::cout << "Ball is going UP !!!" << std::endl;
		}else //Ball is right, brick is left
			if ( (ballY1 >= brickY1 - this->GetHeight() || ballY1 <= brickY2) && ballX1 >= brickX2 ){
				//todo
			ReverseVertical();
			std::cout << "Ball is going left  <<<<<<----!!!!" << std::endl;
		}else //Ball is up, brick is down
			if((ballX1 >= brickX1-this->GetWidth() || ballX1 <=brickX2) && ballY2 <= brickY1 ){ 
				//todo
			ReverseVertical();
			std::cout << "Ball is going DOWN !!!!" << std::endl;
		} else //Ball is left, brick is right
			if( (ballY1 >= brickY1 - this->GetHeight() || ballY1 <= brickY2) && ballX2 <= brickX1 ){
				//todo
			ReverseHorizon();
			std::cout << "Ball is going right ------->>>>" << std::endl;
		} else //lol, assert
			assert(0);

	}
	else
		assert(!"kapia malakia ekanes sthn ball malaka\n");
	return;
}

void Ball::ReverseHorizon(void){
	goingLeft = !goingLeft;
	return;
}
void Ball::ReverseVertical(void){
	goingUp = !goingUp;
	return;
}
void Ball::SetSpeedX(int _newspeed){
	this->speedX = _newspeed;
	return;
}

void Ball::SetSpeedY(int _newspeed){
	this->speedY = _newspeed;
	return;
}

int Ball::GetSpeedX(void){
	return this->speedX;
}

int Ball::GetSpeedY(void){
	return this->speedY;
}
