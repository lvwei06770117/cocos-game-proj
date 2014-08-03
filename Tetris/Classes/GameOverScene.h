#ifndef __TERIS_GAMEOVER_SCENE_H__
#define __TERIS_GAMEOVER_SCENE_H__


#include "cocos2d.h"

USING_NS_CC;

 class GameOverLayer : public LayerColor 
 {      
 public: 
	 GameOverLayer():_label(NULL) {  };      
	 virtual ~GameOverLayer();      
	 bool init();      
	 CREATE_FUNC(GameOverLayer);
	 void gameOverDone();
	 CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label); 
 };
 
 class GameOverScene : public cocos2d::Scene 
 {      
 public: 
	 GameOverScene():_layer(NULL) { };      
	 ~GameOverScene();      
	 bool init();      
	 CREATE_FUNC(GameOverScene);       
	 CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);     
 };

 #endif // __TERIS_GAMEOVER_SCENE_H__