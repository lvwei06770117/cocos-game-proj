#ifndef __TETRIS_MatrixNode_H__
#define __TETRIS_MatrixNode_H__

#include "cocos2d.h";

USING_NS_CC;

class MatrixNode : public Sprite
{
public:
	static MatrixNode* createMatrixSprite(int _cellWidth,int _borderWidth);
	MatrixNode(int _cellWidth,int _borderWidth);
	virtual bool init() override;
	~MatrixNode();
	int getRows();
	void rotateMatrix();
	
private:
	void createMatrixNode();
	//void getWidth();
	//void getHeight();
	void drawMatrixBox();
private:
	int m_matrix[4][4];
	int rows;
	//int height;
	int cellWidth;
	int borderWidth;

};

#endif