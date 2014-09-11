/* 
 * File:   GameController.cpp
 * Author: alexey
 * 
 * Created on 31 Август 2014 г., 2:55
 */

#include "GameController.h"

#include <Table.h>

#include <iostream>

GameController* GameController::m_game_controller = 0;

GameController::GameController()
{
}

GameController::~GameController()
{
}

int GameController::addTable(cardsrv::Table* table)
{
    m_tables.insert(std::make_pair(table->id(), table));
    return table->id();
}

const cardsrv::Table* GameController::table(int id) const
{
    cardsrv::Table* ret_table = 0;
    //    std::map<int, cardsrv::Table*> m_tables;
    std::map<int, cardsrv::Table*>::const_iterator it;
    if ((it = m_tables.find(id)) != m_tables.end())
        ret_table = (*it).second;

    return ret_table;
}

cardsrv::Table* GameController::removeTable(int id)
{
    cardsrv::Table* ret_table = 0;

    std::map<int, cardsrv::Table*>::iterator it;

    if ((it = m_tables.find(id)) != m_tables.end())
    {
        ret_table = (*it).second;

        // todo: delete players!

        m_tables.erase(it);
    }

    return ret_table;
}

bool GameController::addPlayerToTable(int player_id, int table_id)
{
    cardsrv::Player *player = 0;

    if (!m_players.empty() && m_players.find(player_id) != m_players.end())
        return false;

    cardsrv::Table *table = 0;
    std::map<int, cardsrv::Table*>::iterator it;
    if ((it = m_tables.find(table_id)) != m_tables.end())
        table = (*it).second;

    if (table)
    {
        player = table->addPlayer(player_id);
        if (player)
            m_players.insert(std::make_pair(player_id, player));
    }

    return (bool)player;
}

const cardsrv::Player* GameController::const_player(int player_id) const
{
    return this->player(player_id);
}

cardsrv::Player* GameController::player(int player_id) const
{
    cardsrv::Player *player = 0;
    std::map<int, cardsrv::Player*>::const_iterator it;
    if ((it = m_players.find(player_id)) != m_players.end())
        player = (*it).second;

    return player;
}

cardsrv::Player* GameController::removePlayerFromTable(int player_id)
{
    cardsrv::Player *player = 0;
    std::map<int, cardsrv::Player*>::iterator it = m_players.find(player_id);
    if (it != m_players.end())
    {
        m_players.erase(it);
        player = (*it).second;
    }

    return player;
}


