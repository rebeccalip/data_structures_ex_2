#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>
#include <memory>
#include "team.h"
#include "wet2util.h"

class Team;

class Player
{
private:
    int player_id;
    //int team_id;
    int games_played;
    int cards;
    bool goal_keaper;
    int num_of_team_games_before;
    permutation_t spirit;
    int ability;
    permutation_t spirit_before_him;


    int abs(const int a);

    friend class Team;

public:
    Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, 
        bool goalKeeper, int num_of_team_games_before, const permutation_t& teams_spirit);      
    ~Player() = default;

    int getPlayerId() const;
    int getNumGamesPlayed() const;
    int getNumGoals() const;
    int getNumCards() const;
    int getNumGamesPlayedBefore() const;
    bool getIsGoalKeeper() const;
    const permutation_t& get_spirit_before_him() const;

    void setNumOfTeamGamesBefore(int num_games);
    void uptadeGoals(const int extraGoals);
    void uptadeCards(const int extraCards);
    void uptadeGamesPlayed(const int extraGamesPlayed);

};





#endif // PLAYER_H_