#include "OutLayer.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
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
bool OutLayer::init()
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

    //创建一个精灵对象，
    backSprite = CCSprite::create("pic/confirm.png");
    //设置精灵对象的位置
    backSprite->setPosition(ccp(400,300));
    //将精灵添加到布景中
    this->addChild(backSprite, BACKGROUND_LEVEL_WYF);

	//创建yes菜单项
	CCMenuItemImage *yesItem = CCMenuItemImage::create
	(
		 "pic/yes.png",     //平时的图片
		 "pic/yes1.png",   //选中时的图片
		 this,
		 menu_selector(OutLayer::yesCallback)//点击时执行的回调方法
	);
	//设置yes菜单项的位置
	yesItem->setPosition(ccp(325,200));

	//创建no菜单项
	CCMenuItemImage *noItem = CCMenuItemImage::create
	(
		 "pic/no.png",     //平时的图片
		 "pic/no1.png",   //选中时的图片
		 this,
		 menu_selector(OutLayer::noCallback)//点击时执行的回调方法
	);
	//设置yes菜单项的位置
	noItem->setPosition(ccp(475,200));

	//创建菜单对象
	CCMenu* pMenuRight = CCMenu::create(yesItem,noItem, NULL);
	//设置菜单位置
	pMenuRight->setPosition(CCPointZero);
	//将下一箭头菜单添加到布景中
	this->addChild(pMenuRight, DASHBOARD_LEVEL_WYF);
    return true;
}

//实现类中的回调方法
void OutLayer::noCallback(CCObject* pSender)
{
	man->toBeginLayer();
	if(BACKMUSIC)
	{
		//继续声音
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
}

//实现FromLayer类中的menuCloseCallback方法，处理关闭菜单项点击事件
void OutLayer::yesCallback(CCObject* pSender)
{
	//退出
    CCDirector::sharedDirector()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
      exit(0);
    #endif
}
