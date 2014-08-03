#ifndef __SimpleRecognizer_H__
#define __SimpleRecognizer__

#include "cocos2d.h"

USING_NS_CC;

typedef enum {
	SimpleGesturesRight,
	SimpleGesturesLeft,
	SimpleGesturesUp,//
	SimpleGesturesDown,//
	SimpleGesturesError,//
	SimpleGesturesNotSupport
    
} SimpleGestures;

class SimpleRecognizer
{
protected:
	//--- These are variables because C++ doesn't (easily) allow
	//---  constants to be floating point numbers
	double X;
	double Y;
	SimpleGestures result;
    std::vector<Point> points;
    
public:
	SimpleRecognizer();
    
	void beginPoint(Point point);
	void movePoint(Point point);
	SimpleGestures endPoint(Point point);
    
    std::vector<Point>& getPoints();
    
};

#endif