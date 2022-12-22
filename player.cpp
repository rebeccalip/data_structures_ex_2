#include <iostream>
#include "player.h"

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper, int num_of_team_games_before):
 player_id(playerId), team_id(teamId), games_played(gamesPlayed), cards(cards), goal_keaper(goalKeeper),
        num_of_team_games_before(num_of_team_games_before), spirit(spirit), ability(ability)
{};

    


int Player::getPlayerId() const
{
    return player_id;
}


int Player::getNumGamesPlayed() const
{
    return games_played;
}

int Player::getNumCards() const
{
    return cards;
}
bool Player::getIsGoalKeeper() const
{
    return goal_keaper;
}

int Player::getNumGamesPlayedBefore() const
{
    return num_of_team_games_before;
}
void Player::setNumOfTeamGamesBefore(int num_games)
{
    num_of_team_games_before = num_games;
}



void Player::uptadeCards(const int extraCards)
{
    cards+=extraCards;
}

void Player::uptadeGamesPlayed(const int extraGamesPlayed)
{
    games_played+=extraGamesPlayed;
}

int Player::abs(const int a)
{
    if(a>0)
        return (a);
    return (-a);
}



