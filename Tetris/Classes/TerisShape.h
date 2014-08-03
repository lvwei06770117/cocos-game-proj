#ifndef __TETRIS_Shape_H__
#define __TETRIS_Shape_H__

#include "cocos2d.h"

USING_NS_CC;

typedef enum{
	MoveLeft,
	MoveRight,
	MoveDown,
	MoveUp
}TerisDirection;

class TetrisShape
{
public:
	TetrisShape(int row,int col,int cWidth,int bWidth,int x,int y);
	~TetrisShape();

	int ShapeX(int i);
	int ShapeY(int j);	
	int getRowIndex(){return rowIndex; }
	int getColIndex(){return colIndex; }
	int getWidth();
	int getHeight();
	bool isFullCell(int x,int y);
	DrawNode * drawShape();
	DrawNode * shapeMove(TerisDirection dir);
	DrawNode * shapeRotate();

private:
	int rowIndex;//�к�
	int colIndex;//�к�
	int marginX;
	int marginY;
	int color;

	int cellWidth; //���ӿ��
	int borderWidth; //�����߿��
	int shape_matrix[4][4]; //��״�������
};

#endif