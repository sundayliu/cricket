//
//  UserRecord.cpp
//  Cricket
//
//  Created by JUN LIU on 9/11/14.
//
//

#include "UserRecord.h"

UserRecord* UserRecord::instance = NULL;

UserRecord::UserRecord()
{
    
}

UserRecord::~UserRecord()
{
    
}

bool UserRecord::init()
{
    return true;
}

UserRecord* UserRecord::getInstance()
{
    if (instance == NULL)
    {
        instance = new UserRecord();
        if (!instance->init())
        {
            delete instance;
            instance = NULL;
        }
    }
    
    return instance;
}

int UserRecord::getInt(const char* key, int value)
{
    return CCUserDefault::sharedUserDefault()->getIntegerForKey(key,value);
}

void UserRecord::saveInt(const char* key, int value)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey(key, value);
}

float UserRecord::getFloat(const char* key, float value)
{
    return CCUserDefault::sharedUserDefault()->getFloatForKey(key,value);
}

void UserRecord::saveFloat(const char* key, float value)
{
    CCUserDefault::sharedUserDefault()->setFloatForKey(key, value);
}

bool UserRecord::getBool(const char* key, bool value)
{
    return CCUserDefault::sharedUserDefault()->getBoolForKey(key, value);
}

void UserRecord::saveBool(const char* key, bool value)
{
    CCUserDefault::sharedUserDefault()->setBoolForKey(key, value);
}

std::string UserRecord::getString(const char* key, const char* value)
{
    return CCUserDefault::sharedUserDefault()->getStringForKey(key, value);
}

void UserRecord::saveString(const char* key, const char* value)
{
    CCUserDefault::sharedUserDefault()->setStringForKey(key, value);
}


