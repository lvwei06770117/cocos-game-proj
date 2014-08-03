
#include <stdlib.h>
#include <time.h>

#include "TerisShape.h"

USING_NS_CC;

int shape[7][4][4]  = {
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
	{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}
};

TetrisShape::TetrisShape(int row,int col,int cWidth,int bWidth,int x,int y):rowIndex(row),colIndex(col),
	cellWidth(cWidth),borderWidth(bWidth),marginX(x),marginY(y)
{
	srand((unsigned)time(NULL));
	int shapeIndex = rand() % 7;
	for(int j = 0 ; j < 4 ; j++)    
	{
		for(int  i= 0; i < 4 ; i++) 
		{
			shape_matrix[j][i] = shape[shapeIndex][j][i];
		}
	}
}

TetrisShape::~TetrisShape()
{
}

int TetrisShape::getWidth()
{
	for (int j = 3; j >= 0; j--)
	{
		for (int i = 0; i < 4; i++)
		{
			if(shape_matrix[i][j] > 0)
				return j + 1;
		}
	}
	return 0;
}

int TetrisShape::getHeight()
{
	for (int i = 3; i >= 0; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			if(shape_matrix[i][j] > 0)
				return i + 1;
		}
	}
	return 0;
}

int TetrisShape::ShapeX(int i)
{
	return ( colIndex + i ) * ( cellWidth + borderWidth ) + borderWidth;
}

int TetrisShape::ShapeY(int j)
{
	//return ( colIndex - j ) * ( cellWidth + borderWidth ) + borderWidth;
	return ( rowIndex - j ) * ( cellWidth + borderWidth ) + borderWidth;
}

bool TetrisShape::isFullCell(int x,int y)
{
	return shape_matrix[x][y] == 1;
}

DrawNode* TetrisShape::drawShape()
{
	auto draw = DrawNode::create();

	for(int j = 0 ; j < 4 ; j++) {
		for(int  i= 0; i < 4 ; i++) {
			if(shape_matrix[j][i]>0) {
				
				int x1 = ShapeX(i) + marginX;
				int x2 = x1 + cellWidth;
				int y1 = ShapeY(j) + marginY;
				int y2 = y1 + cellWidth;
				Point points[] = { Point(x1,y1), Point(x1,y2), Point(x2,y2),Point(x2,y1) };
				draw->drawPolygon(points,sizeof(points)/sizeof(points[0]),Color4F(1,0,0,0.5),0,Color4F(0,0,1,1));
			}
		}
	}

	return draw;
}

DrawNode* TetrisShape::shapeMove(TerisDirection dir)
{
	switch (dir)
	{
	case MoveUp:

		break;
	case MoveDown:
		rowIndex--;
		break;
	case MoveLeft:
		colIndex--;
		break;
	case MoveRight:
		colIndex++;
		break;
	default:
		break;
	}
	
	return drawShape();
}

DrawNode* TetrisShape::shapeRotate()
{
	int rows = 4;
	for (int i = 0 ; i < rows/2 ; i++)
	{
		int m=rows-i*2;
		if (m==1) break;
		for (int j = i; j < m+i-1;j++)
		{
			int tmp=shape_matrix[i][j];
			shape_matrix[i][j]=shape_matrix[rows-j-1][i];
			shape_matrix[rows-j-1][i]=shape_matrix[rows-i-1][rows-j-1];
			shape_matrix[rows-i-1][rows-j-1]=shape_matrix[j][rows-i-1];
			shape_matrix[j][rows-i-1]=tmp;
		}
	}
	return drawShape();

}

