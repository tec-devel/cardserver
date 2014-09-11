/* 
 * File:   TableController.cpp
 * Author: alexey
 * 
 * Created on 31 Август 2014 г., 2:13
 */

#include "TableObject.h"

#include <Table.h>
#include "GameController.h"
#include <stdlib.h>
#include <iostream>

#include <json/json.h>

TableObject::TableObject(const std::string& n)
: RestfulObject(n)
{
}

TableObject::~TableObject()
{
}

void TableObject::method_get(std::vector<std::string>, std::string*, std::string*)
{
    std::cout << "TableObject::method_get" << std::endl;
}

void TableObject::method_post(std::vector<std::string> restful_data, std::string*, std::string* responce)
{
    if (!restful_data.empty())
    {
        cardsrv::Table *table = new cardsrv::Table(atoi(restful_data[1].data()));
        GameController::instance()->addTable(table);
        
        json_object * jobj = json_object_new_object();

        json_object_object_add(jobj, "id", json_object_new_int(table->id()));
        responce->append(json_object_to_json_string(jobj));
    }
}

void TableObject::method_put(std::vector<std::string>, std::string*, std::string*)
{
}

void TableObject::method_delete(std::vector<std::string> restful_data, std::string*, std::string*)
{
    if (!restful_data.empty())
    {
        cardsrv::Table *table = GameController::instance()->removeTable(atoi(restful_data[0].data()));
        if (table)
            delete table;
    }
}

