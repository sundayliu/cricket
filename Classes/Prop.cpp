
#include "Prop.h"
#include <string.h>
#include <vector>



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

//构造函数
Prop::Prop()
{

}
Prop* Prop::create(const char* pic)
{
	Prop* temp = NULL;
	temp = new Prop();
	temp->initWithFile(pic);
	temp->autorelease();
	return temp;
}




