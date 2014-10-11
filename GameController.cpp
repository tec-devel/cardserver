/* 
 * File:   GameController.cpp
 * Author: alexey
 * 
 * Created on 31 Август 2014 г., 2:55
 */

#include "GameController.h"

#include <AbstractTable.h>
#include <Table.h>

#include <iostream>

GameController* GameController::m_game_controller = 0;

GameController::GameController()
{
}

GameController::~GameController()
{
}

int GameController::addTable(cardsrv::AbstractTable* table)
{
    m_tables.insert(std::make_pair(table->id(), table));
    return table->id();
}

const cardsrv::AbstractTable* GameController::table(int id) const
{
    cardsrv::AbstractTable* ret_table = 0;
    //    std::map<int, cardsrv::Table*> m_tables;
    std::map<int, cardsrv::AbstractTable*>::const_iterator it;
    if ((it = m_tables.find(id)) != m_tables.end())
        ret_table = (*it).second;

    return ret_table;
}

std::map <int, cardsrv::AbstractTable*> GameController::tables() const
{
    return m_tables;
}

cardsrv::AbstractTable* GameController::removeTable(int id)
{
    cardsrv::AbstractTable* ret_table = 0;

    std::map<int, cardsrv::AbstractTable*>::iterator it;

    if ((it = m_tables.find(id)) != m_tables.end())
    {
        ret_table = (*it).second;

        // todo: delete players!


        for (std::list <cardsrv::AbstractPlayer*>::iterator player_it = ret_table->players().begin();
                player_it != ret_table->players().end();
                ++player_it)
        {
            std::map<int, cardsrv::AbstractPlayer*>::iterator map_it = m_players.find((*player_it)->id());
            if (map_it != m_players.end())
                m_players.erase(map_it);
        }

        m_tables.erase(it);
    }

    return ret_table;
}

bool GameController::addPlayerToTable(int player_id, int table_id)
{
    cardsrv::AbstractPlayer *player = 0;

    if (!m_players.empty() && m_players.find(player_id) != m_players.end())
        return false;

    cardsrv::AbstractTable *table = 0;
    std::map<int, cardsrv::AbstractTable*>::iterator it;
    if ((it = m_tables.find(table_id)) != m_tables.end())
        table = (*it).second;

    if (table && table->state() == cardsrv::AbstractTable::Waiting)
    {
        player = table->addPlayer(player_id);
        if (player)
            m_players.insert(std::make_pair(player_id, player));

        if (table->isFull())
            table->startGame();
    }

    return (bool)player;
}

const cardsrv::AbstractPlayer* GameController::const_player(int player_id) const
{
    return this->player(player_id);
}

cardsrv::AbstractPlayer* GameController::player(int player_id) const
{
    cardsrv::AbstractPlayer *player = 0;
    std::map<int, cardsrv::AbstractPlayer*>::const_iterator it;
    if ((it = m_players.find(player_id)) != m_players.end())
        player = (*it).second;

    return player;
}

cardsrv::AbstractPlayer* GameController::removePlayerFromTable(int player_id)
{
    cardsrv::AbstractPlayer *player = 0;
    std::map<int, cardsrv::AbstractPlayer*>::iterator it = m_players.find(player_id);
    if (it != m_players.end())
    {
        m_players.erase(it);
        player = (*it).second;
    }

    return player;
}


