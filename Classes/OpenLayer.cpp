#include "OpenLayer.h"
#include "AppMacros.h"
#include <string.h>
#include "cocos2d.h"
#include "BanQiuSceneManager.h"

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

//实现GuoguanLayer类中的init方法，初始化布景
bool OpenLayer::init()
{
    //调用父类的初始化
    if ( !CCLayer::init() )
    {
        return false;
    }
    //获取可见区域尺寸
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //创建一个精灵对象，充当物体
	CCSprite *bn = CCSprite::create("pic/bn.png");
	//设置精灵对象的位置
	bn->setPosition(ccp(400, 240));
	bn->setOpacity(0);//把透明度设置为0
	//将精灵添加到布景中
	this->addChild(bn, GAME_LEVEL_WYF);
	CCActionInterval *act=CCFadeIn::create(1.5f);
	CCActionInterval *act2=act->reverse();
	bn->runAction(CCSequence::create(
	act,
	act2,
	CCCallFuncND::create(this, callfuncND_selector(OpenLayer::playGameCallback),NULL),
	NULL
	)
	);

    return true;
}

//实现FromLayer类中的下一个菜单的回调方法
void OpenLayer::playGameCallback(CCNode* node,void* param)
{
	  man->toBeginLayer();
}


