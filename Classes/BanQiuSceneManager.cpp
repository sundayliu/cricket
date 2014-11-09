#include "BanQiuSceneManager.h"
#include "AppMacros.h"
#include "AppDelegate.h"
#include "NewGameLayer.h"
#include "BanQiuLayer.h"
#include "BeginLayer.h"
#include "LoseLayer.h"
#include "WinLayer.h"
#include "HelpLayer.h"
#include "AchieveLayer.h"
#include "TransUtil.h"
#include "DialogLayer.h"
#include "UserRecord.h"
#include "OutLayer.h"
#include "SetLayer.h"
#include "OpenLayer.h"

//#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))

//USING_NS_CC;
using namespace cocos2d;

//实现HelloWorldSceneManager类中的createScene方法
CCScene* BanQiuSceneManager::createScene()
{
	//创建CCScene（场景）对象
    CCScene *scene = CCScene::create();
    //创建一个布景对象（类的对象）
    OpenLayer *openLayer = OpenLayer::create();
    openLayer->man=this;
    //向场景中添加布景
    scene->addChild(openLayer);
    //返回场景对象
    return scene;
}

void BanQiuSceneManager::setAchieve(int score,int guan)
{
	int maxScore=UserRecord::getInstance()->getInt("MaxScore",-1);
	int guanKa=UserRecord::getInstance()->getInt("guanKa",-1);

	if(guanKa==-1||guan>=guanKa)
	{
		if(guan>5)
		{
			UserRecord::getInstance()->saveInt("guanKa",5);
		}
		else
		{
			UserRecord::getInstance()->saveInt("guanKa",guan);
		}
		if(maxScore==-1||score>maxScore||guan>guanKa)
		{
			UserRecord::getInstance()->saveInt("MaxScore",score);
		}
	}
}

int BanQiuSceneManager::getMaxScore()
{
	int maxScore=UserRecord::getInstance()->getInt("MaxScore",-1);
	return maxScore;
}
int BanQiuSceneManager::getGuanKa()
{
	int guanKa=UserRecord::getInstance()->getInt("guanKa",-1);
	return guanKa;
}
//切换到主menu开始的场景
void BanQiuSceneManager::toBeginLayer(int score,int guanKa)
{
//	获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	BeginLayer *layer = BeginLayer::create();
	layer->tsm=this;
//	layer->isDialog = false;
	toGameLayerSence->addChild(layer);

	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
//	执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
	this->setAchieve(score,guanKa);
}
void BanQiuSceneManager::toBeginLayer()
{
//	获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	BeginLayer *layer = BeginLayer::create();
	layer->tsm=this;
//	layer->isDialog = false;
	toGameLayerSence->addChild(layer);

	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
//	执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}
//切换到新游戏开始的场景
void BanQiuSceneManager::toNewGameLayer(int guanka)
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	NewGameLayer *layer = NewGameLayer::create();
	layer->man = this;
	layer->guanka=guanka;
	layer->initString();
	toGameLayerSence->addChild(layer);

	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}
//切换到about的场景
void BanQiuSceneManager::toHelpLayer()
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	HelpLayer *layer = HelpLayer::create();
	layer->tsm = this;
	toGameLayerSence->addChild(layer);

	CCTransitionScene* ccts = TransUtil::createTransition(9,0.8,toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}
//切换到Rulls的场景
void BanQiuSceneManager::toAchieveLayer()
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	AchieveLayer *layer = AchieveLayer::create();
	layer->man=this;
	toGameLayerSence->addChild(layer);

	CCTransitionScene* ccts = TransUtil::createTransition(9,0.8,toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}

//切换到游戏开始的场景
void BanQiuSceneManager::toGameLayer(int guanka)
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	BanQiuLayer *layer = BanQiuLayer::create();
	layer->mag = this;
	layer->guanka=guanka;//把关卡传过去
	layer->initString();
	toGameLayerSence->addChild(layer);

	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}

//切换到游戏结束的场景
void BanQiuSceneManager::toLoseLayer(int score,int guanKa)
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	LoseLayer *layer = LoseLayer::create();
	layer->tsm=this;
	toGameLayerSence->addChild(layer);

	//创建切换特效 CCTransitionFlipY::create(t, s, kCCTransitionOrientationDownOver);
	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
	this->setAchieve(score,guanKa);
}

//切换到游戏胜利的场景
void BanQiuSceneManager::toWinLayer(int score,int guanka)
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	WinLayer *layer = WinLayer::create();
	layer->tsm =this;
	layer->setScore(score);
	layer->guanka=guanka;//把关卡传过去
	layer->judge(guanka);
	toGameLayerSence->addChild(layer);
	//创建切换特效 CCTransitionFlipY::create(t, s, kCCTransitionOrientationDownOver);
	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}

//切换到退出游戏的场景
void BanQiuSceneManager::toOutLayer()
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	OutLayer *layer = OutLayer::create();
	layer->man =this;
	toGameLayerSence->addChild(layer);

	//创建切换特效 CCTransitionFlipY::create(t, s, kCCTransitionOrientationDownOver);
	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}

//切换到设置游戏的场景
void BanQiuSceneManager::toSetLayer()
{
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector -> setDepthTest(true);
	CCScene* toGameLayerSence = CCScene::create();
	SetLayer *layer = SetLayer::create();
	layer->man =this;
	toGameLayerSence->addChild(layer);

	//创建切换特效 CCTransitionFlipY::create(t, s, kCCTransitionOrientationDownOver);
	CCTransitionScene* ccts= CCTransitionFadeTR::create(1.0f, toGameLayerSence);
	//执行切换
	CCDirector::sharedDirector()->replaceScene(ccts);
}

