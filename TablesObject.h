/* 
 * File:   TablesObject.h
 * Author: alexey
 *
 * Created on 11 Октябрь 2014 г., 15:46
 */

#ifndef TABLESOBJECT_H
#define	TABLESOBJECT_H

#include "RestfulObject.h"

class TablesObject : public RestfulObject {
public:
    TablesObject(const std::string& n);
    virtual ~TablesObject();

    void method_get(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0);
    void method_post(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0);
    void method_put(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0);
    void method_delete(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0);
};

#endif	/* TABLESOBJECT_H */

