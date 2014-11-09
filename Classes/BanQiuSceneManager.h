#ifndef __BallSimpleSceneManager_H__
#define __BallSimpleSceneManager_H__

#include "cocos2d.h"

//用于创建场景的类
class BanQiuSceneManager
{
public:
	//创建场景对象的方法
    cocos2d::CCScene* createScene();
    void toGameLayer(int guanka);
    void toLoseLayer(int score,int guanKa);
    void toWinLayer(int score,int guanka);
    void toNewGameLayer(int guanka);
    void toBeginLayer();
    void toBeginLayer(int score,int guanKa);
    void toHelpLayer();
    void toAchieveLayer();
    void toSetLayer();
    void toOutLayer();
	void setAchieve(int score,int guanKa);
    int getMaxScore();
    int getGuanKa();
};

#endif
