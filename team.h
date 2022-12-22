#ifndef TEAM_H_
#define TEAM_H_

#include "player.h"
#include <iostream>
#include <memory>

class Team;

class Team
{

private:
    int team_id;
    int points;
    int num_of_players;
    int num_of_games;
    int sum_of_player_abilities;
    int num_of_goal_keepers;
    permutation_t team_spirit;
    bool is_in_game;

    //void updatePlayersTeamHelper(AvlTree<std::shared_ptr<class Player>,int>::Node* node, Team* team);

public:

    friend class world_cup_t;
    friend class Player;
    Team(int teamId, int points);
    Team(const Team& other_team);
    ~Team() = default;
    bool isEmpty();
    bool isLegal();

    int getTeamId() const;
    int getPoints() const;
    int getNumPlayers() const;
    int getNumCards() const;
    int getNumGames() const;

    void updatePoints(const int extra);
    void updateGamesPlayed(const int extra);

    void addPlayerToTeam(std::shared_ptr<class Player> player);

    void updatePlayersTeam(Team* team);
};





#endif //TEAM_H_