/*Collision checker class */

#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include <list>

#include "Sprite.h"
#include "KeyLogger.h"


class CollisionChecker {
private:
	std::list<Sprite *> movable;
	std::list<Sprite *> unmovable;
	std::list<Sprite *> powerup;
	std::list<Sprite *> todelete;
	bool CheckSprites( Sprite *first, Sprite *sec);

public:
	void AddMovable(Sprite *toadd);
	void AddUnmovable(Sprite *toadd);
	void AddPowerUp(Sprite *toadd);
	void ToDelete(Sprite *sprite);
	void CollisionCheck(void);
	void CleanUp(void);

	CollisionChecker(void){}
	~CollisionChecker(void);
};

#endif