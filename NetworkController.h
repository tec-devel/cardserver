/* 
 * File:   NetworkController.h
 * Author: alexey
 *
 * Created on 31 Август 2014 г., 2:35
 */

#ifndef NETWORKCONTROLLER_H
#define	NETWORKCONTROLLER_H

#include <map>
#include <string>
#include <vector>

class RestfulObject;

class NetworkController {

    std::map<std::string, RestfulObject*> m_objects;

    NetworkController();
    static NetworkController* m_network_controller;

public:
    virtual ~NetworkController();

    static NetworkController* instance()
    {
        if(!m_network_controller)
            m_network_controller = new NetworkController;
        
        return m_network_controller;
    }
    
    void registerObject(RestfulObject* object);
    
    void methodGet(std::string object, const std::vector<std::string>&, std::string *request = 0, std::string *reply = 0);
    void methodPost(std::string object, const std::vector<std::string>&, std::string *request = 0, std::string *reply = 0);
    void methodPut(std::string object, const std::vector<std::string>&, std::string *request = 0, std::string *reply = 0);
    void methodDelete(std::string object, const std::vector<std::string>&, std::string *request = 0, std::string *reply = 0);

};

#endif	/* NETWORKCONTROLLER_H */

