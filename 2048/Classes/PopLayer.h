
#ifndef ___048__PopLayer__
#define ___048__PopLayer__

#include "cocos2d.h"

USING_NS_CC;

class PopLayer : public LayerColor
{
public:
    static PopLayer* create(const Color4B& color);
    virtual bool initWithColor(const Color4B& color);
    
    //�����¼������ص�����
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
private:
    void onRestart(Ref* pSender);
    void onExit(Ref* pSender);
    void onContinue(Ref* pSender);
};

#endif /* defined(___048__PopLayer__) */