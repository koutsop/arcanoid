/*
 * author: koutsop
 */

#include <iostream>

#include "Board.h"


#define BOARD_SPEED	1


Board::Board(int start_x, int start_y, 
			 AnimationFilm *af) : 	startY(start_y),
									Sprite(start_x, start_y, af)
{SetVisibility(true);}


void Board::Move(const int dx, const int dy){
	if( (keyPressed == Key_Left) || (keyPressed == Key_A)){
		SetPointUpLeft(GetPointUpLeft().GetX() - BOARD_SPEED, startY);
		SetPointDownRight(GetPointDownRight().GetX() - BOARD_SPEED, GetPointDownRight().GetY());
	}

	else if( (keyPressed == Key_Right) || (keyPressed == Key_D) ){
		SetPointUpLeft(GetPointUpLeft().GetX() + BOARD_SPEED, startY);
		SetPointDownRight(GetPointDownRight().GetX() + BOARD_SPEED, GetPointDownRight().GetY());

	}

	else if( (keyPressed == Key_Mouse_Left) || (keyPressed == Key_Mouse_Right) ){
		int distance = GetPointUpLeft().GetX() - GetPointDownRight().GetX();
		SetPointUpLeft(dx, startY);
		SetPointDownRight(dx+distance, GetPointDownRight().GetY());
	}
	return;
}


/*
void Board::Move(const int dx, const int dy){
	if( StateHolder::GetKey() == Key_Left )
		SetPointUpLeft(GetPointUpLeft().GetX() - 1, startY);

	else if( StateHolder::GetKey() == Key_Right )
		SetPointUpLeft(GetPointUpLeft().GetX() + 1, startY);

	else if( StateHolder::GetKey() == Key_Mouse_Left )
		SetPointUpLeft(dx, startY);

	else if( StateHolder::GetKey() == Key_Mouse_Right )
		SetPointUpLeft(dx, startY);

	return;
}
*/