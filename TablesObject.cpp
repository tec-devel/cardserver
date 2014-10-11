/* 
 * File:   TablesObject.cpp
 * Author: alexey
 * 
 * Created on 11 Октябрь 2014 г., 15:46
 */

#include "TablesObject.h"
#include "GameController.h"

#include <AbstractTable.h>

#include <json/json.h>

TablesObject::TablesObject(const std::string& n)
: RestfulObject(n)
{
}

TablesObject::~TablesObject()
{
}

void TablesObject::method_get(std::vector<std::string> restful_data, const std::string&, std::string *responce)
{
        if (restful_data.size() == 1)
    {
        json_object * jobj = json_object_new_object();
        json_object * j_table_array = json_object_new_array();
        json_object * j_table;

        std::map <int, cardsrv::AbstractTable*> tables = GameController::instance()->tables();
        std::map <int, cardsrv::AbstractTable*>::iterator it;
        for (it = tables.begin(); it != tables.end(); ++it)
        {
            j_table = json_object_new_object();
            json_object_object_add(j_table, "id", json_object_new_int((*it).second->id()));
            json_object_object_add(j_table, "max_players", json_object_new_int((*it).second->maxPlayers()));
            json_object_object_add(j_table, "real_players", json_object_new_int((*it).second->realPlayers()));
            json_object_array_add(j_table_array, j_table);
        }

        json_object_object_add(jobj, "tables", j_table_array);

        *responce = std::string(json_object_to_json_string(jobj));
    }
}

void TablesObject::method_post(std::vector<std::string>, const std::string&, std::string*)
{
}

void TablesObject::method_put(std::vector<std::string>, const std::string&, std::string*)
{
}

void TablesObject::method_delete(std::vector<std::string>, const std::string&, std::string*)
{
}

