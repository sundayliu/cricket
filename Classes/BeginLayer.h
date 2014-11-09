#ifndef  _BeginLayer_H_
#define  _BeginLayer_H_
#include "cocos2d.h"
#include "BanQiuSceneManager.h"
#include "stdio.h"
#include "NewGameLayer.h"

//using namespace cocos2d;
//自定义的布景类
class BeginLayer : public cocos2d::CCLayer
{
public:
	//所属Scene
	cocos2d::CCScene *scene;
	//背景精灵
	cocos2d::CCSprite *backSprite;
	cocos2d::CCMenu* pMenu;//
	//所属管理者
	BanQiuSceneManager *tsm;
	NewGameLayer *ng;
	int guanka;
	bool isDialog;
	//初始化的方法
    virtual bool init();
    virtual void keyBackClicked();//返回键监听函数
    void newSence(CCObject* pSender);
    void continueSence(CCObject* pSender);
    void achievementsSence(CCObject* pSender);
    void rulesSence(CCObject* pSender);
    void aboutSence(CCObject* pSender);
    void setSence(CCObject* pSender);
    void setMoveFinish(CCNode* node,void* param);

    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(BeginLayer);
//    CCPoint origin;
//    CCSize visibleSize;
};

#endif
