#include "AchieveLayer.h"
#include "AppMacros.h"
#include "DialogLayer.h"
#include <string.h>
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
bool AchieveLayer::init()
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
    CCSprite *playSprite = CCSprite::create("pic/menuHight.png");
	//设置精灵对象的位置
    playSprite->setPosition(ccp(400, 404));
	//将背景精灵添加到布景中
	this->addChild(playSprite, GAME_LEVEL_WYF);
//label  328
	//创建一个文本标签
	int MaxScore=UserRecord::getInstance()->getInt("MaxScore",0);
	char a[12];

	snprintf(a, 12, "%d",MaxScore);

	CCLabelTTF* pLabel = CCLabelTTF::create(a, "Arial", TITLE_FONT_SIZE);
	//设置标签字体的颜色
	pLabel->setColor (ccc3(255, 255, 255));
	//设置文本标签的位置
	pLabel->setPosition
	(
		ccp
		(
			400,					//X坐标
			328	                    //Y坐标
		 )
	);
	//将文本标签添加到布景中
	this->addChild(pLabel, DASHBOARD_LEVEL_WYF);

	 //创建一个精灵对象，充当物体
	CCSprite *hight = CCSprite::create("pic/menuBest.png");
	//设置精灵对象的位置
	hight->setPosition(ccp(400, 252));
	//将背景精灵添加到布景中
	this->addChild(hight, GAME_LEVEL_WYF);

	//创建一个文本标签
    

	int guanKa=UserRecord::getInstance()->getInt("guanKa",1);
	char b[12];

	snprintf(b, 12, "%d",guanKa);

	CCLabelTTF* pL = CCLabelTTF::create(b, "Arial", TITLE_FONT_SIZE);
	//设置标签字体的颜色
	pL->setColor (ccc3(255, 255, 255));
	//设置文本标签的位置
	pL->setPosition
	(
		ccp
		(
			400,					//X坐标
			176	                    //Y坐标
		 )
	);
	//将文本标签添加到布景中
	this->addChild(pL, DASHBOARD_LEVEL_WYF);

	//创建home菜单项
	CCMenuItemImage *pRightItem = CCMenuItemImage::create
	(
		 "pic/menuHome.png",     //平时的图片
		 "pic/menuHome2.png",   //选中时的图片
		 this,
		 menu_selector(AchieveLayer::menuDoEffectCallback)//点击时执行的回调方法
	);
	//设置菜单项的位置
	pRightItem->setPosition
	(
		ccp
		(
			origin.x+visibleSize.width/2,//X坐标
			origin.y+visibleSize.height-380					//Y坐标
		 )
	 );

	//创建菜单对象
	CCMenu* pMenuRight = CCMenu::create(pRightItem, NULL);
	//设置菜单位置
	pMenuRight->setPosition(CCPointZero);
	//将菜单添加到布景中
	this->addChild(pMenuRight, DASHBOARD_LEVEL_WYF);
    return true;
}

//实现FromLayer类中的下一个菜单的回调方法
void AchieveLayer::menuDoEffectCallback(CCObject* pSender)
{
	  man->toBeginLayer();
}

//返回键监听
void AchieveLayer::keyBackClicked()
{
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	man->toBeginLayer();
}

