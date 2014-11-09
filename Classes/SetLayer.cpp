#include "SetLayer.h"
#include "AppMacros.h"
#include <string.h>
#include "DialogLayer.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "BanQiuSceneManager.h"
#include "UserRecord.h"
//#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
//#include <android/log.h>
//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
//#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
//#else
//#define LOGI(...)
//#define LOGW(...)
//#endif

//USING_NS_CC;
using namespace cocos2d;

//实现GuoguanLayer类中的init方法，初始化布景
bool SetLayer::init()
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

	//创建背景音乐菜单项
	CCMenuItemImage *backMusicItem = CCMenuItemImage::create
	(
		 "pic/backMusic.png",     //平时的图片
		 "pic/backMusic2.png",   //选中时的图片
		 this,
		 menu_selector(SetLayer::setBackMusic)//点击时执行的回调方法
	);
	//设置背景音乐菜单项的位置
	backMusicItem->setPosition(ccp(350,340));

	//小喇叭OK
	lbokSprite = CCSprite::create("pic/labaok.png");
    //设置精灵对象的位置
	lbokSprite->setPosition(ccp(600,340));
    //将背景精灵添加到布景中
    this->addChild(lbokSprite, GAME_LEVEL_WYF);

    //小喇叭NO
	lbnoSprite = CCSprite::create("pic/labano.png");
	//设置精灵对象的位置
	lbnoSprite->setPosition(ccp(600,340));

	//设置喇叭的状态
	if(BACKMUSIC)
	{
		lbokSprite->setVisible(true);
		lbnoSprite->setVisible(false);
	}
	else
	{
		lbokSprite->setVisible(false);
		lbnoSprite->setVisible(true);
	}

	//将背景精灵添加到布景中
	this->addChild(lbnoSprite, GAME_LEVEL_WYF);

	//创建音效菜单项
	CCMenuItemImage *musicItem = CCMenuItemImage::create
	(
		 "pic/music.png",     //平时的图片
		 "pic/music2.png",   //选中时的图片
		 this,
		 menu_selector(SetLayer::setMusic)//点击时执行的回调方法
	);
	//设置音效菜单项的位置
	musicItem->setPosition(ccp(350,240));

	//小喇叭2ok
	lb2okSprite = CCSprite::create("pic/labaok.png");
	//设置精灵对象的位置
	lb2okSprite->setPosition(ccp(600,240));
	//将背景精灵添加到布景中
	this->addChild(lb2okSprite, GAME_LEVEL_WYF);

	//小喇叭2no
	lb2noSprite = CCSprite::create("pic/labano.png");
	//设置精灵对象的位置
	lb2noSprite->setPosition(ccp(600,240));

	//设置喇叭的状态
	if(MUSIC)
	{
		lb2okSprite->setVisible(true);
		lb2noSprite->setVisible(false);
	}
	else
	{
		lb2okSprite->setVisible(false);
		lb2noSprite->setVisible(true);
	}

	//将背景精灵添加到布景中
	this->addChild(lb2noSprite, GAME_LEVEL_WYF);

	//创建home菜单项
	CCMenuItemImage *backItem = CCMenuItemImage::create
	(
		 "pic/menuHome.png",     //平时的图片
		 "pic/menuHome2.png",   //选中时的图片
		 this,
		 menu_selector(SetLayer::backCallback)//点击时执行的回调方法
	);
	//设置音效菜单项的位置
	backItem->setPosition(ccp(350,140));

	//创建菜单对象
	CCMenu* pMenuRight = CCMenu::create(backMusicItem,musicItem,backItem, NULL);
	//设置菜单位置
	pMenuRight->setPosition(CCPointZero);
	//将菜单添加到布景中
	this->addChild(pMenuRight, DASHBOARD_LEVEL_WYF);

    return true;
}

//实现类中的方法，处理返回菜单项点击事件
void SetLayer::backCallback(CCObject* pSender)
{
	man->toBeginLayer();
}

//设置喇叭的状态
void SetLayer::setBackMusic()
{
	BACKMUSIC=!BACKMUSIC;//状态置反

	UserRecord::getInstance()->saveBool("backMusic",BACKMUSIC);
    
	if(BACKMUSIC)
	{
		lbokSprite->setVisible(true);
		lbnoSprite->setVisible(false);
		//播放背景音乐
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic
		(
			"sound/background.mp3",
			true
		);
	}
	else
	{
		lbokSprite->setVisible(false);
		lbnoSprite->setVisible(true);
		//暂停声音播放
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	}
}

//设置喇叭的状态
void SetLayer::setMusic()
{
	MUSIC=!MUSIC;//状态置反


	UserRecord::getInstance()->saveBool("music",MUSIC);

	if(MUSIC)
	{
		lb2okSprite->setVisible(true);
		lb2noSprite->setVisible(false);
	}
	else
	{
		lb2okSprite->setVisible(false);
		lb2noSprite->setVisible(true);
	}
}

//返回键监听
void SetLayer::keyBackClicked()
{
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	man->toBeginLayer();
}
