/* 
 * File:   PlayerObject.cpp
 * Author: alexey
 * 
 * Created on 31 Август 2014 г., 3:43
 */

#include "PlayerObject.h"

#include "GameController.h"
#include <AbstractPlayer.h>
#include <stdlib.h>

#include <json/json.h>

#include <iostream>
#include <sstream>

using namespace cardsrv;

PlayerObject::PlayerObject(std::string n)
: RestfulObject(n)
{
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::method_get(std::vector<std::string> restful_data, const std::string&, std::string* responce)
{
    std::cout << "PlayerObject::method_get" << std::endl;

    if (restful_data.size() == 3)
    {
        AbstractPlayer *player = GameController::instance()->player(atoi(restful_data[AbstractPlayer::PlayerId].data()));
        if (player && player->tokenGet() == restful_data[AbstractPlayer::PlayerToken])
        {
            player->get(restful_data, *responce);
            std::string get_token = "1";
            player->setGetToken(get_token);
        }
    }
}

void PlayerObject::method_post(std::vector<std::string> restful_data, const std::string&, std::string* responce)
{
    std::cout << "PlayerObject::method_post" << std::endl;

    json_object * jobj = json_object_new_object();

    if (restful_data.size() == 3)
    {
        bool result = GameController::instance()->addPlayerToTable(atoi(restful_data[1].data()), atoi(restful_data[2].data()));

        json_object_object_add(jobj, "status", json_object_new_int((int) result));

        if (result)
        {
            cardsrv::AbstractPlayer *player = GameController::instance()->player(atoi(restful_data[1].data()));
            if (player)
            {
                std::string get_token = "1", put_token = "2";
                player->setGetToken(get_token);
                json_object_object_add(jobj, "get_token", json_object_new_string(get_token.data()));
                player->setPutToken(put_token);
                json_object_object_add(jobj, "put_token", json_object_new_string(put_token.data()));

            }
        }

        responce->append(json_object_to_json_string(jobj));
    }

    //    if (responce->empty())
    //        json_object_object_add(jobj, "status", json_object_new_int((int) false));

}

void PlayerObject::method_put(std::vector<std::string> restful_data, const std::string& request, std::string* responce)
{
    std::cout << "PlayerObject::method_put" << std::endl;

    if (restful_data.size() == 4)
    {
        AbstractPlayer *player = GameController::instance()->player(atoi(restful_data[AbstractPlayer::PlayerId].data()));
        if (player && player->tokenPut() == restful_data[AbstractPlayer::PlayerToken])
        {
            player->put(restful_data, request, *responce);
            std::string put_token = "2";
            player->setPutToken(put_token);
        }
    }
}

void PlayerObject::method_delete(std::vector<std::string>, const std::string&, std::string*)
{
    std::cout << "PlayerObject::method_delete" << std::endl;
}

