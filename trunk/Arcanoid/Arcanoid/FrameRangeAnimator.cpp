/*
 *author: koutsop
 */
//TODO na elen3w thn Move sto sprite giati den uparxei:
//TODO na dw an xriazete h while
#include "FrameRangeAnimator.h"

void FrameRangeAnimator::Progress (timestamp_t currTime) {

	//while (currTime - lastTime >= anim->GetDelay()) {
	if(currTime - lastTime >= anim->GetDelay()){
	    if (currFrame == anim->GetEndFrame())
			currFrame = anim->GetStartFrame();
	    else
			++currFrame;
	    sprite->Move( anim->GetDx(), anim->GetDy() );
	    sprite->SetFrame(currFrame);
	    lastTime += anim->GetDelay();

	    if (currFrame == anim->GetEndFrame() && !anim->GetContinuous()) {
			state = ANIMATOR_FINISHED;
			NotifyStopped();
			return;
	    }
	}//end of first if
	return;
}
/////////////////////////////////////////////////////////////////////



void FrameRangeAnimator::Start(Sprite* s, FrameRangeAnimation* a, timestamp_t t) {
	sprite = s;
	anim = a;
	lastTime = t;
	state = ANIMATOR_RUNNING;
	sprite->SetFrame(currFrame = anim->GetStartFrame());
}

