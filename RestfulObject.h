/* 
 * File:   RestfulController.h
 * Author: alexey
 *
 * Created on 31 Август 2014 г., 2:14
 */

#ifndef RESTFULCONTROLLER_H
#define	RESTFULCONTROLLER_H

#include <string>
#include <vector>

class RestfulObject {
    std::string m_name;

public:
    RestfulObject(const std::string& n);
    virtual ~RestfulObject();

    std::string name() const {
        return m_name;
    }

    virtual void method_get(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0) = 0;
    virtual void method_post(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0) = 0;
    virtual void method_put(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0) = 0;
    virtual void method_delete(std::vector<std::string> restful_data, const std::string& request = std::string(), std::string *responce = 0) = 0;

};

#endif	/* RESTFULCONTROLLER_H */

