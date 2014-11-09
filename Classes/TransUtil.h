#ifndef __TransUtil_H__
#define __TransUtil_H__

#include "cocos2d.h"

//各种变换
class FadeWhiteTransition : public CCTransitionFade
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFade::create(t, s, ccWHITE);
    }
};

class FlipXLeftOver : public CCTransitionFlipX
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipX::create(t, s, kCCTransitionOrientationLeftOver);
    }
};

class FlipXRightOver : public CCTransitionFlipX
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipX::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class FlipYUpOver : public CCTransitionFlipY
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipY::create(t, s, kCCTransitionOrientationUpOver);
    }
};

class FlipYDownOver : public CCTransitionFlipY
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipY::create(t, s, kCCTransitionOrientationDownOver);
    }
};

class FlipAngularLeftOver : public CCTransitionFlipAngular
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipAngular::create(t, s, kCCTransitionOrientationLeftOver);
    }
};

class FlipAngularRightOver : public CCTransitionFlipAngular
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionFlipAngular::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class ZoomFlipXLeftOver : public CCTransitionZoomFlipX
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipX::create(t, s, kCCTransitionOrientationLeftOver);
    }
};

class ZoomFlipXRightOver : public CCTransitionZoomFlipX
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipX::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class ZoomFlipYUpOver : public CCTransitionZoomFlipY
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipY::create(t, s, kCCTransitionOrientationUpOver);

    }
};

class ZoomFlipYDownOver : public CCTransitionZoomFlipY
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipY::create(t, s, kCCTransitionOrientationDownOver);
    }
};

class ZoomFlipAngularLeftOver : public CCTransitionZoomFlipAngular
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipAngular::create(t, s, kCCTransitionOrientationLeftOver);
    }
};

class ZoomFlipAngularRightOver : public CCTransitionZoomFlipAngular
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        return CCTransitionZoomFlipAngular::create(t, s, kCCTransitionOrientationRightOver);
    }
};

class PageTransitionForward : public CCTransitionPageTurn
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCTransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public CCTransitionPageTurn
{
public:
    static CCTransitionScene* create(float t, CCScene* s)
    {
        CCDirector::sharedDirector()->setDepthTest(true);
        return CCTransitionPageTurn::create(t, s, true);
    }
};
class TransUtil
{
public:
	//场景切换的静态方法
	static CCTransitionScene* createTransition(int nIndex, float t, CCScene* s)
	{
	    CCDirector::sharedDirector()->setDepthTest(false);
	    switch(nIndex)
	    {
	    case 0: return CCTransitionJumpZoom::create(t, s);

	    case 1: return CCTransitionProgressRadialCCW::create(t, s);
	    case 2: return CCTransitionProgressRadialCW::create(t, s);
	    case 3: return CCTransitionProgressHorizontal::create(t, s);
	    case 4: return CCTransitionProgressVertical::create(t, s);
	    case 5: return CCTransitionProgressInOut::create(t, s);
	    case 6: return CCTransitionProgressOutIn::create(t, s);

	    case 7: return CCTransitionCrossFade::create(t,s);//当前场景淡出，另一场景淡入

	    case 8: return PageTransitionForward::create(t, s);
	    case 9: return PageTransitionBackward::create(t, s);
	    case 10: return CCTransitionFadeTR::create(t, s);
	    case 11: return CCTransitionFadeBL::create(t, s);
	    case 12: return CCTransitionFadeUp::create(t, s);
	    case 13: return CCTransitionFadeDown::create(t, s);

	    case 14: return CCTransitionTurnOffTiles::create(t, s);//溶解的效果

	    case 15: return CCTransitionSplitRows::create(t, s);
	    case 16: return CCTransitionSplitCols::create(t, s);

	    case 17: return CCTransitionFade::create(t, s);
	    case 18: return FadeWhiteTransition::create(t, s);

	    case 19: return FlipXLeftOver::create(t, s);
	    case 20: return FlipXRightOver::create(t, s);
	    case 21: return FlipYUpOver::create(t, s);
	    case 22: return FlipYDownOver::create(t, s);
	    case 23: return FlipAngularLeftOver::create(t, s);
	    case 24: return FlipAngularRightOver::create(t, s);

	    case 25: return ZoomFlipXLeftOver::create(t, s);
	    case 26: return ZoomFlipXRightOver::create(t, s);
	    case 27: return ZoomFlipYUpOver::create(t, s);
	    case 28: return ZoomFlipYDownOver::create(t, s);
	    case 29: return ZoomFlipAngularLeftOver::create(t, s);
	    case 30: return ZoomFlipAngularRightOver::create(t, s);

	    case 31: return CCTransitionShrinkGrow::create(t, s);
	    case 32: return CCTransitionRotoZoom::create(t, s);

	    case 33: return CCTransitionMoveInL::create(t, s);
	    case 34: return CCTransitionMoveInR::create(t, s);
	    case 35: return CCTransitionMoveInT::create(t, s);
	    case 36: return CCTransitionMoveInB::create(t, s);

	    case 37: return CCTransitionSlideInL::create(t, s);
	    case 38: return CCTransitionSlideInR::create(t, s);
	    case 39: return CCTransitionSlideInT::create(t, s);
	    case 40: return CCTransitionSlideInB::create(t, s);

	    default: break;
	    }
	    return NULL;
	}

};

#endif
