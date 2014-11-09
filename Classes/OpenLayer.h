#ifndef  _Open_H_
#define  _Open_H_
#include "cocos2d.h"
#include "BanQiuSceneManager.h"

//自定义的布景类
class OpenLayer : public cocos2d::CCLayer
{
public:

    //Manager 对象的引用
    BanQiuSceneManager* man;
	//初始化的方法
    virtual bool init();
    //执行特效菜单的回调方法
    void playGameCallback(CCNode* node,void* param);
    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(OpenLayer);
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
