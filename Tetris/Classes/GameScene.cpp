
#include<math.h>

#include "GameScene.h"
#include "GameOverScene.h"

USING_NS_CC;

enum 
{
    kTagShapeNode = 1,
};

Scene* GameLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
	//////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	MeasureCellWidth();

	//matrix = MatrixNode::createMatrixSprite(cellWidth,TETRIS_LINE_Width);
	//int rows = matrix->getRows();
	//float x = (3+rows/2.0f)* (cellWidth + TETRIS_LINE_Width )+leftBottomX;
	//float y = (TETRIS_ROW_NUMS-rows/2.0f)*(cellWidth + TETRIS_LINE_Width )+leftBottomY;

	//float x = 3* (cellWidth + TETRIS_LINE_Width )+leftBottomX;
	//float y = (TETRIS_ROW_NUMS-rows)*(cellWidth + TETRIS_LINE_Width )+leftBottomY;

	//addChild(matrix,1);
	//matrix->setPosition(x,y);

	for (int i = 0; i < TETRIS_ROW_NUMS; i++)
	{
		for (int j = 0; j < TETRIS_COL_NUMS; j++)
		{
			matrix_box[i][j].isfull = false;
			matrix_box[i][j].color = 1;
		}
	}

	for (int i = 0; i < TETRIS_ROW_NUMS; i++)
	{
		is_fullline[i] = false;
	}

	shapeNum = 0;
	newShape();
	//this->schedule(schedule_selector(GameLayer::shapeMove), 1.0f/10);
	this->schedule(schedule_selector(GameLayer::shapeMove), 1.0f);

	//设置触摸事件监听
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//设置键盘事件监听
	auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(GameLayer::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(GameLayer::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	return true;
}

void GameLayer::draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated)
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(GameLayer::onDraw, this, transform, transformUpdated);
    renderer->addCommand(&_customCommand);
}

void GameLayer::onDraw(const kmMat4 &transform, bool transformUpdated)
{
	kmGLPushMatrix();
    kmGLLoadMatrix(&transform);

	 //draw
    CHECK_GL_ERROR_DEBUG();

	glLineWidth( TETRIS_LINE_Width );

	DrawPrimitives::setDrawColor4B(255,0,0,255);
	for (int i = 0; i <= TETRIS_ROW_NUMS; i++)
	{
		Point startPosition = Point(leftBottomX , leftBottomY + i * (cellWidth + TETRIS_LINE_Width ));
		Point endPosition = Point(leftBottomX+TETRIS_COL_NUMS*(cellWidth+TETRIS_LINE_Width),leftBottomY + i * (cellWidth + TETRIS_LINE_Width));
		DrawPrimitives::drawLine( startPosition,endPosition );
	}
	CHECK_GL_ERROR_DEBUG();

	for (int i = 0; i <= TETRIS_COL_NUMS; i++)
	{
		Point startPosition = Point(leftBottomX + i * (cellWidth + TETRIS_LINE_Width) , leftBottomY);
		Point endPosition = Point(leftBottomX + i * (cellWidth + TETRIS_LINE_Width),leftBottomY + TETRIS_ROW_NUMS * ( cellWidth + TETRIS_LINE_Width ));
		DrawPrimitives::drawLine( startPosition,endPosition );
	}
	
	CHECK_GL_ERROR_DEBUG();

    //end draw
    kmGLPopMatrix();
}

void GameLayer::MeasureCellWidth()
{
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	 leftBottomX = 100;
	 leftBottomY = 40;
	 int hor_width = (visibleSize.width- (TETRIS_COL_NUMS+1)*TETRIS_LINE_Width-leftBottomX*2)/TETRIS_COL_NUMS;
	 int ver_width = (visibleSize.height-(TETRIS_ROW_NUMS+1)*TETRIS_LINE_Width-leftBottomY*2)/TETRIS_ROW_NUMS;
	 cellWidth = MIN(hor_width,ver_width);
}

bool GameLayer::isMoveLeft()
{
	if(shape && shape->getColIndex() == 0)
		return false;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(shape && shape->isFullCell(i,j))
			{
				int row = shape->getRowIndex() - i;
				int col = shape->getColIndex() + j - 1;
				if(col < 0 || matrix_box[row][col].isfull)
					return false;
			}
		}
	}
	
	return true;
}

bool GameLayer::isMoveRight()
{
	//int index = shape->getColIndex() + shape->getWidth();
	if(shape && (shape->getColIndex()+ shape->getWidth()) >= TETRIS_COL_NUMS)
	{
		return false;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(shape && shape->isFullCell(i,j))
			{
				int row = shape->getRowIndex() - i;
				int col = shape->getColIndex() + j + 1;
				//出有边界或者已经有格子
				if(col >= TETRIS_COL_NUMS || matrix_box[row][col].isfull)
					return false;
			}
		}
	}

	return true;
}

bool GameLayer::isMoveDown()
{
	//0 based index,so plus 1
	if(shape && (shape->getRowIndex()-shape->getHeight() + 1) == 0)
		return false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(shape && shape->isFullCell(i,j))
			{
				int row = shape->getRowIndex() - i - 1;
				int col = shape->getColIndex() + j;
				if(row < 0 || matrix_box[row][col].isfull)
					return false;
			}
		}
	}
	return true;
}

bool GameLayer::isChange()
{
	int rows = 4;
	int row = 0;
	int col = 0;
	for (int i = 0 ; i < rows/2 ; i++)
	{
		int m=rows-i*2;
		if (m==1) break;
		for (int j = i; j < m+i-1;j++)
		{
			if(shape->isFullCell(i,j)) // j,rows - i - 1
			{
				row = shape->getRowIndex() - j;
				col = shape->getColIndex() + (rows - i - 1);
				if(row < 0 || row >= TETRIS_ROW_NUMS || 
					col < 0 || col >= TETRIS_COL_NUMS || 
					matrix_box[row][col].isfull )
					return false;
			}

			if(shape->isFullCell(j,rows-i-1)) //  rows - i - 1 ,rows - j - 1
			{
				row = shape->getRowIndex() - (rows - i - 1);
				col = shape->getColIndex() + (rows - j - 1);

				if(row < 0 || row >= TETRIS_ROW_NUMS || 
					col < 0 || col >= TETRIS_COL_NUMS || 
					matrix_box[row][col].isfull )
					return false;
			}

			if(shape->isFullCell(rows-i-1,rows-j-1)) // rows-j-1,i
			{
				row = shape->getRowIndex() - (rows-j-1);
				col = shape->getColIndex() + i;
				if(row < 0 || row >= TETRIS_ROW_NUMS || 
					col < 0 || col >= TETRIS_COL_NUMS || 
					matrix_box[row][col].isfull )
					return false;
			}
			if(shape->isFullCell(rows-j-1,i)) //i,j
			{
				row = shape->getRowIndex() - i;
				col = shape->getColIndex() + j;
				if(row < 0 || row >= TETRIS_ROW_NUMS || 
					col < 0 || col >= TETRIS_COL_NUMS || 
					matrix_box[row][col].isfull )
					return false;
			}
		}
	}
	return true;
}

bool GameLayer::isGameOver()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if(shape && shape->isFullCell(i,j))
			{
				int row = shape->getRowIndex() - i;
				int col = shape->getColIndex() + j;
				if(matrix_box[row][col].isfull)
					return true;
			}
		}
	}
	return false;
}

void GameLayer::newShape()
{	
	shape = new TetrisShape(20,3,cellWidth,TETRIS_LINE_Width,leftBottomX,leftBottomY);
	if(isGameOver())
	{
		auto gameOverScene = GameOverScene::create(); 
		gameOverScene->getLayer()->getLabel()->setString("You Lose :[");  
		Director::getInstance()->replaceScene(gameOverScene);
	}
	else
	{
		auto shapeNode = shape->drawShape();
		shapeNum++;
		this->addChild(shapeNode,100,(kTagShapeNode + shapeNum));
	}
	
}

void GameLayer::clearFullLine()
{

}

void GameLayer::shapeMove(float dt)
{
	
	if(isMoveDown())
	{
		auto s = (DrawNode*) getChildByTag(kTagShapeNode + shapeNum);
		this->removeChild(s);
		auto shapeNode = shape->shapeMove(MoveDown);
		this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int row = shape->getRowIndex() - i;
				int col = shape->getColIndex() + j;			

				if(col>=0 && col <= TETRIS_COL_NUMS
					&&row>=0 && row <= TETRIS_ROW_NUMS)
					matrix_box[row][col].isfull = shape->isFullCell(i,j);
			}
		}
		delete shape;
		newShape();
	}
}

bool GameLayer::onTouchBegan(Touch* touch, Event* event)
{
	Point beginTouch = touch->getLocation();   
	recognizer.beginPoint(beginTouch);
	return true;
}

void GameLayer::onTouchMoved(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	recognizer.movePoint(pos);
}

void GameLayer::onTouchEnded(Touch* touch, Event* event)
{
	Point pos = touch->getLocation();
	SimpleGestures rtn = recognizer.endPoint(pos);
	DrawNode* shapeNode = nullptr;
	switch (rtn)
	{
	case SimpleGesturesLeft:
		if(isMoveLeft())
		{
			this->removeChildByTag(kTagShapeNode + shapeNum);
			shapeNode = shape->shapeMove(MoveLeft);
			this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
		}
		break;
	case SimpleGesturesRight:
		if(isMoveRight())
		{
			this->removeChildByTag(kTagShapeNode + shapeNum);
			shapeNode = shape->shapeMove(MoveRight);
			this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
		}
		break;
	case SimpleGesturesDown:
		
		break;
	case SimpleGesturesUp:
		//变形临界检测
		if(isChange())
		{
			this->removeChildByTag(kTagShapeNode + shapeNum);
			shapeNode = shape->shapeRotate();
			this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
		}
		break;
	default:
		break;
	}
}

void GameLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	
}

void GameLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	DrawNode* shapeNode = nullptr;
	if(keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		if(isMoveLeft())
		{
			this->removeChildByTag(kTagShapeNode + shapeNum);
			shapeNode = shape->shapeMove(MoveLeft);
			this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
		}
	}
	if(keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		if(isMoveRight())
		{
			this->removeChildByTag(kTagShapeNode + shapeNum);
			shapeNode = shape->shapeMove(MoveRight);
			this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
		}
	}
	if(keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{

	}
	if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		//变形临界检测
		if(isChange())
		{
			this->removeChildByTag(kTagShapeNode + shapeNum);
			shapeNode = shape->shapeRotate();
			this->addChild(shapeNode,100,kTagShapeNode + shapeNum);
		}
	}
}
