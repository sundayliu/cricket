
#include "FielderSprite.h"
//#include <android/log.h>
#include <string.h>
#include <vector>
#include <math.h>
#include "AppMacros.h"

//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
//#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

//USING_NS_CC;
using namespace cocos2d;

//构造函数
FielderSprite::FielderSprite()
{

}
FielderSprite* FielderSprite::create(const char* pic)
{
	FielderSprite* temp = NULL;
	temp = new FielderSprite();
	temp->initWithFile(pic);
	temp->autorelease();
	return temp;
}

void FielderSprite::setMark(int mark)
{
	this->mark=mark;
}
int FielderSprite::getMark()
{
	return this->mark;
}
