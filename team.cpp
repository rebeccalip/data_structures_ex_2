#include "team.h"
#include "player.h"

Team::Team(int teamId)
{
    team_id=teamId;
    points = 0;
    num_of_players=0;
    num_of_games=0;
    num_of_goal_keepers=0;
    teams_ability.setTeamId(team_id);
    //is_in_game = true;
    sum_of_player_abilities = 0;
    team_spirit = permutation_t::neutral();
}

int Team::getTeamId() const
{
    return team_id;
}
OppNode* Team::getFirstPlayer() const
{
    return this->firstPlayer;
}
void Team::setFirstPlayer(OppNode* firstPlayer)
{
    this->firstPlayer = firstPlayer;
}
int Team::getPoints() const
{
    return points;
}
int Team::getNumPlayers() const
{
    return num_of_players;
}
int Team::getNumGames() const
{
    return num_of_games;
}

int Team::getPlayersAbilities() const
{
    return sum_of_player_abilities;
}
permutation_t Team::getTeamsSpirit() const
{
    return team_spirit;
}

TeamAbility Team::getTeamsAbility() const
{
    return teams_ability;
}

void Team::updatePoints(const int extra)
{
    points += extra;
}
void Team::updateGamesPlayed(const int extra)
{
    num_of_games+=extra;
}

bool Team::isEmpty()
{
    return num_of_players==0;
}

bool Team::isLegal()
{
    return (num_of_goal_keepers>0);
}
void Team::updateNumOfPlayers(const int extra )
{
    this->num_of_players+=extra;
}
void Team::updateSumOfPlayersAbilities(int newPlayerAbility)
{
    this->sum_of_player_abilities += newPlayerAbility;
}
void Team::updateNumOfGoalkeepers(const int extra)
{
    this->num_of_goal_keepers+=extra;
}
void Team::updateTeamSpirit(const permutation_t& newPlayerSpirit)
{
    this->team_spirit = team_spirit * newPlayerSpirit;
}
void Team::updateTeamAbility(int newPlayerAbility)
{
    this->teams_ability.setTeamAbility(newPlayerAbility);
}

int Team::getNumGoalKeepers() const
{
    return num_of_goal_keepers;
}


