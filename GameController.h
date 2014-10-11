/* 
 * File:   GameController.h
 * Author: alexey
 *
 * Created on 31 Август 2014 г., 2:55
 */

#ifndef GAMECONTROLLER_H
#define	GAMECONTROLLER_H

namespace cardsrv {
    class AbstractPlayer;
    class AbstractTable;
}

#include <map>

class GameController {
    std::map <int, cardsrv::AbstractTable*> m_tables;
    std::map <int, cardsrv::AbstractPlayer*> m_players;
    GameController();
    static GameController* m_game_controller;
public:

    static GameController* instance() {
        if (!m_game_controller)
            m_game_controller = new GameController;
        return m_game_controller;
    }
    
    int addTable(cardsrv::AbstractTable*);
    const  cardsrv::AbstractTable* table(int id) const;
    cardsrv::AbstractTable* removeTable(int id);
    std::map <int, cardsrv::AbstractTable*> tables() const;
    
    bool addPlayerToTable(int player_id, int table_id);
    const cardsrv::AbstractPlayer* const_player(int player_id) const;
    cardsrv::AbstractPlayer* player(int player_id) const;
    cardsrv::AbstractPlayer* removePlayerFromTable(int id);

    virtual ~GameController();
private:

};

#endif	/* GAMECONTROLLER_H */

