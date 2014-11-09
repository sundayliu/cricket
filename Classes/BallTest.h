#ifndef  _BallTest_H_
#define  _BallTest_H_

#include "cocos2d.h"

class  BallTest : public cocos2d::CCSprite
{
public:
	int mark;
	float x;
	float y;
	bool hitFlag;

public:
    	BallTest();
    	static BallTest* create(const char* pic);

    void setMark(int mark);
    int getMark();
    void setXY(float x,float y);
    void setHitFlag(bool b);
    bool getHitFlag();
};

#endif
