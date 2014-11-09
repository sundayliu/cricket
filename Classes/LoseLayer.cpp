#include "LoseLayer.h"
//#include "GameSceneManager.h"
#include "AppMacros.h"
#include <string.h>
#include "SimpleAudioEngine.h"

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

//实现LoseLayer类中的init方法，初始化布景
bool LoseLayer::init()
{
    //调用父类的初始化
    if ( !CCLayer::init() )
    {
        return false;
    }
    setKeypadEnabled(true);
    //获取可见区域尺寸
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    origin = CCDirector::sharedDirector()->getVisibleOrigin();

   //创建一个精灵对象，包含背景图片
   CCSprite* bSprite = CCSprite::create("pic/bckgr.png");
   //设置精灵对象的位置
   bSprite->setPosition(ccp(origin.x, origin.y));
   bSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5

   //将精灵添加到布景中
   this->addChild(bSprite, 0);
   //====================================================================
   //创建一个失败的精灵
   CCSprite* oSprite = CCSprite::create("pic/out.png");
  //设置精灵对象的位置
   oSprite->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+280));
  //将精灵添加到布景中
   this->addChild(oSprite, GAME_LEVEL_WYF);


   //创建一个失败label的精灵
   CCSprite* faileSprite = CCSprite::create("pic/failed.png");
  //设置精灵对象的位置
   faileSprite->setPosition(ccp(origin.x+visibleSize.width/2, origin.y+280));
  //将精灵添加到布景中
   this->addChild(faileSprite, DASHBOARD_LEVEL_WYF);
   //========================================================================

   	//创建新游戏的精灵
    CCMenuItemImage *homeMenuItem = CCMenuItemImage::create
	(
	  "menuHome.png",     //平时的图片
	  "menuHome2.png",   //选中时的图片
	  this,
	  menu_selector(LoseLayer::homeSence)//点击时执行的回调方法
	);
	//设置关闭菜单项的位置
    homeMenuItem->setPosition
	(
		ccp
		(
			origin.x+visibleSize.width/2,//X坐标
			 origin.y+visibleSize.height-380					//Y坐标
		 )
	 );

	 //创建菜单对象
	 CCMenu* homeMenu = CCMenu::create(homeMenuItem, NULL);
	 //设置菜单位置
	 homeMenu->setPosition(CCPointZero);
	 //将菜单添加到布景中
   		 this->addChild(homeMenu, DASHBOARD_LEVEL_WYF);

    return true;
}

void LoseLayer::homeSence(CCObject* pSender)
{
	tsm->toBeginLayer();
}

void LoseLayer::setScore(int score)
{
	this->score=score;
}
int LoseLayer::getScore()
{
	return this->score;
}
void LoseLayer::addLabel()
{
	  char a[30];
	   snprintf(a, 30, "ALL OUT!!! You scored %d runs",this->score);
	   CCLabelTTF* pLabel = CCLabelTTF::create
	   	(
	   		a,
	   		"Arial",
	   		40
	   	);
	   	//设置标签字体的颜色
	   	pLabel->setColor (ccc3(255, 255, 255));
	   	//设置文本标签的位置
	   	pLabel->setPosition
	   	(
	   		ccp
	   		(
	   			origin.x + visibleSize.width/2,									//X坐标
	   			origin.y + visibleSize.height-320 //Y坐标
	   		 )
	   	);
	   	this->addChild(pLabel, 1);
	   	//===============================================================================
}
//返回键监听
void LoseLayer::keyBackClicked()
{
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	tsm->toBeginLayer();
}
