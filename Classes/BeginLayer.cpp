#include "BeginLayer.h"
#include "AppMacros.h"
#include <string.h>
#include "SimpleAudioEngine.h"
#include "AppDelegate.h"
#include "DialogLayer.h"
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

//实现BeginLayer类中的init方法，初始化布景
bool BeginLayer::init()
{
    //调用父类的初始化
    if ( !CCLayer::init() )
    {
        return false;
    }
    isDialog = false;
    //开启按键监听
    setKeypadEnabled(true);
    //获取可见区域尺寸
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

     //创建一个精灵对象，包含背景图片
	 CCSprite* bSprite = CCSprite::create("pic/background.png");
	 //设置精灵对象的位置
	 bSprite->setPosition(ccp(origin.x, origin.y));
	 bSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
	 //将精灵添加到布景中
	 this->addChild(bSprite, 0);
   //=========================================================================================
   //创建新游戏的精灵
   CCMenuItemImage *newMenuItem = CCMenuItemImage::create
	(
	  "menuNew.png",     //平时的图片
	  "menuNew2.png",   //选中时的图片
	  this,
	  menu_selector(BeginLayer::newSence)//点击时执行的回调方法
	);

	 //=========================================================================================
	 //创建继续游戏精灵
	 CCMenuItemImage *continueItem = CCMenuItemImage::create
	 (
		  "menuContinue.png",     //平时的图片
		  "menuContinue2.png",   //选中时的图片
		  this,
		  menu_selector(BeginLayer::continueSence)//点击时执行的回调方法
	 );

	 //=========================================================================================
	 //创建成就的精灵
	 CCMenuItemImage *achievementsItem = CCMenuItemImage::create
	 (
		  "menuAchievements.png",     //平时的图片
		  "menuAchievements2.png",   //选中时的图片
		  this,
		  menu_selector(BeginLayer::achievementsSence)//点击时执行的回调方法
	 );

	 //=========================================================================================
	 //创建关于的精灵
	 CCMenuItemImage *aboutItem = CCMenuItemImage::create
	 (
		  "menuAbout.png",     //平时的图片
		  "menuAbout2.png",   //选中时的图片
		  this,
		  menu_selector(BeginLayer::aboutSence)//点击时执行的回调方法
	 );

	 //创建设置的精灵
	 CCMenuItemImage *settItem = CCMenuItemImage::create
	 (
		  "set.png",     //平时的图片
		  "set2.png",   //选中时的图片
		  this,
		  menu_selector(BeginLayer::setSence)//点击时执行的回调方法
	 );

	 //=============================================================================================
	 //创建文本精灵
	CCSprite* tSprite = CCSprite::create("pic/title.png");

	//设置精灵对象的位置
	tSprite->setPosition(ccp(origin.x, origin.y+visibleSize.height-207));
	tSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5

	//将精灵添加到布景中
	this->addChild(tSprite, 3);

//===========================================================================================
	//创建菜单对象
		pMenu = CCMenu::create(continueItem,newMenuItem,achievementsItem,aboutItem,settItem,NULL);
		//设置菜单位置
		pMenu->setPosition(CCPointZero);
		//将菜单添加到布景中
		this->addChild(pMenu, GAME_LEVEL_WYF);

		CCNode* child = NULL;
		//得到CCArray
		CCArray * pArray = pMenu->getChildren();
		//得到CCArray中元素的数量
		int count = pArray->count();
		//遍历CCArray
		for(int m=0;m<count;m++)
		{
			child = (CCNode*)(pArray->objectAtIndex(m));
			child->setPosition(ccp(400,550));
			CCActionInterval* moveTo1 = CCMoveTo::create(0.2f,ccp(400,-40));
			CCActionInterval* moveTo2 = CCMoveTo::create(0.25f*(count-m),ccp(400,80+80*(count-1-m)));
			CCActionInterval* move_ease_in2 = CCEaseElasticOut::create(moveTo2);
			CCDelayTime *delay = CCDelayTime::create(0.2f*(count-m-1));
			CCSequence* seq = CCSequence::create(delay,moveTo1,move_ease_in2, NULL);
			//如果是第一个运动的精灵，精灵运动完毕之后添加回调方法
			if(m!=0)
			{
				child->runAction(seq);
			}
			else
			{
				CCSequence* seq0 = CCSequence::create(delay,moveTo1,move_ease_in2,NULL);
				child->runAction(seq0);
			}
		}
//==================================================================================================
    return true;
}

void BeginLayer::setMoveFinish(CCNode* node,void* param)
{
	this->removeChild(node);
}
void BeginLayer::newSence(CCObject* pSender)
{
	tsm->toNewGameLayer(1);//第一关
}

void BeginLayer::continueSence(CCObject* pSender)
{

	int gK=UserRecord::getInstance()->getInt("continue",1);

	tsm->toNewGameLayer(gK);
}
void BeginLayer::achievementsSence(CCObject* pSender)
{
	tsm->toAchieveLayer();
}
void BeginLayer::rulesSence(CCObject* pSender)
{
	tsm->toAchieveLayer();
}
void BeginLayer::aboutSence(CCObject* pSender)
{
	tsm->toHelpLayer();
}

void BeginLayer::setSence(CCObject* pSender)
{
	tsm->toSetLayer();
}

//返回键监听
void BeginLayer::keyBackClicked()
{
	if(isDialog)
	{
		return;
	}
	isDialog = true;
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	tsm->toOutLayer();
}
