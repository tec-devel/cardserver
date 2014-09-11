/* 
 * File:   TableController.h
 * Author: alexey
 *
 * Created on 31 Август 2014 г., 2:13
 */

#ifndef TABLECONTROLLER_H
#define	TABLECONTROLLER_H

#include "RestfulObject.h"

class TableObject : public RestfulObject 
{
public:
    TableObject(const std::string& name);
    virtual ~TableObject();
    
    virtual void method_get(std::vector<std::string>,  const std::string& request = std::string(), std::string *responce = 0);
    virtual void method_post(std::vector<std::string>,  const std::string& request = std::string(), std::string *responce = 0);
    virtual void method_put(std::vector<std::string>,  const std::string& request = std::string(), std::string *responce = 0);
    virtual void method_delete(std::vector<std::string>,  const std::string& request = std::string(), std::string *responce = 0);
    
private:

};

#endif	/* TABLECONTROLLER_H */

