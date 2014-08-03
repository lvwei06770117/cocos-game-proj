#ifndef __CARDSPRITE_H__
#define __CARDSPRITE_H__

#include "cocos2d.h"

USING_NS_CC;

class CardSprite : public Sprite
{
public:
	static CardSprite* createCardSprite(int number, int wight, int height,Point position);
	virtual bool init();
	CREATE_FUNC(CardSprite);
    ~CardSprite();
	int getNumber();
	void setNumber(int num);
	void runNewNumberAction();
private:
	void initCard(int number, int wight, int height, Point position);
	//ÏÔÊ¾Êý×Ö
	int number;
	//±³¾°
	LayerColor * colorBackground ;
	//Label¿Ø¼þ
	Label * labelCardNumber ;
};

#endif