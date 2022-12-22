#include "team.h"
#include "player.h"

Team::Team(int teamId, int points1)
{
    team_id=teamId;
    points = points1;
    num_of_players=0;
    num_of_games=0;
    sum_of_cards=0;
    sum_of_goals=0;
    num_of_goal_keepers=0;
}

int Team::getTeamId() const
{
    return team_id;
}
int Team::getPoints() const
{
    return points;
}
int Team::getNumPlayers() const
{
    return num_of_players;
}
int Team::getNumGoals() const
{
    return sum_of_goals;
}
int Team::getNumCards() const
{
    return sum_of_cards;
}
int Team::getNumGames() const
{
    return num_of_games;
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
    return (num_of_players>=LEGAL_MINIMAL_PLAYERS) && (num_of_goal_keepers>0);
}

void Team::addPlayerToTeam(std::shared_ptr<class Player> player)
{
    teams_playres_id.insert(player->getPlayerId(), player);
    try
    {
        teams_playres_score.insert(player->getScore(), nullptr);
    }
    catch(const std::bad_alloc&)
    {
        teams_playres_id.remove(player->getPlayerId());
        throw;
    }
    num_of_players++;
    sum_of_cards += player->getNumCards();
    sum_of_goals += player->getNumGoals();
    if(player->getIsGoalKeeper())
        num_of_goal_keepers++;
    if (num_of_players==1 || teams_playres_score.getMaxKey() < player->getScore())
        best_player = player.get();
    player->setNumOfTeamGamesBefore(num_of_games);
}

void Team::removePlayerFromTeam(std::shared_ptr<class Player> player)
{
    num_of_players--;
    teams_playres_id.remove(player->getPlayerId());
    teams_playres_score.remove(player->getScore());
    if(best_player==player.get())
    {
        if(num_of_players==0)
            best_player=nullptr;
        else
            best_player=((teams_playres_score.getMaxValue())->getData()).get();
    }
    sum_of_cards -= player->getNumCards();
    sum_of_goals -= player->getNumGoals();

}

void Team::updatePlayersTeamHelper(AvlTree<std::shared_ptr<class Player>,int>::Node* node, Team* team)
{
    if(node==nullptr)
        return;
    updatePlayersTeamHelper(node->left, team);
    if (node->getValue() == nullptr)
        std::cout << "problemmmm" << std::endl;
    else
        node->getValue()->players_team = team;
    updatePlayersTeamHelper(node->right, team);
}

void Team::updatePlayersTeam(Team* team)
{
    updatePlayersTeamHelper(teams_playres_id.root , team);
}

