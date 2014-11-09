#include "NewGameLayer.h"
#include "AppMacros.h"
#include <string>
//#include <android/log.h>
#include <string.h>
#include "cocos2d.h"
#include "BanQiuSceneManager.h"
#include "AppDelegate.h"
#include "UserRecord.h"

//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
//#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

//USING_NS_CC;
using namespace cocos2d;

//实现类中的init方法，初始化布景
bool NewGameLayer::init()
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
    //创建一个精灵对象，充当背景
    backSprite = CCSprite::create("pic/bckgr_2.png");
    //设置精灵对象的位置
    backSprite->setPosition(ccp(origin.x, origin.y));
    backSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
    //将背景精灵添加到布景中
    this->addChild(backSprite, BACKGROUND_LEVEL_WYF);

    //创建一个精灵对象，充当物体
    CCSprite *playSprite = CCSprite::create("pic/letsplay.png");
	//设置精灵对象的位置
    playSprite->setPosition(ccp(400, 300));
	//将背景精灵添加到布景中
	this->addChild(playSprite, GAME_LEVEL_WYF);
	CCActionInterval* at=CCMoveTo::create(1,CCPointMake(150,150));
	CCActionInterval* end=CCMoveTo::create(1,CCPointMake(638,150));
	CCSequence *ccseq = CCSequence::create
	(
		at,
		end,
		CCCallFuncND::create(this, callfuncND_selector(NewGameLayer::playGameCallback), NULL),
		NULL
	);
	playSprite->runAction(ccseq);

    return true;
}
//初始化字符串
void NewGameLayer::initString()
{
	//当前关卡字符串
	std::string strLevel[]={"pic/l1.png","pic/l2.png","pic/l3.png","pic/l4.png","pic/l5.png"};
	std::string strTarget[]={"pic/s1.png","pic/s2.png","pic/s3.png","pic/s4.png","pic/s5.png"};
	std::string strChance[]={"pic/c1.png","pic/c2.png","pic/c3.png","pic/c4.png","pic/c5.png"};

	//创建一个精灵对象，充当关卡
	CCSprite *levelSprite = CCSprite::create(strLevel[guanka-1].c_str());
	levelSprite->setPosition(ccp(400,400));
	//添加到布景中
	this->addChild(levelSprite, DASHBOARD_LEVEL_WYF);

	//创建一个精灵对象，充当目标分数
	CCSprite *targetSprite = CCSprite::create(strTarget[guanka-1].c_str());
	targetSprite->setPosition(ccp(400,320));
	//添加到布景中
	this->addChild(targetSprite, DASHBOARD_LEVEL_WYF);

	//创建一个精灵对象，充当机会
	CCSprite *chanceSprite = CCSprite::create(strChance[guanka-1].c_str());
	chanceSprite->setPosition(ccp(400,240));
	//添加到布景中
	this->addChild(chanceSprite, DASHBOARD_LEVEL_WYF);
}

//实现FromLayer类中的下一个菜单的回调方法
void NewGameLayer::playGameCallback(CCObject* pSender,void* m)
{
	  man->toGameLayer(this->guanka);
	  guanKa = this->guanka;

	  UserRecord::getInstance()->saveInt("continue",guanKa);

}

//实现FromLayer类中的menuCloseCallback方法，处理关闭菜单项点击事件
void NewGameLayer::menuCloseCallback(CCObject* pSender)
{
	//退出
    CCDirector::sharedDirector()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
      exit(0);
    #endif
}
