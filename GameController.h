/* 
 * File:   GameController.h
 * Author: alexey
 *
 * Created on 31 Август 2014 г., 2:55
 */

#ifndef GAMECONTROLLER_H
#define	GAMECONTROLLER_H

namespace cardsrv {
    class Player;
    class Table;
}

#include <map>

class GameController {
    std::map <int, cardsrv::Table*> m_tables;
    std::map <int, cardsrv::Player*> m_players;
    GameController();
    static GameController* m_game_controller;
public:

    static GameController* instance() {
        if (!m_game_controller)
            m_game_controller = new GameController;
        return m_game_controller;
    }
    
    int addTable(cardsrv::Table*);
    const  cardsrv::Table* table(int id) const;
    cardsrv::Table* removeTable(int id);
    
    bool addPlayerToTable(int player_id, int table_id);
    const cardsrv::Player* player(int player_id) const;
    cardsrv::Player* removePlayerFromTable(int id);

    virtual ~GameController();
private:

};

#endif	/* GAMECONTROLLER_H */

