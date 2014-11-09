
#include "BallTest.h"
#include <string.h>
#include <vector>
#include <math.h>
#include "AppMacros.h"

#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#endif

//USING_NS_CC;
using namespace cocos2d;

//构造函数
BallTest::BallTest()
{

}
BallTest* BallTest::create(const char* pic)
{
	BallTest* temp = NULL;
	temp = new BallTest();
	temp->initWithFile(pic);
	temp->autorelease();
	return temp;
}

void BallTest::setHitFlag(bool b)
{
	this->hitFlag = b;
}

bool BallTest::getHitFlag()
{
	return this->hitFlag;
}

void BallTest::setMark(int mark)
{
	this->mark=mark;
	switch(mark)
	{
	case 1://加载粒子系统
		CCParticleSystem* cps = CCParticleSun::create();
		cps->retain();
		this->addChild(cps, 10);
		cps->setPosition( ccp( 0, 7) );
		cps->setLife(0.06f);break;
	}

}
int BallTest::getMark()
{
	return this->mark;
}
void BallTest::setXY(float x,float y)
{
	float vx=x-OUTBALL_X;
	float vy=y-OUTBALL_Y;
	float l=sqrt(vx*vx+vy*vy);
	this->x=vx/l;
	this->y=vy/l;
	this->mark=0;
}

