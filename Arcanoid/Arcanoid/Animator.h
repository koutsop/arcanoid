/*
 *author: koutsop
 */
#ifndef ANIMATOR_H
#define ANIMATOR_H


#include <map>
#include <string>

class Animator;

typedef std::map<std::string, Animator *> AnimatorMap;

typedef unsigned long timestamp_t;

enum animatorstate_t {
	ANIMATOR_FINISHED	= 0,
	ANIMATOR_RUNNING	= 1,
	ANIMATOR_STOPPED	= 2
};

class Animator { 
public:
	typedef void (*FinishCallback)(Animator*,void*);

protected:
	timestamp_t			lastTime;
	animatorstate_t		state;
	FinishCallback		onFinish;
	void*				finishClosure;
	
	void NotifyStopped (void);

public:
	void Stop (void);
	bool HasFinished (void) const { return state != ANIMATOR_RUNNING; }
	virtual void TimeShift (timestamp_t offset);
	virtual void Progress (timestamp_t currTime) = 0;
	void SetOnFinish (FinishCallback f, void* c =(void*) 0) { onFinish = f, finishClosure = c; }
	
	Animator (void); 
	virtual ~Animator(){};
};


#endif
