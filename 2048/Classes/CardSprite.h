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
	//��ʾ����
	int number;
	//����
	LayerColor * colorBackground ;
	//Label�ؼ�
	Label * labelCardNumber ;
};

#endif