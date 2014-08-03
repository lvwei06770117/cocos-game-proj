#ifndef __TETRIS_GameSCENE_H__
#define __TETRIS_GameSCENE_H__

#include "cocos2d.h"
#include "TerisShape.h"
#include "SimpleRecognizer.h"

USING_NS_CC;

#define TETRIS_COL_NUMS 10 //����˹��������
#define TETRIS_ROW_NUMS 21 //����˹��������
#define TETRIS_LINE_Width 1 //�߿�

struct box
{
	bool isfull;
	int color;
};

class GameLayer : public Layer
{
public:
    static Scene* createScene();
	virtual bool init();  
	// implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
	virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;
	
	//�����¼������ص�����
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);
	virtual void onTouchEnded(Touch* touch, Event* event);

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

protected:
    void onDraw(const kmMat4 &transform, bool transformUpdated);
    CustomCommand _customCommand;
private:
	//�������˹����ÿ�����ӵĿ�ȣ���Ϊ�������Σ����Ը߶�=���
	void MeasureCellWidth();

	void newShape();
	void shapeMove(float dt);
	bool isMoveLeft();
	bool isMoveRight();
	bool isMoveDown();
	bool isChange();
	bool isGameOver();

	void clearFullLine();

private:
	int score;
	int cellWidth;
	int leftBottomX;
	int leftBottomY;
	//MatrixNode* matrix;

	int dir;
	TetrisShape* shape;
	SimpleRecognizer recognizer;
	bool is_fullline[TETRIS_ROW_NUMS];
	box matrix_box[TETRIS_ROW_NUMS][TETRIS_COL_NUMS];
	int shapeNum;
};

#endif