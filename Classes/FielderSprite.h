#ifndef  _FielderSprite_H_
#define  _FielderSprite_H_

#include "cocos2d.h"

//自己写的cocos2dx应用程序要继承CCApplication
class  FielderSprite : public cocos2d::CCSprite
{
public:
	int mark;//记录走的哪条路线1,2,...,6
	long stopTime;//吃道具停止的时间
	cocos2d::CCActionInterval* ccat;//记录路线
public:
		FielderSprite();
    	static FielderSprite* create(const char* pic);
//    virtual ~Ball();
//    virtual CCSprite* create (const char * pszFileName);
//    virtual void setPosition(const CCPoint &anchorPoint);
//    virtual void setAnchorPoint (const CCPoint &anchorPoint);
    void setMark(int mark);
    int getMark();
};

#endif
