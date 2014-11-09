#ifndef  _Prop_H_
#define  _Prop_H_

#include "cocos2d.h"

//自己写的cocos2dx应用程序要继承CCApplication
class  Prop : public cocos2d::CCSprite
{
public:
	int mark;//0代表火球 ，1代表停止 ，2代表出一片火
	float cTime;//出道具的时间

public:
	Prop();
    	static Prop* create(const char* pic);

};

#endif
