#include "WinLayer.h"
#include "AppMacros.h"
#include <string.h>
#include "SimpleAudioEngine.h"
#include "Math.h"

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

//实现WinLayer类中的init方法，初始化布景
bool WinLayer::init()
{
    //调用父类的初始化
    if ( !CCLayer::init() )
    {
        return false;
    }
    //开启按键监听
    setKeypadEnabled(true);
    //获取可见区域尺寸
    visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    origin = CCDirector::sharedDirector()->getVisibleOrigin();
    //=========================================================================================

   //创建一个精灵对象，包含背景图片
   CCSprite* bSprite = CCSprite::create("pic/bckgr.png");
   //设置精灵对象的位置
   bSprite->setPosition(ccp(origin.x, origin.y));
   bSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
   //========================================================================
   	//标签
    label = CCSprite::create("pic/ready1.png");
    //设置标签的位置
   	label->setPosition(ccp(400,240));
   	//将精灵添加到布景中
   	this->addChild(label, GAME_LEVEL_WYF);

   //将精灵添加到布景中
   this->addChild(bSprite, BACKGROUND_LEVEL_WYF);

   LOGI("33333333%d",guanka);

   	//===============================================================================
   	//创建新游戏的精灵
    CCMenuItemImage *homeMenuItem = CCMenuItemImage::create
	 (
		  "menuHome.png",     //平时的图片
		  "menuHome2.png",   //选中时的图片
		  this,
		  menu_selector(WinLayer::homeSence)//点击时执行的回调方法
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
   	 this->addChild(homeMenu, GAME_LEVEL_WYF);
//   	 CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("Sound/sixer.mpeg");
    return true;
}

void WinLayer::judge(int guanka)
{
	if(guanka>5)//游戏通关
	   {
		   this->schedule(schedule_selector(WinLayer::addParticleSystem),2);//以秒为单位
		   label->setVisible(false);
		   //创建一个胜利的精灵
			CCSprite* sSprite = CCSprite::create("pic/sachin2.png");
			//设置精灵对象的位置
			sSprite->setPosition(ccp(0,300));
			//将精灵添加到布景中
			this->addChild(sSprite, GAME_LEVEL_WYF);

			 //创建一个胜利label的精灵
			CCSprite* labelSprite = CCSprite::create("pic/win.png");
			//设置精灵对象的位置
			labelSprite->setPosition(ccp(400,300));
			//将精灵添加到布景中
			this->addChild(labelSprite, GAME_LEVEL_WYF);

			CCActionInterval* go=CCMoveTo::create(OUTBALL_T,CCPointMake(950,300));
			CCSequence* atBack = CCSequence::create
			(
			go,
			NULL
			);
			sSprite->runAction(atBack);
	   }else
	   {
		   //====================================================================
			//创建一个胜利的精灵
			CCSprite* sSprite = CCSprite::create("pic/sachin2.png");
			//设置精灵对象的位置
			sSprite->setPosition(ccp(0,300));
			//sSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
			//将精灵添加到布景中
			this->addChild(sSprite, GAME_LEVEL_WYF);

			CCActionInterval* go=CCMoveTo::create(OUTBALL_T,CCPointMake(950,300));
			CCSequence* atBack = CCSequence::create
			(
			go,
			CCCallFuncND::create(this, callfuncND_selector(WinLayer::goNextGame), NULL),
			NULL
			);

			sSprite->runAction(atBack);
	   }
}
void WinLayer::homeSence(CCObject* pSender)
{
	tsm->toBeginLayer(this->getScore(),guanka);//去主menu界面
}

void WinLayer::goNextGame()
{
		tsm->toNewGameLayer(this->guanka);
}

void WinLayer::setScore(int score)
{
	this->score=score;
}

int WinLayer::getScore()
{
	return this->score;
}

//通关放烟花
void WinLayer::addParticleSystem()
{
	int w=rand()%700;
	int h=rand()%380;
	CCParticleSystem* cps = CCParticleExplosion::create();
	cps->setTexture( CCTextureCache::sharedTextureCache()->addImage("pic/fire.png") );
	cps->setAutoRemoveOnFinish(true);
	cps->setPosition(ccp( w, h));
	this->addChild(cps);
}

//返回键监听
void WinLayer::keyBackClicked()
{
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	tsm->toBeginLayer();
}

