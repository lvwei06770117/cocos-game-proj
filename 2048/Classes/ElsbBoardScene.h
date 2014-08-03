#ifndef __ELSBBOARD_SCENE_H__
#define __ELSBBOARD_SCENE_H__

#include "cocos2d.h"
#include "VisibleRect.h"
#include "CardSprite.h"
#include "SimpleRecognizer.h"

USING_NS_CC;

class ElsbBoard : public Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // implement the "static create()" method manually
    CREATE_FUNC(ElsbBoard);
	~ElsbBoard();

	void createCardSprite(Size size);
	void createCardNumber(bool animation);

	//触摸事件监听回调函数
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

private:

	//左滑动
    bool doLeft();
    //右滑动
    bool doRight();
    //上滑动
    bool doUp();
    //下滑动
    bool doDown();

	void doCheck();
	void setScore(int score);
	bool isWin();
	void removeSuccessLayer();

	void saveStatus();
    void resumeStatus();
	void onPause(Ref * sender);
	bool shouldCreateCardNumber();
	Point getPosition(int x,int y);

private:
	//定义cellSize/cellSpace
    int cellSize;
    int cellSpace;

	CardSprite* cardArr[4][4];
	int score;
	Label* cardNumberTTF;
	SimpleRecognizer *recognizer;
	LayerColor * successLayer;
};



#endif