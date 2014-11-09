#include "DialogLayer.h"
#include "AppMacros.h"
#include "BanQiuSceneManager.h"
#include "SimpleAudioEngine.h"
#include "BanQiuLayer.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
using namespace cocos2d;

bool DialogLayer::init()
{
    bool bRet = false;
    
    do {
        CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(0, 0, 0, 125),800,480));
        this->initDialog();
        bRet = true;
    } while (0);
    
    return bRet;
}

void DialogLayer::initDialog()
{
	//创建新游戏的精灵
    CCMenuItemImage *resume = CCMenuItemImage::create
	(
		 "pic/resume.png", //平时的图片
		"pic/resume2.png",  //选中时的图片
	  this,
	  menu_selector(DialogLayer::menuCallbackContinueGame)//点击时执行的回调方法
	);
	//设置关闭菜单项的位置
    resume->setPosition(ccp(400,170));
	 //创建菜单对象
	 CCMenu* resumeMenu = CCMenu::create(resume, NULL);
	 //设置菜单位置
	 resumeMenu->setPosition(CCPointZero);
	 //将菜单添加到布景中
	 this->addChild(resumeMenu, DASHBOARD_LEVEL_WYF);

	 //创建新游戏的精灵
	CCMenuItemImage *saveExit = CCMenuItemImage::create
	(
	 "pic/menu_1.png", //平时的图片
	"pic/menu_2.png",  //选中时的图片
	this,
	menu_selector(DialogLayer::homeSence)//点击时执行的回调方法
	);
	//设置关闭菜单项的位置
	saveExit->setPosition(ccp(400,310));
	//创建菜单对象
	m_pMenu = CCMenu::create(saveExit, NULL);
	//设置菜单位置
	m_pMenu->setPosition(CCPointZero);
	//将菜单添加到布景中
	this->addChild(m_pMenu, DASHBOARD_LEVEL_WYF);
}

void DialogLayer::onEnter()
{
    CCLayerColor::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
}

void DialogLayer::onExit()
{
    CCLayerColor::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool DialogLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    m_bTouchedMenu = m_pMenu->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DialogLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchMoved(pTouch, pEvent);
    }
}

void DialogLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

void DialogLayer::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_bTouchedMenu) {
        m_pMenu->ccTouchEnded(pTouch, pEvent);
        m_bTouchedMenu = false;
    }
}

//去主场景的回调方法
void DialogLayer::homeSence(CCObject* pSender)
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->resume();//继续场景
	if(BACKMUSIC)
	{
		//继续声音
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	tsm->toBeginLayer(this->getScore(),this->getGuanKa());

}

//继续游戏的回调方法
void DialogLayer::menuCallbackContinueGame(cocos2d::CCObject *pSender)
{
    this->removeFromParentAndCleanup(false);
    //获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->resume();//继续场景
	if(BACKMUSIC)
	{
		//继续声音
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}

}
void DialogLayer::setScore(int score)
{
	this->score=score;
}
void DialogLayer::setGuanKa(int guanKa)
{
	this->guanKa=guanKa;
}
int DialogLayer::getScore()
{
	return this->score;
}
int DialogLayer::getGuanKa()
{
	return this->guanKa;
}
