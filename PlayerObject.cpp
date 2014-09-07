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

//#include <json/json.h>


#include <iostream>

//using namespace boost::property_tree;
using namespace cardsrv;

PlayerObject::PlayerObject(std::string n)
: RestfulObject(n)
{
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::method_get(std::vector<std::string> restful_data, std::string*, std::string* responce)
{
    std::cout << "PlayerObject::method_get" << std::endl;

    const Player *player = GameController::instance()->player(atoi(restful_data[0].data()));

    if (responce)
    {
        //        ptree root_t;
        //        ptree player_t, players_t;
        //        ptree slot_t, slots_t;
        //        ptree cards_t;
        //
        //        BOOST_FOREACH(Player* tmp_player, player->table_players())
        //        {
        //            switch (player->status())
        //            {
        //            case Player::Active:
        //                status = "active";
        //                break;
        //            case Player::Passive:
        //                status = "passive";
        //                break;
        //            case Player::Neutral:
        //                status = "neutral";
        //                break;
        //            }
        //
        //            switch (player->activity())
        //            {
        //            case Player::Enabled:
        //                activity = "enabled";
        //                break;
        //            case Player::Disabled:
        //                activity = "disabled";
        //                break;
        //            }
        //
        //            player_t.push_back(std::make_pair("status", status));
        //            player_t.push_back(std::make_pair("activity", activity));
        //            if (tmp_player == player)
        //                player_t.push_back(std::make_pair("you", "true"));
        //
        //            players_t.add_child("", player_t);
        //            player_t.clear();
        //        }
        //
        //        root_t.push_back(std::make_pair("players", players_t));
        //        std::string slot_status;
        //        int slot_counter = 0;
        //
        //        BOOST_FOREACH(Slot* tmp_slot, player->table_slots())
        //        {
        //            switch (tmp_slot->status())
        //            {
        //            case Slot::Ok:
        //                slot_status = "ok";
        //                break;
        //            case Slot::Wait:
        //                slot_status = "wait";
        //                break;
        //            case Slot::Empty:
        //                slot_status = "empty";
        //                break;
        //            }
        //
        //            slot_t.push_back(std::make_pair("number", slot_counter++));
        //            slot_t.push_back(std::make_pair("status", slot_status));
        //
        //            BOOST_FOREACH(Card tmp_card, tmp_slot->cards())
        //            {
        //                cards_t.push_back(std::make_pair("", tmp_card.toString()));
        //            }
        //
        //            slot_t.push_back(std::make_pair("cards", cards_t));
        //            cards_t.clear();
        //
        //            slots_t.push_back(std::make_pair("", slot_t));
        //            slot_t.clear();
        //        }
        //        root_t.push_back(std::make_pair("slots", slots_t));
        //
        //        write_json("test.json", players_t);
        //

        std::string status, activity;
//        json_object * jobj = json_object_new_object();
//        json_object * jplayer = json_object_new_object();

        for (std::list<Player*>::iterator it = player->table_players().begin();
             it != player->table_players().end();
             ++it)
        {
            switch (player->status())
            {
            case Player::Active:
                status = "active";
                break;
            case Player::Passive:
                status = "passive";
                break;
            case Player::Neutral:
                status = "neutral";
                break;
            }

            switch (player->activity())
            {
            case Player::Enabled:
                activity = "enabled";
                break;
            case Player::Disabled:
                activity = "disabled";
                break;
                //            }
            }
        }

        /*Creating a json array*/
//        json_object *jstatus = json_object_new_string(status.data());
//        json_object *jactivity = json_object_new_string(activity.data());
//
//        json_object_object_add(jplayer, "status", jstatus);
//        json_object_object_add(jplayer, "activity", jactivity);
//
//        json_object_object_add(jobj, "players", jplayer);
//
//        for (std::list<Player*>::iterator it = player.table_players().begin();
//             it != player.table_players().end();
//             ++it)
//        {
//            
//        }
//
//
//        /*Creating json strings*/
//        json_object * jstring[3];
//        jstring[0] = json_object_new_string("c");
//        jstring[1] = json_object_new_string("c++");
//        jstring[2] = json_object_new_string("php");
//
//        /*Adding the above created json strings to the array*/
//        int i;
//        for (i = 0; i < 3; i++)
//        {
//            json_object_array_put_idx(jarray, i + 2, jstring[i]);
//        }
//
//        /*Form the json object*/
//        json_object_object_add(jobj, "Categories", jarray);
//
//        /*Now printing the json object*/
//        printf("The json object created: %sn", json_object_to_json_string(jobj));


        *responce = player->toString();
    }
}

void PlayerObject::method_post(std::vector<std::string> restful_data, std::string*, std::string*)
{
    GameController::instance()->addPlayerToTable(atoi(restful_data[0].data()), atoi(restful_data[1].data()));
}

void PlayerObject::method_put(std::vector<std::string>, std::string*, std::string*)
{
}

void PlayerObject::method_delete(std::vector<std::string>, std::string*, std::string*)
{
}

