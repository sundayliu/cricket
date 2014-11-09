#ifndef  _SetLayer_H_
#define  _SetLayer_H_
#include "cocos2d.h"
#include "BanQiuSceneManager.h"

//自定义的布景类
class SetLayer : public cocos2d::CCLayer
{
public:

	//背景精灵
	cocos2d::CCSprite *backSprite;
	//目标分数精灵
    cocos2d::CCSprite *targetSprite;
    //Manager 对象的引用
    BanQiuSceneManager* man;

    cocos2d::CCSprite *lbokSprite;//小喇叭ok
    cocos2d::CCSprite *lb2okSprite;//小喇叭2ok

    cocos2d::CCSprite *lbnoSprite;//小喇叭no
    cocos2d::CCSprite *lb2noSprite;//小喇叭2no

	//初始化的方法
    virtual bool init();
    void backCallback(CCObject* pSender);//返回

    //返回键监听
    void keyBackClicked();
    //设置喇叭的状态
    void setBackMusic();
    void setMusic();
    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(SetLayer);

};

#endif
