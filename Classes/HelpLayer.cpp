#include "HelpLayer.h"
#include "AppMacros.h"
#include "DialogLayer.h"
#include <string.h>
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
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
bool HelpLayer::init()
{
    //调用父类的初始化
    if ( !CCLayer::init() )
    {
        return false;
    }

    //开启按键监听
    setKeypadEnabled(true);
    //获取可见区域尺寸
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //创建一个精灵对象，充当背景
    backSprite = CCSprite::create("pic/bckgr_2.png");
    //设置精灵对象的位置
    backSprite->setPosition(ccp(origin.x, origin.y));
    backSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
    //将背景精灵添加到布景中
    this->addChild(backSprite, BACKGROUND_LEVEL_WYF);

    //创建一个精灵对象，充当物体
    CCSprite *playSprite = CCSprite::create("pic/about.png");
	//设置精灵对象的位置
    playSprite->setPosition(ccp(200, 320));
	//将背景精灵添加到布景中
	this->addChild(playSprite, GAME_LEVEL_WYF);

	//创建一个精灵对象，充当物体
	CCSprite *helpSprite = CCSprite::create("pic/help1.png");
	//设置精灵对象的位置
	helpSprite->setPosition(ccp(600, 320));
	//将背景精灵添加到布景中
	this->addChild(helpSprite, GAME_LEVEL_WYF);

	//创建home菜单项
	CCMenuItemImage *pRightItem = CCMenuItemImage::create
	(
		 "pic/menuHome.png",     //平时的图片
		 "pic/menuHome2.png",   //选中时的图片
		 this,
		 menu_selector(HelpLayer::playGameCallback)//点击时执行的回调方法
	);
	//设置home菜单项的位置
	pRightItem->setPosition
	(
		ccp
		(
			origin.x+visibleSize.width/2,//X坐标
			origin.y+visibleSize.height-380					//Y坐标
		 )
	 );

	//创建下一箭头菜单对象
	CCMenu* pMenuRight = CCMenu::create(pRightItem, NULL);
	//设置下一箭头菜单位置
	pMenuRight->setPosition(CCPointZero);
	//将下一箭头菜单添加到布景中
	this->addChild(pMenuRight, 2);

    return true;
}

//实现FromLayer类中的下一个菜单的回调方法
void HelpLayer::playGameCallback(CCObject* pSender)
{
	  tsm->toBeginLayer();
}

//实现FromLayer类中的menuCloseCallback方法，处理关闭菜单项点击事件
void HelpLayer::menuCloseCallback(CCObject* pSender)
{
	//退出
    CCDirector::sharedDirector()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
      exit(0);
    #endif
}

//返回键监听
void HelpLayer::keyBackClicked()
{
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	tsm->toBeginLayer();
}

