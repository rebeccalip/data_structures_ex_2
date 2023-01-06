#ifndef TEAM_H_
#define TEAM_H_

#include "player.h"
#include "oppositeTree.h"
#include <iostream>
#include <memory>
#include "teamAbility.h"
#include "wet2util.h"

class Team;
class OppNode;


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
    //bool is_in_game;
    TeamAbility teams_ability;
    OppNode *firstPlayer; //problem

    //void updatePlayersTeamHelper(AvlTree<std::shared_ptr<class Player>,int>::Node* node, Team* team);

public:

    friend class world_cup_t;
    friend class Player;
    Team(int teamId);
    Team(const Team& other_team) = default;
    ~Team() = default;
    bool isEmpty();
    bool isLegal();

    OppNode* getFirstPlayer();
    void setFirstPlayer(OppNode* firstPlayer);
    int getTeamId() const;
    int getPoints() const;
    int getNumPlayers() const;
    int getNumGames() const;
    int getPlayersAbilities() const;
    permutation_t getTeamsSpirit() const;
    //bool IsInGame() const;
    TeamAbility getTeamsAbility() const;
    int getNumGoalKeepers() const;

    void updatePoints(const int extra);
    void updateGamesPlayed(const int extra);
    void updateNumOfPlayers(const int extra);
    void updateSumOfPlayersAbilities(int newPlayerAbility);
    void updateNumOfGoalkeepers(const int extra);
    void updateTeamSpirit(const permutation_t& newPlayerSpirit);
    void updateTeamAbility(int newPlayerAbility);


};





#endif //TEAM_H_