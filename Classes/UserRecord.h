//
//  UserRecord.h
//  Cricket
//
//  Created by JUN LIU on 9/11/14.
//
//

#ifndef Cricket_UserRecord_h
#define Cricket_UserRecord_h

#include "cocos2d.h"
using namespace cocos2d;

#include <string>

class UserRecord
{
public:
    static UserRecord* getInstance();
    
public:
    UserRecord();
    virtual ~UserRecord();
    
public:
    bool init();
    
public:
    int getInt(const char* key, int value);
    void saveInt(const char* key, int value);
    
    float getFloat(const char* key, float value);
    void saveFloat(const char* key, float value);
    
    
    bool getBool(const char* key, bool value);
    void saveBool(const char* key, bool value);
    
    std::string getString(const char* key, const char* value);
    void saveString(const char* key, const char* value);
    
private:
    static UserRecord* instance;
};

#endif
