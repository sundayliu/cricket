#ifndef _DialogLayer_h
#define _DialogLayer_h

#include "cocos2d.h"
#include "BanQiuSceneManager.h"
#include "AppMacros.h"
#include "BanQiuLayer.h"

using namespace cocos2d;

class DialogLayer: public CCLayerColor
{
private:
	int score;
	int guanKa;
public:
    //主菜单界面
	CCMenu *m_pMenu;
    //按钮是否被点击的标志位
    bool m_bTouchedMenu;
    //所属管理者
    BanQiuSceneManager *tsm;
//    BanQiuLayer *ball;
public:
    
    virtual bool init();
    //初始化
    void initDialog();

    CREATE_FUNC(DialogLayer);
    
    void onEnter();
    void onExit();
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    void setScore(int score);
    void setGuanKa(int guanKa);
    int getScore();
    int getGuanKa();
    
    void homeSence(CCObject* pSender);
    void menuCallbackContinueGame(CCObject *pSender);
};

#endif
