/*
 * author: koutsop
 */
#ifndef SPRITEHOLDER_H
#define SPRITEHOLDER_H

#include <map>
#include <string>
#include <cassert>
#include <iostream>

#include "Sprite.h"

using namespace std;
typedef map<string, Sprite *> SpriteMap;


class SpriteHolder {
private:
	SpriteMap sprites;

public:
	SpriteHolder(void);
	~SpriteHolder(void);

	void Move();			//kanei tis kuniseis

	/* @target: Na epustrefei to sunolo ton sprites pou uparxoun ston holder.
	 * @return: To sunolo ton sprites.
	 */
	size_t Size(void);
	
	/* @target: Na diagrafei ola ta sprites.
	 */
	void Clear(void);
	
	/* @target: Na elegxei an uparxoun stoixia sto holder h' oxi.
	 * @return: True an den exei stoixeia alios false.
	 */
	bool IsEmpty(void);
	
	/* @target: Na 8etei ena sigkekrimeno sprite pou uparxei ston holder.
	 * @param : name einai to onoma tou sprite pou 8eloume na kanoume thn alagh
	 *		  :sptire einai to eno sprite.
	 * @retrun: True an egine to set alios false.
	 */
	bool SetSprite(string name, Sprite * sprite);
	

	/* @target: Na epistrefei to prwto stoikxeio tou holder.
	 * @return: To prwto stoixio tou holder.
	 */
	SpriteMap::iterator	GetFirst(void);
	
	/* @target: Na epistrefei ena stoixeio meta apo to teleuteo stoixeio tou holder.
	 * @return: Ena stoixeio meta to teleuteo stoixeio tou holder
	 */
	SpriteMap::iterator	GetEnd(void);
	
	/* @target: Na briskei ena sprite mesa sto holder me ena sigkekrimeno name.
	 * @parma : name to onoma tou sprite pros anazitish.
	 * @return: Enan iterator sto sugkekrimeno sprite.
	 */
	SpriteMap::iterator GetSprite(string name);
	
	/* @target: Na isagh ena kenourio sprite ston holder me ena kainourio onoma.
	 * @parma : name to onoma tou sprite pros isagwgh, sprite to sprite pou 8a 
	 *		  :eisagoume ston holder.
	 */
	void Insert(string name, Sprite * sprite);
};

#endif