
#include "MatrixNode.h"

USING_NS_CC;

enum 
{
    kTagDrawer = 1,
};


int matrixBox[7][4][4]  = {
	{{1,1,1,1},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,1,0},{1,0,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,1,0},{0,1,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,1,0},{0,0,1,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}},
	{{0,1,1,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}},
	{{1,1,0,0},{1,1,0,0},{0,0,0,0},{0,0,0,0}}
};

MatrixNode* MatrixNode::createMatrixSprite(int _cellWidth,int _borderWidth)
{
	MatrixNode* matrix = new MatrixNode(_cellWidth,_borderWidth);
	if(matrix&&matrix->init())
	{
		matrix->autorelease();
		//matrix->initMatrixBox(_cellWidth,_borderWidth);
		return matrix;
	}

	CC_SAFE_DELETE(matrix);
    
	return NULL;
}

MatrixNode::~MatrixNode()
{

}

MatrixNode::MatrixNode(int _cellWidth,int _borderWidth):cellWidth(_cellWidth),borderWidth(_borderWidth),rows(4)
{
	//getWidth();
	//rows = 4;	
}

bool MatrixNode::init()
{

	if(!Sprite::init())
	{
		return false;
	}
	int w = (cellWidth+borderWidth)*rows;
	
	setContentSize(Size(w,w));
	createMatrixNode();
	
	drawMatrixBox();
	return true;
}

void MatrixNode::createMatrixNode()
{
	int boxId = CCRANDOM_0_1() * 7;        //生成0~6随机数
	for(int j = 0 ; j < 4 ; j++)    
	{
		for(int  i= 0; i < 4 ; i++) 
		{
			m_matrix[j][i] = matrixBox[boxId][j][i];
		}
	}
}

/*
void MatrixNode::getWidth()
{
	for (int j = 3; j >= 0; j--)
	{
		for (int i = 0; i < 4; i++)
		{
			if (matrixBox[i][j]>0)
			{
				rows = j + 1;
			}
		}
	}
}*/

void MatrixNode::drawMatrixBox()
{
	auto drawOld = getChildByTag(kTagDrawer);
	if(drawOld)
	{
		removeChild(drawOld,true);
	}

	auto draw = DrawNode::create();
	addChild(draw,1,kTagDrawer);
	Size s = getContentSize();
	for(int j = 0 ; j < 4 ; j++)    
	{
	for(int  i= 0; i < 4 ; i++) 
	{
		if(m_matrix[j][i]>0)
		{
			int x1 = j*(cellWidth+borderWidth)+borderWidth;
			int x2 = (j+1)*(cellWidth+borderWidth);
			int y1 = (3-i)*(cellWidth+borderWidth)+borderWidth;
			int y2 = (4-i)*(cellWidth+borderWidth);
			Point points[] = { Point(x1,y1), Point(x1,y2), Point(x2,y2),Point(x2,y1) };
			draw->drawPolygon(points,sizeof(points)/sizeof(points[0]),Color4F(1,0,0,0.5),0,Color4F(0,0,1,1));
		}
	}
	}	 
}

int MatrixNode::getRows()
{
	return rows;
}

void MatrixNode::rotateMatrix()
{
	for (int i=0;i<rows/2;i++)
	{
		int m=rows-i*2;
		if (m==1) break;
		for (int j = i; j < m+i-1;j++)
		{
			int tmp=m_matrix[i][j];
			m_matrix[i][j]=m_matrix[rows-j-1][i];
			m_matrix[rows-j-1][i]=m_matrix[rows-i-1][rows-j-1];
			m_matrix[rows-i-1][rows-j-1]=m_matrix[j][rows-i-1];
			m_matrix[j][rows-i-1]=tmp;
		}
	}
	drawMatrixBox();
}

