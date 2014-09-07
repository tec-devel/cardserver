/* 
 * File:   NetworkController.cpp
 * Author: alexey
 * 
 * Created on 31 Август 2014 г., 2:35
 */

#include "NetworkController.h"
#include "RestfulObject.h"

NetworkController* NetworkController::m_network_controller = 0;


NetworkController::NetworkController()
{
}

NetworkController::~NetworkController()
{
}

void NetworkController::registerObject(RestfulObject* object)
{
    m_objects.insert(std::make_pair(object->name(), object));
}

void NetworkController::methodGet(std::string object, const std::vector<std::string>& data)
{
    std::map<std::string, RestfulObject*>::iterator it;
    if((it = m_objects.find(object)) != m_objects.end())
        (*it).second->method_get(data);
}

void NetworkController::methodPost(std::string object, const std::vector<std::string>& data)
{
    std::map<std::string, RestfulObject*>::iterator it;
    if((it = m_objects.find(object)) != m_objects.end())
        (*it).second->method_post(data);
}

void NetworkController::methodPut(std::string object, const std::vector<std::string>& data)
{
    std::map<std::string, RestfulObject*>::iterator it;
    if((it = m_objects.find(object)) != m_objects.end())
        (*it).second->method_put(data);
}

void NetworkController::methodDelete(std::string object, const std::vector<std::string>& data)
{
    std::map<std::string, RestfulObject*>::iterator it;
    if((it = m_objects.find(object)) != m_objects.end())
        (*it).second->method_delete(data);
}
