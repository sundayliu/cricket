#ifndef __AppMacros_H__
#define __AppMacros_H__

#include "cocos2d.h"

//#include <string>

//定义表示图片资源套装的结构体
typedef struct tagResource
{
    cocos2d::CCSize size;  //此资源包对应的分辨率（包括宽度、高度）
    char directory[100];   //此资源包子目录名
}PicResource;

//定义表示声音资源套装的结构体
typedef struct SoundResourceStruct
{
    char directory[100];   //此资源包子目录名
}SoundResource;
extern const std::string classPath;
//创建不同名称资源套装的结构体实例
static PicResource picResource  =  { cocos2d::CCSizeMake(800, 480),"pic"};
static SoundResource soundResource  =  {"sound"};

//根据不同的目标分辨率设置Cocos2dx的工作尺寸
static cocos2d::CCSize designResolutionSize = cocos2d::CCSizeMake(800, 480);

//动态计算字体大小
#define TITLE_FONT_SIZE  (cocos2d::CCEGLView::sharedOpenGLView()->getDesignResolutionSize().width / picResource.size.width * 30)

//设置物体位置常量
#define GRID_ONE_TOP_X 491        //上面1号网的x位置
#define GRID_ONE_TOP_Y 480        //上面1号网的Y位置
#define GRID_ONE_TOP_INDEX 1      //上面1号网的编号

#define GRID_ONE_BOTTOM_X 491     //下面1号网的x位置
#define GRID_ONE_BOTTOM_Y 30      //下面1号网的Y位置
#define GRID_ONE_BOTTOM_INDEX 2   //下面1号网的编号

#define GRID_TWO_TOP_X 741        //上面2号网的x位置
#define GRID_TWO_TOP_Y 480        //上面2号网的Y位置
#define GRID_TWO_TOP_INDEX 3      //上面2号网的编号

#define GRID_TWO_BOTTOM_X 741     //下面2号网的x位置
#define GRID_TWO_BOTTOM_Y 30      //下面2号网的Y位置
#define GRID_TWO_BOTTOM_INDEX 4   //下面2号网的编号

#define GRID_SIX_X 800            //6号网的x位置
#define GRID_SIX_Y 255            //6号网的y位置
#define GRID_SIX_INDEX 5          //6号网的编号

#define BOARD_X 0                 //仪表盘的x位置
#define BOARD_Y 0                 //仪表盘的y位置
#define SCORE_HEIGHT 30           //仪表盘的高度

#define PLAYER_X 30               //球员的x位置
#define PLAYER_Y 180              //球员的y位置

#define GOALKEEPER_X 800          //守门员的x位置
#define GOALKEEPER_Y 240          //守门员的y位置

#define OUTBALL_X 100             //出球的x位置
#define OUTBALL_Y 200             //出球的y位置
#define OUTBALL_T 2               //出球的时间
#define BALL_V 800                //球的速度


#define TARGET_SCORE 50           //目标分数

#define SCORE_X 157               //分数的x位置
#define SCORE_Y 17                //分数的y位置

#define GRID_WIDTH 190            //网格的宽度
#define GRID_HEIGHT 59            //网格的高度

#define GRID_OFFSET 15            //网格偏移量
#define TARGETLABEL_X 580         //目标分数label的x位置
#define OVERLABEL_X 340           //被挡次数文本标签的x位置
#define SPACE_TIME 300            //发两球最短时间间隔单位毫秒

//定义不同层次的Z Level
#define BACKGROUND_LEVEL_WYF 0	  //背景层次
#define GAME_LEVEL_WYF 1		  //游戏活动层次
#define DASHBOARD_LEVEL_WYF 2	  //仪表板层次
#define TOP_LEVEL 3               //仪表板上面的层

extern int guanKa;
extern bool BACKMUSIC;
extern bool MUSIC;

#endif
