#include "AppDelegate.h"
#include "AppMacros.h"
#include "BanQiuSceneManager.h"
#include <vector>
#include <string>
#include "SimpleAudioEngine.h"
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
int guanKa;
bool BACKMUSIC;
bool MUSIC;
//构造函数
AppDelegate::AppDelegate(){}

//析构函数
AppDelegate::~AppDelegate(){}

//初始化游戏中的CCDirector以及CCScene
bool AppDelegate::applicationDidFinishLaunching()
{
	guanKa =1;
	//初始音乐位开启
    

	BACKMUSIC = UserRecord::getInstance()->getBool("backMusic",true);
	MUSIC = UserRecord::getInstance()->getBool("music",true);


    //获取CCDirector（导演）
    CCDirector* pDirector = CCDirector::sharedDirector();
    //获取CCEGLView
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
    //为导演设置绘制用OpenGLView
    pDirector->setOpenGLView(pEGLView);

    //设置目标分辨率尺寸
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionShowAll);
    //获取画面帧尺寸
	CCSize frameSize = pEGLView->getFrameSize();
//
//	LOGI("dr%f:%f",designResolutionSize.width,designResolutionSize.height);
//	LOGI("fr%f:%f",frameSize.width,frameSize.height);

    //设置资源子目录序列
	std::string rDis(picResource.directory);
	std::vector<std::string> pathV(2);
	pathV.push_back(picResource.directory);
	pathV.push_back(soundResource.directory);
	CCFileUtils::sharedFileUtils()->setSearchPaths(pathV);

	//加载背景音乐
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic
	(
		"sound/background.mp3"
	);
	if(BACKMUSIC)
	{
		//播放背景音乐
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic
		(
			"sound/background.mp3",
			true
		);
	}


	//加载发射子弹音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
	(
		"sound/fire.mp3"
	);
	//加载音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
	(
		"sound/failure.mp3"
	);
	//加载音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
	(
		"sound/mainback.mp3"
	);
//	//加载音效
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
//	(
//		"sound/menu.wav"
//	);
	//加载音效
	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
	(
		"sound/victory.mp3"
	);
//	//加载音效
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
//	(
//		"sound/tada.wav"
//	);
//	//加载音效
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
//	(
//		"sound/run.wav"
//	);
//	//加载音效
//	CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect
//	(
//		"sound/pew_pew_lei.wav"
//	);


    BanQiuSceneManager *mag = new BanQiuSceneManager();
	//设置缩放因子
	pDirector->setContentScaleFactor(1.0);
	
//    //打开FPS显示
//    pDirector->setDisplayStats(true);
//
//    //设置FPS，标准值为1/60
//    pDirector->setAnimationInterval(1.0 /60);

    //创建场景对象
    CCScene *pScene = mag->createScene();

    //告诉导演使用那个场景
    pDirector->runWithScene(pScene);

    return true;
}

//当程序离开前台，进入后台时调用
void AppDelegate::applicationDidEnterBackground()
{
	//停止动画
    CCDirector::sharedDirector()->stopAnimation();
    //如果有声音的话要调用下面一句暂停声音播放
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

//当程序进入前台时调用
void AppDelegate::applicationWillEnterForeground()
{
	//开始动画
    CCDirector::sharedDirector()->startAnimation();
    //如果有声音的话要调用下面一句开始声音播放
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
