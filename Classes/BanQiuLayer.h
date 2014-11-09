#ifndef  _BallSimpleLayer_H_
#define  _BallSimpleLayer_H_

#include "cocos2d.h"
#include "BallTest.h"
#include "FielderSprite.h"
#include "BanQiuSceneManager.h"
#include "Prop.h"
using namespace cocos2d;
//自定义的布景类
class BanQiuLayer : public cocos2d::CCLayer
{
public:
	//cocos2d::CCSprite *ballSprite;//小球
	cocos2d::CCLabelTTF *pLabel;//当前分数的label
	cocos2d::CCLabelTTF *overLabel;//被挡次数的label
	cocos2d::CCPoint location;//触控点
	//BallTest *temp;//小球
	//Prop* propSprite1;//道具
	BanQiuSceneManager *mag;//Manager对象的引用
	cocos2d::CCArray *arr;//存放小球的数组
	cocos2d::CCArray *pArr;//存放道具的数组
	cocos2d::CCArray *array;//存放守门员的数组
	cocos2d::CCArray *stArr;//存放停止守门员的数组
//	cocos2d::CCSprite *pause;//暂停精灵
	CCSequence* seq;//出球动作序列
	CCSprite **fire;
	CCActionInterval* at;//出球动作
	//一系列的动作
//	CCActionInterval* at1;
//	CCActionInterval* at2;
//	CCActionInterval* at3;
//	CCActionInterval* at4;
//	CCActionInterval* at5;
//	CCActionInterval* at6;

    int guanka;
    int tempScore; //总分数
    int tempCount; //被挡球的次数
    bool outBallFlag;  //发球标志位
    bool outPropFlag;  //发道具标志位
    bool blurFlag;//第三种道具标志位
    bool outFielderFlag;//出守门员标志位
    bool isDialog;//dialog界面的标志位
    int ballCount; //小球数量
    int targetCount;//允许被挡球的次数
    int targetScore;//目标分数
    long currTime; //当前时间
//    float fielder_time;//两守门员间隔出来时间

	//初始化的方法
    virtual bool init();  
    virtual void keyBackClicked();//返回键监听函数
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    void stopFielder();//停止守门员运动
    //菜单关闭回调方法
//    void menuCloseCallback(CCObject* pSender);
    //初始化字符串
    void initString();
    //更新碰撞检测
    void upDate(float dt);
    void particlesCallback(CCObject* pSender);
    void outBall();//出球方法
    void outFielder();//出守门员
    void outProp();//出道具
    void removeBall(CCNode* node,void* param);//移除小球方法
    void removeProp(CCNode* node,void* param);//移除道具
    void removeScoreOne(CCNode* node,void* param);//移除1分数图片的回掉方法
    void removeScoreTwo(CCNode* node,void* param);//移除2分数图片的回掉方法
    void removeScoreSix(CCNode* node,void* param);//移除6分数图片的回掉方法
    void plussScore(float x,float y,int score);//进了网调用的方法
    long getCurrentTime();//时间方法
    void setOutFielderFlag();//设置出守门员标志
    void setOutPropFlag();//设置出道具标志
    void pauseCallBack();//暂停按钮的回掉方法
    void outFire();//第三种道具出火
    void removeBlur(CCNode* node,void* param);
    //CCPlatformMacros.h文件中定义的一个宏，创建指定类型的对象
    //并做好相应的初始化与释放工作
    CREATE_FUNC(BanQiuLayer);
};

#endif
