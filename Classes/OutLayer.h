#ifndef  _OutLayer_H_
#define  _OutLayer_H_
#include "cocos2d.h"
#include "BanQiuSceneManager.h"

//自定义的布景类
class OutLayer : public cocos2d::CCLayer
{
public:

	//背景精灵
	cocos2d::CCSprite *backSprite;
    //Manager 对象的引用
    BanQiuSceneManager* man;
	//初始化的方法
    virtual bool init();
    //的回调方法
    void noCallback(CCObject* pSender);
    //的回调方法
    void yesCallback(CCObject* pSender);
    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(OutLayer);
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
