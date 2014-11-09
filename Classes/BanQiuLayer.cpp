#include "BanQiuLayer.h"
#include "AppMacros.h"
#include <string.h>
#include "SimpleAudioEngine.h"
#include <math.h>
#include <time.h>
#include "BallTest.h"
#include "FielderSprite.h"
#include "Prop.h"
#include "DialogLayer.h"
//#include "ApplyParticlesUtil.h"


#if CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID
#include <android/log.h>
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))
#else
#define LOGI(...)
#define LOGW(...)
#endif

//USING_NS_CC;
using namespace cocos2d;

//实现HelloWorldLayer类中的init方法，初始化布景
bool BanQiuLayer::init()
{
    //调用父类的初始化
    if ( !CCLayer::init() )
    {
        return false;
    }
    //初始化数据
    tempScore = 0;
    tempCount = 0;
    ballCount = 0;
    targetCount = 5;//允许被挡球的次数
    targetScore = 50;//目标分数
    fire=new CCSprite*[48];
    currTime = getCurrentTime();
    outBallFlag = false;
    blurFlag = false;
    outFielderFlag = true;
    outPropFlag = false;
    isDialog = false;
    setTouchEnabled(true);
    //开启按键监听
    setKeypadEnabled(true);
    //数组的初始化
    arr = CCArray::create();
    arr->retain();
    pArr = CCArray::create();
    pArr->retain();
    array = CCArray::create();
    array->retain();
    stArr = CCArray::create();
	stArr->retain();

    //获取可见区域尺寸
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    //获取可见区域原点坐标
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    //创建一个tempScore文本标签
    pLabel = CCLabelTTF::create("Score", "Arial", TITLE_FONT_SIZE);
    //设置标签字体的颜色
    pLabel->setColor (ccc3(0, 0, 0));
    //设置文本标签的位置
    pLabel->setPosition
    (
    	ccp
    	(
			SCORE_X,					//X坐标
			SCORE_Y	                    //Y坐标
         )
    );
    //将文本标签添加到布景中
    this->addChild(pLabel, TOP_LEVEL);

	//创建一个被挡次数文本标签
	overLabel = CCLabelTTF::create("0", "Arial", TITLE_FONT_SIZE);
	//设置标签字体的颜色
	overLabel->setColor (ccc3(250, 0, 0));
	//设置文本标签的位置
	overLabel->setPosition
	(
		ccp
		(
			OVERLABEL_X,				//X坐标
			SCORE_Y	                    //Y坐标
		 )
	);
	//将文本标签添加到布景中
	this->addChild(overLabel, TOP_LEVEL);

    //创建一个精灵对象，包含background.png图片，充当背景
    CCSprite* pSprite = CCSprite::create("pic/background.png");
    //设置精灵对象的位置
    pSprite->setPosition(ccp(origin.x, origin.y));
    pSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
    //将背景精灵添加到布景中
    this->addChild(pSprite, BACKGROUND_LEVEL_WYF);

    //暂停 精灵
	CCMenuItemImage *pauseMenuItem = CCMenuItemImage::create
	(
	  "pic/pause.png",     //平时的图片
	  "pic/pause1.png",   //选中时的图片
	  this,
	  menu_selector(BanQiuLayer::pauseCallBack)//点击时执行的回调方法
	);
	//设置关闭菜单项的位置
	pauseMenuItem->setPosition(ccp(150,450));

	//创建菜单对象
	CCMenu* pauseMenu = CCMenu::create(pauseMenuItem, NULL);
	//设置菜单位置
	pauseMenu->setPosition(CCPointZero);
	//将菜单添加到布景中
	this->addChild(pauseMenu,DASHBOARD_LEVEL_WYF);

    //创建一个精灵对象，包含six.png图片，充当6号网
	CCSprite* sixSprite = CCSprite::create("pic/six.png");
	//设置精灵对象的位置
	sixSprite->setPosition(ccp(GRID_SIX_X, GRID_SIX_Y));
	sixSprite->setAnchorPoint(ccp(1, 0.5));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(sixSprite, DASHBOARD_LEVEL_WYF);

	//创建一个精灵对象，包含two.png图片，充当上面的2号网
	CCSprite* twoTSprite = CCSprite::create("pic/two.png");
	//设置精灵对象的位置
	twoTSprite->setPosition(ccp(GRID_TWO_TOP_X, GRID_TWO_TOP_Y));
	twoTSprite->setAnchorPoint(ccp(1, 1));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(twoTSprite, DASHBOARD_LEVEL_WYF);

	//创建一个精灵对象，包含two.png图片，充当下面的2号网
	CCSprite* twoBSprite = CCSprite::create("pic/two.png");
	//设置精灵对象的位置
	twoBSprite->setPosition(ccp(GRID_TWO_BOTTOM_X,GRID_TWO_BOTTOM_Y));
	twoBSprite->setAnchorPoint(ccp(1, 0));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(twoBSprite, DASHBOARD_LEVEL_WYF);

	//创建一个精灵对象，包含one.png图片，充当上面的1号网
	CCSprite* oneTSprite = CCSprite::create("pic/one.png");
	//设置精灵对象的位置
	oneTSprite->setPosition(ccp(GRID_ONE_TOP_X, GRID_ONE_TOP_Y));
	oneTSprite->setAnchorPoint(ccp(1, 1));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(oneTSprite, DASHBOARD_LEVEL_WYF);

	//创建一个精灵对象，包含one.png图片，充当下面的1号网
	CCSprite* oneBSprite = CCSprite::create("pic/one.png");
	//设置精灵对象的位置
	oneBSprite->setPosition(ccp(GRID_ONE_BOTTOM_X,GRID_ONE_BOTTOM_Y));
	oneBSprite->setAnchorPoint(ccp(1, 0));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(oneBSprite, DASHBOARD_LEVEL_WYF);

    //创建一个精灵对象，包含sachin.png图片，充当球员
	CCSprite* sachinSprite = CCSprite::create("pic/sachin.png");
	//设置精灵对象的位置
	sachinSprite->setPosition(ccp(PLAYER_X,PLAYER_Y));
	sachinSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(sachinSprite, GAME_LEVEL_WYF);

	//创建一个精灵对象，包含ticker.png图片，充当仪表盘
	CCSprite* tickerSprite = CCSprite::create("pic/ticker.png");
	//设置精灵对象的位置
	tickerSprite->setPosition(ccp(BOARD_X,BOARD_Y));
	tickerSprite->setAnchorPoint(ccp(0, 0));//默认锚点为0.5，0.5
	//将背景精灵添加到布景中
	this->addChild(tickerSprite, DASHBOARD_LEVEL_WYF);
    this->schedule(schedule_selector(BanQiuLayer::upDate),0.01f);//以秒为单位

    this->schedule(schedule_selector(BanQiuLayer::setOutPropFlag),5);//以秒为单位
    return true;
}
//初始化字符串
void BanQiuLayer::initString()
{
	//创建一个目标分数文本标签
	CCLabelTTF *over ;
	char o[5];
	snprintf(o, 5, "%d",6-guanka);
	std::string overStr = "/ ";
	overStr=overStr+o;
	over = CCLabelTTF::create(overStr.c_str(), "Arial", TITLE_FONT_SIZE);
	//设置标签字体的颜色
	over->setColor (ccc3(250, 0, 0));
	//设置文本标签的位置
	over->setPosition
	(
		ccp
		(
			OVERLABEL_X+40,				//X坐标
			SCORE_Y	                    //Y坐标
		 )
	);
	//将文本标签添加到布景中
	this->addChild(over, TOP_LEVEL);

	 //创建一个目标分数文本标签
	CCLabelTTF *targetLabel ;
	char s[5];
	snprintf(s, 5, "%d",guanka*50);
	targetLabel = CCLabelTTF::create(s, "Arial", TITLE_FONT_SIZE);
	//设置标签字体的颜色
	targetLabel->setColor (ccc3(250, 0, 0));
	//设置文本标签的位置
	targetLabel->setPosition
	(
		ccp
		(
			TARGETLABEL_X,				//X坐标
			SCORE_Y	                    //Y坐标
		 )
	);
	//将文本标签添加到布景中
	this->addChild(targetLabel, TOP_LEVEL);

	 //创建一个关卡文本标签
	CCLabelTTF *gk ;
	char g[5];
	snprintf(g, 5, "%d",guanka);
	gk = CCLabelTTF::create(g, "Arial", TITLE_FONT_SIZE);
	//设置标签字体的颜色
	gk->setColor (ccc3(250, 0, 0));
	//设置文本标签的位置
	gk->setPosition(ccp(720,SCORE_Y));
	this->addChild(gk, TOP_LEVEL);

	this->schedule(schedule_selector(BanQiuLayer::setOutFielderFlag),(6-guanka)/2.0f);//以秒为单位
}
//碰撞检测
void BanQiuLayer::upDate(float dt)
{
	if(outBallFlag)
	{
		outBallFlag = false;//出球标志位置为false
		outBall();//调用出球方法
	}

	if(outFielderFlag)
	{
		outFielderFlag = false;//标志位置为false
		outFielder();//调用出守门员方法
	}

	if(outPropFlag)
	{
		outPropFlag = false;
		outProp();//出道具
	}

	for(int i=0;i<arr->count();i++)//小球
	{
		BallTest* temp =(BallTest*)arr->objectAtIndex(i);
		CCPoint ballPoint = temp->getPosition();

		for(int j=0;j<array->count();j++)//守门员
		{
			FielderSprite* tempSprite = (FielderSprite*)array->objectAtIndex(j);
			CCPoint fielderPoint = tempSprite->getPosition();

			if(blurFlag)//如果吃到第三种道具 当道的移除守门员
			{
				CCPoint firePoint = fire[1]->getPosition();
				if(fielderPoint.x-firePoint.x<10)
				{
					array->removeObject(tempSprite);
					this->removeChild(tempSprite);
				}
			}

			for(int k=0;k<pArr->count();k++)//道具
			{
				Prop* pTemp =(Prop*)pArr->objectAtIndex(k);
				CCPoint propPoint = pTemp->getPosition();
				//吃到道具
				if(abs(propPoint.x-ballPoint.x)<17&&abs(propPoint.y-ballPoint.y)<27)
				{
					int m = pTemp->mark;//判断吃到什么道具

					switch(m)
					{
					case 0:
						if(temp->mark!=1)//是带火的球加火
						{
							temp->setMark(1);//red 带火的球
						}
						break;
					case 1:stopFielder();//停止守门员运动
					break;
					case 2:outFire();
					break;
					}
					//吃到道具 道具消失
					pTemp->stopAllActions();
					pArr->removeObject(pTemp);
					this->removeChild(pTemp);
				}
			}

			if(abs(fielderPoint.x-ballPoint.x)<17&&abs(fielderPoint.y-ballPoint.y)<27)
			{//若碰到守门员则反弹
				float vx = temp->x;
				float vy = temp->y;
				int mark = temp->getMark();
				if(temp->mark==0)//判断为普通的球
				{
					//第一次碰到守门员把小球碰撞标志位置成false
					if(temp->getHitFlag())
					{
						temp->setHitFlag(false);
						tempCount++;//球被挡次数加1
						char a[4];
						snprintf(a, 4, "%d",tempCount);
						overLabel->setString(a);
					}
					if(tempCount==(this->targetCount)+1-guanka)//失败
					{
						mag->toLoseLayer(tempScore,guanKa);

						if(MUSIC)
						{
							//播放失败音乐
							CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect
							(
									"sound/failure.mp3"
							);
						}
					}
					//temp->stopAllActions();
					//temp->cleanup();
					temp->stopAction(seq);//停止以前的动作
					//创建反弹的动作
					CCActionInterval* back=CCMoveBy::create(OUTBALL_T,CCPointMake(-BALL_V*vx,BALL_V*vy));
					CCSequence* atBack = CCSequence::create
					(
						back,
						CCCallFuncND::create(this, callfuncND_selector(BanQiuLayer::removeBall), NULL),
						NULL
					);

					temp->runAction(back);
					if(MUSIC)
					{
						//播放被挡音乐
						CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect
						(
								"sound/mainback.mp3"
						);
					}

				}

			}
		}

		if(ballPoint.x<GRID_ONE_BOTTOM_X&&ballPoint.x>GRID_ONE_BOTTOM_X-GRID_WIDTH+GRID_OFFSET
		&&ballPoint.y<GRID_ONE_BOTTOM_Y+GRID_HEIGHT&&ballPoint.y>GRID_ONE_BOTTOM_Y
		)//若进了下面1号网
		{
			//移除小球
			this->removeChild(temp);
			arr->removeObject(temp);

			plussScore(GRID_ONE_BOTTOM_X-GRID_WIDTH/2,GRID_ONE_BOTTOM_Y+GRID_HEIGHT,GRID_ONE_BOTTOM_INDEX);

		}else if(ballPoint.x<GRID_ONE_TOP_X&&ballPoint.x>GRID_ONE_TOP_X-GRID_WIDTH
				&&ballPoint.y<GRID_ONE_TOP_Y&&ballPoint.y>GRID_ONE_TOP_Y-GRID_HEIGHT
		)//若进了上面1号网
		{
			//移除小球
			this->removeChild(temp);
			arr->removeObject(temp);
			plussScore(GRID_ONE_TOP_X-GRID_WIDTH/2,GRID_ONE_TOP_Y-GRID_HEIGHT,GRID_ONE_TOP_INDEX);
		}
		else if(ballPoint.x<GRID_TWO_BOTTOM_X&&ballPoint.x>GRID_TWO_BOTTOM_X-GRID_WIDTH

				&&ballPoint.y<GRID_TWO_BOTTOM_Y+GRID_HEIGHT&&ballPoint.y>GRID_TWO_BOTTOM_Y
		)//若进了下面2号网
		{
			//移除小球
			this->removeChild(temp);
			arr->removeObject(temp);

			plussScore(GRID_TWO_BOTTOM_X-GRID_WIDTH/2,GRID_TWO_BOTTOM_Y+GRID_HEIGHT,GRID_TWO_BOTTOM_INDEX);
		}
		else if(ballPoint.x<GRID_TWO_TOP_X&&ballPoint.x>GRID_TWO_TOP_X-GRID_WIDTH

				&&ballPoint.y<GRID_TWO_TOP_Y&&ballPoint.y>GRID_TWO_TOP_Y-GRID_HEIGHT
		)//若进了上面2号网
		{
			//移除小球
			this->removeChild(temp);
			arr->removeObject(temp);

			plussScore(GRID_TWO_TOP_X-GRID_WIDTH/2,GRID_TWO_TOP_Y-GRID_HEIGHT,GRID_TWO_TOP_INDEX);
		}
		else if(ballPoint.x>GRID_SIX_X-GRID_HEIGHT

				&&ballPoint.y<GRID_SIX_Y+GRID_WIDTH/2&&ballPoint.y>GRID_SIX_Y-GRID_WIDTH/2+GRID_OFFSET

		)//若进了6号网
		{
			//移除小球
			this->removeChild(temp);
			arr->removeObject(temp);

			plussScore(GRID_SIX_X-GRID_HEIGHT,GRID_SIX_Y, GRID_SIX_INDEX);
		}

	}

	for(int i=0;i<stArr->count();i++)//守门员停止2秒后继续前进
	{
		FielderSprite* fs=(FielderSprite*)stArr->objectAtIndex(i);

		if(getCurrentTime()-fs->stopTime>2000)
		{
			CCActionInterval* ca1=CCMoveBy::create(3.5,CCPointMake(-800,-170));
			CCActionInterval* ca2=CCMoveBy::create(4,CCPointMake(-800,-100));
			CCActionInterval* ca3=CCMoveBy::create(2.5,CCPointMake(-800,-30));
			CCActionInterval* ca4=CCMoveBy::create(4.5,CCPointMake(-800,40));
			CCActionInterval* ca5=CCMoveBy::create(5,CCPointMake(-800,110));
			CCActionInterval* ca6=CCMoveBy::create(3,CCPointMake(-800,180));

			switch(fs->mark)
			{
			case 1:fs->runAction(ca1);break;
			case 2:fs->runAction(ca2);break;
			case 3:fs->runAction(ca3);break;
			case 4:fs->runAction(ca4);break;
			case 5:fs->runAction(ca5);break;
			case 6:fs->runAction(ca6);break;
			}


			stArr->removeObject(fs);

		}
	}

	//移除出界小球
	for(int i=0;i<arr->count();i++)
	{
		BallTest* temp =(BallTest*)arr->objectAtIndex(i);
		CCPoint ballPoint = temp->getPosition();
		if(ballPoint.x>800||ballPoint.x<0||ballPoint.y>480||ballPoint.y<0)
		{
			this->removeChild(temp);
			arr->removeObject(temp);
		}
	}
	//移除出界守门员
	for(int j=0;j<array->count();j++)
	{
		FielderSprite* tempSprite = (FielderSprite*)array->objectAtIndex(j);
		CCPoint fielderPoint = tempSprite->getPosition();
		if(fielderPoint.x==0)
		{
			this->removeChild(tempSprite);
			array->removeObject(tempSprite);
		}
	}
}

//调用触摸方法方法  弹出球
void BanQiuLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	long ct = getCurrentTime();

	if((ct-currTime)>SPACE_TIME)
	{
		outBallFlag = true;//发球标志位
		currTime = ct;//把这次发球时间给currTime
	}

	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);
	location = touch->getLocation();
}

void BanQiuLayer::pauseCallBack()//暂停按钮的回掉方法
{
	isDialog = true;
//	mag->toBeginLayer();
	//获取CCDirector（导演）
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->pause();//暂停场景

	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	DialogLayer* dialogLayer = DialogLayer::create();
	dialogLayer->tsm=this->mag;
	dialogLayer->setScore(tempScore);
	dialogLayer->setGuanKa(guanKa);
	dialogLayer->setPosition(ccp(0,0));
	this->addChild(dialogLayer,6);
}


void BanQiuLayer::setOutFielderFlag()
{
	if(!blurFlag)//不是 第三种道具
	{
		outFielderFlag = true;
	}
}

void BanQiuLayer::setOutPropFlag()
{
	outPropFlag = true;
}

//第二种道具停止守门员运动
void BanQiuLayer::stopFielder()
{
	for(int j=0;j<array->count();j++)//守门员
	{
		FielderSprite* tempSprite = (FielderSprite*)array->objectAtIndex(j);

		tempSprite->stopAction(tempSprite->ccat);//black 守门员停止
		stArr->addObject(tempSprite);//添加到停止数组里
		tempSprite->stopTime=getCurrentTime();
	}
}

void BanQiuLayer::outProp()
{
	//创建一个精灵对象，包含图片，充当移动道具
	Prop * propSprite1 = NULL;
	int w = rand()%3;//出那个道具
	switch(w)
	{
	case 0:propSprite1 = Prop::create("pic/red.png");propSprite1->mark=0;break;
	case 1:propSprite1 = Prop::create("pic/black.png");propSprite1->mark=1;break;
	case 2:propSprite1 = Prop::create("pic/blue.png");propSprite1->mark=2;break;
	}

	//设置道具精灵对象的初始位置
	propSprite1->setPosition(ccp(0,480 ));
	propSprite1->setAnchorPoint(ccp(0.5, 0.5));//默认锚点为0.5，0.5
	//将道具精灵添加到布景中
	this->addChild(propSprite1, GAME_LEVEL_WYF);

	ccBezierConfig bezier_7;//贝塞尔曲线
	bezier_7.controlPoint_1 = ccp(100, 460);
	bezier_7.controlPoint_2 = ccp(150, 400);
	bezier_7.endPosition = ccp(200,30);
	CCActionInterval*  cat_7 = CCBezierTo::create(2.5, bezier_7);

	ccBezierConfig bezier_8;//贝塞尔曲线
	bezier_8.controlPoint_1 = ccp(50, 480);
	bezier_8.controlPoint_2 = ccp(200, 400);
	bezier_8.endPosition = ccp(250,30);
	CCActionInterval*  cat_8 = CCBezierTo::create(2, bezier_8);

	ccBezierConfig bezier_9;//贝塞尔曲线
	bezier_9.controlPoint_1 = ccp(100, 480);
	bezier_9.controlPoint_2 = ccp(250, 400);
	bezier_9.endPosition = ccp(300,30);
	CCActionInterval*  cat_9 = CCBezierTo::create(3, bezier_9);

	CCSequence* cc_7 = CCSequence::create
	(
		cat_7,
		CCCallFuncND::create(this, callfuncND_selector(BanQiuLayer::removeProp), NULL),
		NULL
	);

	CCSequence* cc_8 = CCSequence::create
	(
		cat_8,
		CCCallFuncND::create(this, callfuncND_selector(BanQiuLayer::removeProp), NULL),
		NULL
	);

	CCSequence* cc_9 = CCSequence::create
	(
		cat_9,
		CCCallFuncND::create(this, callfuncND_selector(BanQiuLayer::removeProp), NULL),
		NULL
	);

	//走哪条路线
	int r = rand()%3;
	switch(r)
	{
	case 0:propSprite1->runAction(cc_7);break;
	case 1:propSprite1->runAction(cc_8);break;
	case 2:propSprite1->runAction(cc_9);break;
	}

	pArr->addObject(propSprite1);//把道具添加到数组里
}

void BanQiuLayer::outFielder()
{
	//创建一个精灵对象，包含fielder.png图片，充当移动的守门员1
	FielderSprite* fielderSprite1 = FielderSprite::create("pic/fielder.png");
	//设置fielder精灵对象的初始位置
	fielderSprite1->setPosition(ccp(GOALKEEPER_X, GOALKEEPER_Y));
	fielderSprite1->setAnchorPoint(ccp(0.5, 0.5));//默认锚点为0.5，0.5
	//将fielder精灵添加到布景中
	this->addChild(fielderSprite1, GAME_LEVEL_WYF);

	//动作序列中的6个动作
	CCActionInterval* at1=CCMoveBy::create(3.5,CCPointMake(-800,-170));
	CCActionInterval* at2=CCMoveBy::create(4,CCPointMake(-800,-100));
	CCActionInterval* at3=CCMoveBy::create(2.5,CCPointMake(-800,-30));
	CCActionInterval* at4=CCMoveBy::create(4.5,CCPointMake(-800,40));
	CCActionInterval* at5=CCMoveBy::create(5,CCPointMake(-800,110));
	CCActionInterval* at6=CCMoveBy::create(3,CCPointMake(-800,180));
	//走哪条路线
	int r = rand()%6;
	switch(r)
	{
	case 0:fielderSprite1->runAction(at1);fielderSprite1->ccat=at1;
	fielderSprite1->mark=1;break;
	case 1:fielderSprite1->runAction(at2);fielderSprite1->ccat=at2;
	fielderSprite1->mark=2;break;
	case 2:fielderSprite1->runAction(at3);fielderSprite1->ccat=at3;
	fielderSprite1->mark=3;break;
	case 3:fielderSprite1->runAction(at4);fielderSprite1->ccat=at4;
	fielderSprite1->mark=4;break;
	case 4:fielderSprite1->runAction(at5);fielderSprite1->ccat=at5;
	fielderSprite1->mark=5;break;
	case 5:fielderSprite1->runAction(at6);fielderSprite1->ccat=at6;
	fielderSprite1->mark=6;break;
	}

	array->addObject(fielderSprite1);//添加到循环表里
//	outFielderFlag = false;
}

void BanQiuLayer::outBall()//出球方法
{
	//创建一个小球对象，包含ball.png图片，充当球
	BallTest* ballSprite = BallTest::create("pic/ball.png");
	ballSprite->setXY(location.x,location.y);//设置小球的方向
	//设置精灵对象的位置
	ballSprite->setPosition(ccp(OUTBALL_X,OUTBALL_Y));
	//设置hitFlag标志位为true
	ballSprite->setHitFlag(true);
	ballSprite->setAnchorPoint(ccp(0.5, 0.5));//默认锚点为0.5，0.5

	arr->addObject(ballSprite);//把小球添加到循环表里
	//将精灵添加到布景中
	this->addChild(ballSprite, BACKGROUND_LEVEL_WYF);

	float vx = ballSprite->x;
	float vy = ballSprite->y;
	//出球动作
	CCActionInterval* at=CCMoveBy::create(OUTBALL_T,CCPointMake(BALL_V*vx,BALL_V*vy));
	seq = CCSequence::create
	(
		at,
		CCCallFuncND::create(this, callfuncND_selector(BanQiuLayer::removeBall), NULL),
		NULL
	);

	if(ballCount%10==0)//每5个小球里出来一个带火的小球
	{
		ballSprite->setMark(1);//给1代表带火的球
	}

	ballCount++;//发出球的总数加1
	ballSprite->runAction(at);//执行出球动作
	if(MUSIC)
	{
		//播放出球音乐
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect
		(
				"sound/fire.mp3"
		);
	}
}

//第三种道具效果出火
void BanQiuLayer::outFire()
{
	blurFlag = true;//第三种道具置成true

	CCParticleSystem* cps = CCParticleSun::create();
	cps->retain();
	cps->setPosition( ccp( 0, 7) );
	cps->setLife(0.01f);

	for(int i=0;i<48;i++)
	{
		fire[i]=CCSprite::create("pic/fire_2.png");
		fire[i]->setPosition(ccp(50,10*i));
		addChild(fire[i],GAME_LEVEL_WYF);

		fire[i]->addChild(cps, GAME_LEVEL_WYF);
		CCActionInterval* cs = CCMoveTo::create(1,CCPointMake(830,10*i));
		CCDelayTime *delay = CCDelayTime::create(3);
		fire[i]->runAction(
				CCSequence::create(
						cs,delay,CCCallFuncND::create(this, callfuncND_selector(BanQiuLayer::removeBlur), NULL),NULL));
	}

}

//第三种道具效果的回掉方法
void BanQiuLayer::removeBlur(CCNode* node,void* param)
{
	this->removeChild(node);
	blurFlag = false;
}

//移除道具
void BanQiuLayer::removeProp(CCNode* node,void* param)
{
	this->removeChild(node);
}

//移除小球方法
void BanQiuLayer::removeBall(CCNode* node,void* param)
{
	this->removeChild(node);
	arr->removeObject(node);//把小球从数组里删除
}

//进了网的加分动作
void BanQiuLayer::plussScore(float x,float y,int index)
{
	ccBezierConfig bezier;//贝塞尔曲线
	bezier.controlPoint_1 = ccp(350, 240);
	bezier.controlPoint_2 = ccp(250, 106);
	bezier.endPosition = ccp(SCORE_X,SCORE_Y);
	CCActionInterval*  bezierForward = CCBezierTo::create(1.5, bezier);

	ccBezierConfig bezier_1;//贝塞尔曲线
	bezier_1.controlPoint_1 = ccp(400, 350);
	bezier_1.controlPoint_2 = ccp(250, 100);
	bezier_1.endPosition = ccp(SCORE_X,SCORE_Y);
	CCActionInterval*  bezierForward_1 = CCBezierTo::create(1, bezier_1);

	ccBezierConfig bezier_2;//贝塞尔曲线
	bezier_2.controlPoint_1 = ccp(350, 200);
	bezier_2.controlPoint_2 = ccp(250, 100);
	bezier_2.endPosition = ccp(SCORE_X,SCORE_Y);
	CCActionInterval*  bezierForward_2 = CCBezierTo::create(1, bezier_2);

	ccBezierConfig bezier_3;//贝塞尔曲线
	bezier_3.controlPoint_1 = ccp(550, 200);
	bezier_3.controlPoint_2 = ccp(250, 100);
	bezier_3.endPosition = ccp(SCORE_X,SCORE_Y);
	CCActionInterval*  bezierForward_3 = CCBezierTo::create(1, bezier_3);

	ccBezierConfig bezier_4;//贝塞尔曲线
	bezier_4.controlPoint_1 = ccp(350, 200);
	bezier_4.controlPoint_2 = ccp(450, 100);
	bezier_4.endPosition = ccp(SCORE_X,SCORE_Y);
	CCActionInterval*  bezierForward_4 = CCBezierTo::create(1, bezier_4);

	//1号网系列
	CCSequence *one = CCSequence::create
	(
		bezierForward_1,
		CCCallFuncND::create(this,callfuncND_selector(BanQiuLayer::removeScoreOne),NULL ),
		NULL
	);
	CCSequence *oneDown = CCSequence::create
	(
		bezierForward_2,
		CCCallFuncND::create(this,callfuncND_selector(BanQiuLayer::removeScoreOne),NULL ),
		NULL
	);
	//2号网动作系列
	CCSequence *two = CCSequence::create
	(
		bezierForward_3,
		CCCallFuncND::create(this,callfuncND_selector(BanQiuLayer::removeScoreTwo),NULL ),
		NULL
	);
	//2号网动作系列
	CCSequence *twoDown = CCSequence::create
	(
		bezierForward_4,
		CCCallFuncND::create(this,callfuncND_selector(BanQiuLayer::removeScoreTwo),NULL ),
		NULL
	);
	//6号网动作系列
	CCSequence *six = CCSequence::create
	(
		bezierForward,
		CCCallFuncND::create(this,callfuncND_selector(BanQiuLayer::removeScoreSix),NULL ),
		NULL
	);
	CCSprite *sixSprite=NULL;
	switch(index)
	{
	case 1:sixSprite = CCSprite::create("pic/score_1.png");
	sixSprite->runAction(one);
	break;
	case 2:sixSprite = CCSprite::create("pic/score_1.png");
	sixSprite->runAction(oneDown);
	break;
	case 3:sixSprite = CCSprite::create("pic/score_2.png");
	sixSprite->runAction(two);
	break;
	case 4:sixSprite = CCSprite::create("pic/score_2.png");
	sixSprite->runAction(two);
	break;
	case 5:sixSprite = CCSprite::create("pic/score_6.png");
	sixSprite->runAction(six);
	break;
	}
	//设置精灵对象的位置
	sixSprite->setPosition(ccp(x,y));
	//将精灵添加到布景中
	this->addChild(sixSprite, BACKGROUND_LEVEL_WYF);
}

//移除1分数图片然后加分
void BanQiuLayer::removeScoreOne(CCNode* node,void* param)
{
	tempScore+=1;//加分
	char a[6];//把int 型的分数转换成string型的 然后set
	snprintf(a, 6, "%d",tempScore);
	pLabel->setString(a);
	this->removeChild(node);
	if(tempScore>guanka*(this->targetScore)||tempScore==guanka*(this->targetScore))
	{
		mag->toWinLayer(tempScore,(guanka+1));
		//播放胜利音乐
		if(MUSIC)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect
			(
					"sound/victory.mp3"
			);
		}

	}
}

//移除2分数图片然后加分
void BanQiuLayer::removeScoreTwo(CCNode* node,void* param)
{
	tempScore+=2;//加分
	char a[6];//把int 型的分数转换成string型的 然后set
	snprintf(a, 6, "%d",tempScore);
	pLabel->setString(a);
	this->removeChild(node);
	if(tempScore>guanka*(this->targetScore)||tempScore==guanka*(this->targetScore))
	{
		mag->toWinLayer(tempScore,guanka+1);
		//播放胜利音乐
		if(MUSIC)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect
			(
					"sound/victory.mp3"
			);
		}
	}
}

//移除6分数图片然后加分
void BanQiuLayer::removeScoreSix(CCNode* node,void* param)
{
	tempScore+=6;//加分
	char a[6];//把int 型的分数转换成string型的 然后set
	snprintf(a, 6, "%d",tempScore);
	pLabel->setString(a);
	this->removeChild(node);
	if(tempScore>guanka*(this->targetScore)||tempScore==guanka*(this->targetScore))
	{
		mag->toWinLayer(tempScore,guanka+1);
		//播放胜利音乐
		if(MUSIC)
		{
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect
			(
					"sound/victory.mp3"
			);
		}
	}
}

//获得系统时间
long BanQiuLayer::getCurrentTime()
{
	struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

//返回键监听
void BanQiuLayer::keyBackClicked()
{
	//暂停声音播放
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	mag->toBeginLayer();
}
