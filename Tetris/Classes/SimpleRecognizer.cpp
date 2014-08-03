
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
	//ÿ�������ƶ�ʱ,�ڵ�ǰ�����֮ǰ����֮����㲻ͬ��x�����y����
    double dx = this->points[len - 1].x - this->points[0].x;
    double dy = this->points[len - 1].y - this->points[0].y;

	if (abs(dx) > abs(dy)) {
        //�����������,�˶����ƵĴ�����x�᷽��
        if (dx > 50) {
            newRtn = SimpleGesturesRight;
        } else if ( dx < -50 ) {
            newRtn = SimpleGesturesLeft;
        }
    } else {
        //�����������,�˶����ƵĴ�����y�᷽��
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

