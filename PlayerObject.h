/* 
 * File:   PlayerObject.h
 * Author: alexey
 *
 * Created on 31 Август 2014 г., 3:43
 */

#ifndef PLAYEROBJECT_H
#define	PLAYEROBJECT_H

#include "RestfulObject.h"

class PlayerObject : public RestfulObject
{
public:
    PlayerObject(std::string n);
    virtual ~PlayerObject();
    
    virtual void method_get(std::vector<std::string>, std::string *request = 0, std::string *responce = 0);
    virtual void method_post(std::vector<std::string>, std::string *request = 0, std::string *responce = 0);
    virtual void method_put(std::vector<std::string>, std::string *request = 0, std::string *responce = 0);
    virtual void method_delete(std::vector<std::string>, std::string *request = 0, std::string *responce = 0);
};

#endif	/* PLAYEROBJECT_H */

