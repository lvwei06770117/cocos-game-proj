
#include "SimpleRecognizer.h"

USING_NS_CC;

SimpleRecognizer::SimpleRecognizer()
{
	this->result = SimpleGesturesError;
}

void SimpleRecognizer::beginPoint(Point point)
{
	this->result = SimpleGesturesError;
	this->points.clear();
	this->points.push_back(point);
}

void SimpleRecognizer::movePoint(Point point)
{
	this->points.push_back(point);
}

SimpleGestures SimpleRecognizer::endPoint(Point point)
{
	this->points.push_back(point);
	int len = this->points.size();
	if(len < 3)
	{
		return SimpleGesturesError;
	}
	SimpleGestures newRtn = SimpleGesturesError;
	//每当触点移动时,在当前触点和之前触点之间计算不同的x坐标和y坐标
    double dx = this->points[len - 1].x - this->points[0].x;
    double dy = this->points[len - 1].y - this->points[0].y;

	if (abs(dx) > abs(dy)) {
        //在这种情况下,运动趋势的触点在x轴方向
        if (dx > 50) {
            newRtn = SimpleGesturesRight;
        } else if ( dx < -50 ) {
            newRtn = SimpleGesturesLeft;
        }
    } else {
        //在这种情况下,运动趋势的触点在y轴方向
        if (dy > 50) {
            newRtn = SimpleGesturesUp;
        } else if ( dy < -50 ) {
            newRtn = SimpleGesturesDown;
        }
    }

	// first set result
    if (result == SimpleGesturesError) {
        result = newRtn;
    }

    // if diretcory change, not support Recongnizer
    if (result != newRtn) {
        result = SimpleGesturesNotSupport;
    }
    return result;
}

std::vector<Point>& SimpleRecognizer::getPoints()
{
	return points;
}

