#ifndef  _WinLayer_H_
#define  _WinLayer_H_
#include "cocos2d.h"
#include "BanQiuSceneManager.h"
#include <stdio.h>

using namespace cocos2d;
//自定义的布景类
class WinLayer : public cocos2d::CCLayer
{
private:
	int score;

public:
	int guanka;//当前关卡
	//所属Scene
	cocos2d::CCScene *scene;
	cocos2d::CCSprite* label;//”ready1“
	//背景精灵
	cocos2d::CCSprite *backSprite;
	//所属管理者
	BanQiuSceneManager *tsm;
	//初始化的方法
    virtual bool init();
    void homeSence(CCObject* pSender);//回到主menu界面
    void goNextGame();//胜利精灵飞过后的回掉方法
    void setScore(int score);
    void setGuanKa(int guanKa);
    int getScore();
    int getGuanKa();
    void addParticleSystem();//通关放烟花
    void judge(int guanka);
    //返回键监听
    void keyBackClicked();

    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(WinLayer);
    CCPoint origin;
    CCSize visibleSize;
    int n;
//	#define CREATE_FUNC(__TYPE__) \
//	static __TYPE__* create() \
//	{ \
//		__TYPE__ *pRet = new __TYPE__(); \
//		if (pRet && pRet->init()) \
//		{ \
//			pRet->autorelease(); \
//			return pRet; \
//		} \
//		else \
//		{ \
//			delete pRet; \
//			pRet = NULL; \
//			return NULL; \
//		} \

};

#endif
