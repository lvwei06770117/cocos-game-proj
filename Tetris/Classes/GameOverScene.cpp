
#include "GameOverScene.h"
#include "GameScene.h"

bool GameOverScene::init() 
{   
	if( Scene::init() ) 
	{   
		this->_layer = GameOverLayer::create();   
		this->_layer->retain();   
		this->addChild(_layer);   
		return true; 
	}   
	else 
	{   
		return false; 
	} 
}

GameOverScene::~GameOverScene() 
{   
	if (_layer) 
	{ 
		_layer->release();  
		_layer = NULL; 
	} 
}

bool GameOverLayer::init() 
{   
	if ( LayerColor::initWithColor( Color4B(255,255,255,255) ) ) 
	{   
		auto winSize = Director::getInstance()->getWinSize();   
		this->_label = LabelTTF::create("","Artial", 32);   
		_label->retain();  
		_label->setColor( Color3B(0, 0, 0) );  
		_label->setPosition( Point(winSize.width/2, winSize.height/2) );   
		this->addChild(_label);    
		this->runAction( Sequence::create(DelayTime::create(3), CallFunc::create(CC_CALLBACK_0(GameOverLayer::gameOverDone, this)), NULL));   
		return true; 
	}   
	else 
	{   
		return false; 
	} 
}


void GameOverLayer::gameOverDone() 
{   
	Director::getInstance()->replaceScene( GameLayer::createScene() ); 
}

GameOverLayer::~GameOverLayer() 
{   
	if (_label) 
	{  
		_label->release(); 
		_label = NULL; 
	}  
}