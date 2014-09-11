/* 
 * File:   PlayerObject.cpp
 * Author: alexey
 * 
 * Created on 31 Август 2014 г., 3:43
 */

#include "PlayerObject.h"

#include "GameController.h"
#include <Player.h>
#include <stdlib.h>

#include <json/json.h>


#include <iostream>
#include <sstream>
#include <json/json_object.h>
#include <string.h>

//using namespace boost::property_tree;
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

    const Player *player = GameController::instance()->const_player(atoi(restful_data[1].data()));



    //    {
    //"players" : [
    //	{"id": 1, "cards": 5, "status": "passive", "activity": "enabled"},
    //	{"id": 2, "cards": 5, "status": "active", "activity": "enabled"},
    //	{"id": 3, "cards": 5, "status": "active", "activity": "enabled"}
    //	],
    //
    //"player": {
    //	"status": "active",
    //	"activity": "enabled",
    //	"cards":["C6","C7","C8","C9","C10","CJ"]
    //	},
    //
    //"table": {
    //	"trump": "CA",
    //	"slots": [
    //		{"number": 1, "down": "S6", "up": "S7"},
    //		{"number": 2, "down": "D7", "up": "D8"},
    //		{"number": 3, "down": "H8", "up": "H9"}
    //		]
    //	}
    //}



    //if (responce)
    {
        json_object * jobj = json_object_new_object();

        json_object * jplayers_array = json_object_new_array();
        json_object * jtable_player = 0;
        json_object * jtable_player_id = 0;
        json_object * jtable_player_cards = 0;

        std::list<Player*> tmp_player_list = player->table_players();

        for (std::list<Player*>::const_iterator it = tmp_player_list.begin();
                it != tmp_player_list.end();
                ++it)
        {
            json_object * jtable_player_status = 0;
            json_object * jtable_player_activity = 0;
            switch ((*it)->status())
            {
            case Player::Active:
                jtable_player_status = json_object_new_string("active");
                break;
            case Player::Passive:
                jtable_player_status = json_object_new_string("passive");
                break;
            case Player::Neutral:
                jtable_player_status = json_object_new_string("neutral");
                break;
            }

            switch ((*it)->activity())
            {
            case Player::Enabled:
                jtable_player_activity = json_object_new_string("enabled");
                break;
            case Player::Disabled:
                jtable_player_activity = json_object_new_string("disabled");
                break;
            }

            jtable_player = json_object_new_object();

            jtable_player_id = json_object_new_int(-1);
            jtable_player_cards = json_object_new_int((*it)->cards().size());

            json_object_object_add(jtable_player, "id", jtable_player_id);
            json_object_object_add(jtable_player, "cards", jtable_player_cards);
            json_object_object_add(jtable_player, "status", jtable_player_status);
            json_object_object_add(jtable_player, "activity", jtable_player_activity);

            json_object_array_add(jplayers_array, jtable_player);
        }

        json_object_object_add(jobj, "players", jplayers_array);

        json_object * jplayer = json_object_new_object();
        json_object * jplayer_cards = json_object_new_array(); // json_object_new_string();
        json_object * jplayer_one_card = 0; // json_object_new_string();

        switch (player->status())
        {
        case Player::Active:
            json_object_object_add(jplayer, "status", json_object_new_string("active"));
            break;
        case Player::Passive:
            json_object_object_add(jplayer, "status", json_object_new_string("passive"));
            break;
        case Player::Neutral:
            json_object_object_add(jplayer, "status", json_object_new_string("neutral"));
            break;
        }

        switch (player->activity())
        {
        case Player::Enabled:
            json_object_object_add(jplayer, "activity", json_object_new_string("enabled"));
            break;
        case Player::Disabled:
            json_object_object_add(jplayer, "activity", json_object_new_string("disabled"));
            break;
        }


        std::list<Card> tmp_card_list = player->cards();
        for (std::list<Card>::const_iterator p_it = tmp_card_list.begin();
                p_it != tmp_card_list.end();
                ++p_it)
        {
            jplayer_one_card = json_object_new_string((*p_it).toString().data());
            json_object_array_add(jplayer_cards, jplayer_one_card);
        }

        json_object_object_add(jplayer, "cards", jplayer_cards);
        json_object_object_add(jobj, "player", jplayer);

        json_object * jtable = json_object_new_object();
        json_object * jtable_trump = json_object_new_int(player->table_trump());
        json_object * jtable_slots = json_object_new_array();
        json_object * jtable_slot = 0;

        int i = 0;
        std::list<Slot*> tmp_slot_list = player->table_slots();
        for (std::list<Slot*>::const_iterator s_it = tmp_slot_list.begin();
                s_it != tmp_slot_list.end();
                ++s_it, i++)
        {
            jtable_slot = json_object_new_object();
            json_object_object_add(jtable_slot, "number", json_object_new_int(i));

            if ((*s_it)->cards().size() == 1)
                json_object_object_add(jtable_slot, "up", json_object_new_string((*s_it)->cards()[0].toString().data()));

            if ((*s_it)->cards().size() == 2)
                json_object_object_add(jtable_slot, "down", json_object_new_string((*s_it)->cards()[1].toString().data()));

            json_object_array_add(jtable_slots, jtable_slot);
        }

        json_object_object_add(jtable, "trump", jtable_trump);
        json_object_object_add(jtable, "slots", jtable_slots);

        json_object_object_add(jobj, "table", jtable);

        responce->append(json_object_to_json_string(jobj));
    }
}

void PlayerObject::method_post(std::vector<std::string> restful_data, const std::string&, std::string* responce)
{
    if (restful_data.size() == 3)
    {
        bool result = GameController::instance()->addPlayerToTable(atoi(restful_data[1].data()), atoi(restful_data[2].data()));

        json_object * jobj = json_object_new_object();
        json_object_object_add(jobj, "status", json_object_new_int((int) result));

        if (result)
        {
            cardsrv::Player *player = GameController::instance()->player(atoi(restful_data[1].data()));
            if (player)
                json_object_object_add(jobj, "token", json_object_new_string(player->genToken().data()));
        }

        responce->append(json_object_to_json_string(jobj));
    }
}

void PlayerObject::method_put(std::vector<std::string> restful_data, const std::string& request, std::string* responce)
{
//{
//    "turn" : { "token": "1", "slot" : 1, "card" : "S6"}
//}

    if (!request.empty())
    {
        json_object * jobj = json_tokener_parse(request.data());

        int slot_number = -1;
        std::string card;
        std::string token;

        enum json_type type, turn_type;

        json_object_object_foreach(jobj, key, val)
        {
            type = json_object_get_type(val);
            switch (type)
            {
            case json_type_object:
                json_object_object_foreach(val, key1, val1)
            {
                turn_type = json_object_get_type(val1);
                switch (turn_type)
                {
                case json_type_int:
                    slot_number = json_object_get_int(val1);
                    break;
                case json_type_string:
                    if (strcmp(key1, "card") == 0)
                        card.append(json_object_get_string(val1));
                    else if (strcmp(key1, "token") == 0)
                        token.append(json_object_get_string(val1));
                    break;
                }
            }
                break;
            }
        }

        if (slot_number != -1 && !card.empty())
        {
            cardsrv::Player* player = GameController::instance()->player(atoi(restful_data[1].data()));

            if (player)
            {
                std::list<cardsrv::Card> turn_list;
                cardsrv::Card turn_card = cardsrv::Card::fromString(card);
                turn_list.push_back(turn_card);

                // todo: token!!!
                // todo: проверять, есть ли такая карта у игрока!
                
                cardsrv::Player::TurnStatus status = player->turnFromClient(turn_list, token, slot_number);

                json_object * jobj = json_object_new_object();
                switch (status)
                {
                case cardsrv::Player::Success:
                    json_object_object_add(jobj, "status", json_object_new_string("success"));
                    break;
                case cardsrv::Player::Fail:
                    json_object_object_add(jobj, "status", json_object_new_string("fail"));
                    break;
                }
                responce->append(json_object_to_json_string(jobj));
            }
        }
    }
}

void PlayerObject::method_delete(std::vector<std::string>, const std::string&, std::string*)
{
}

