#include "worldcup23a2.h"

world_cup_t::world_cup_t()
{
	num_of_teams = 0;
}

world_cup_t::~world_cup_t()
{
	
}

StatusType world_cup_t::add_team(int teamId)
{
	if (teamId <= 0)
		return StatusType::INVALID_INPUT;
	if (teams_tree_id.find(teamId) != nullptr)
		return StatusType::FAILURE;

	std::shared_ptr<Team> new_team;
	try 
	{
		new_team= std::make_shared<class Team>(teamId); 
	}
	catch (const std::bad_alloc&)
	{
		return StatusType::ALLOCATION_ERROR;
	}
	try
	{
		teams_tree_id.insert(teamId, new_team);
		teams_ability_tree.insert(new_team->getTeamsAbility(), new_team);
	}
	catch(const std::bad_alloc& )
	{
		return StatusType::ALLOCATION_ERROR;
	}
	catch(const InvalidKey&)
	{
		return StatusType::FAILURE;
	}
	num_of_teams++;
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	if (teamId <= 0)
		return StatusType::INVALID_INPUT;
	if (teams_tree_id.find(teamId) == nullptr)
		return StatusType::FAILURE;
	std::shared_ptr<Team> team = teams_tree_id.find(teamId)->getValue();
	TeamAbility teams_ability = team->getTeamsAbility();
	std::shared_ptr<Team> null_team = nullptr;
	if(team->getFirstPlayer() != nullptr)
		team->getFirstPlayer()->setTeam(null_team);
	teams_tree_id.remove(teamId);
	teams_ability_tree.remove(teams_ability);
	num_of_teams--;
	return StatusType::SUCCESS;
	
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{

	if(playerId <= 0 || teamId <= 0 || !spirit.isvalid() || gamesPlayed < 0 || cards < 0)
		return StatusType::INVALID_INPUT;
	if(player_hash_table.isInTable(playerId))
		return StatusType::FAILURE;
	if(teams_tree_id.find(teamId) == nullptr)
		return StatusType::FAILURE;

	int teamGamesUntilNow = teams_tree_id.find(teamId)->getValue()->getNumGames();
	const permutation_t& teamSpirit = teams_tree_id.find(teamId)->getValue()->getTeamsSpirit();
	std::shared_ptr<Player> newPlayer(new Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper, teamGamesUntilNow, teamSpirit));

	OppNode* playerOppNode = new OppNode(nullptr, newPlayer);
	OppNode* teamsFirstPlayer = teams_tree_id.find(teamId)->getValue()->getFirstPlayer();
	if(teamsFirstPlayer == nullptr)
	{
		teams_tree_id.find(teamId)->getValue()->setFirstPlayer(playerOppNode);
		playerOppNode->setTeam(teams_tree_id.find(teamId)->getValue());
		
	}
	else
	{
		playerOppNode->SetParent(teamsFirstPlayer);
	}

	player_hash_table.insert(playerId, playerOppNode);
	// init games and permutation
	playerOppNode->setGames(0);
	playerOppNode->setPermutation(permutation_t::neutral());
	
	//update team stats
	std::shared_ptr<Team> playerTeam = teams_tree_id.find(teamId)->getValue();
	teams_ability_tree.remove(playerTeam->getTeamsAbility());
	
	playerTeam->updateNumOfPlayers(1);
	playerTeam->updateSumOfPlayersAbilities(ability);
	if(goalKeeper)
		playerTeam->updateNumOfGoalkeepers(1);
	playerTeam->updateTeamSpirit(spirit);
	playerTeam->updateTeamAbility(ability);

	teams_ability_tree.insert(playerTeam->getTeamsAbility(), playerTeam);
	
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	if (teamId1<=0 || teamId2<=0 || teamId1==teamId2)
		return StatusType::INVALID_INPUT;
	if (teams_tree_id.find(teamId1)== nullptr || teams_tree_id.find(teamId2)==nullptr)
		return StatusType::FAILURE;

	std::shared_ptr<Team> team1 = teams_tree_id.find(teamId1)->getValue();
	std::shared_ptr<Team> team2 = teams_tree_id.find(teamId2)->getValue();

	if(!team1->isLegal() || !team2->isLegal())
		return StatusType::FAILURE;
	
	team1->updateGamesPlayed(1);
	team2->updateGamesPlayed(1);
	team1->getFirstPlayer()->setGames(team1->getFirstPlayer()->getGames()+1);
	team1->getFirstPlayer()->setGames(team2->getFirstPlayer()->getGames()+1);
	
	int team1total = team1->getPoints() + team1->getPlayersAbilities();
	int team2total = team2->getPoints() + team2->getPlayersAbilities();

	if (team1total > team2total)
	{
		team1->updatePoints(3);
		return	output_t<int>(1);
	}
	if (team1total < team2total)
	{
		team2->updatePoints(3);
		return output_t<int>(3);
	}
		
	int team1spirit_strength = team1->getTeamsSpirit().strength();
	int team2spirit_strength = team2->getTeamsSpirit().strength();

	if(team1spirit_strength > team2spirit_strength)
	{
		team1->updatePoints(3);
		return	output_t<int>(2);
	}
	if(team1spirit_strength > team2spirit_strength)
	{
		team2->updatePoints(3);
		return output_t<int>(4);
	}
	team1->updatePoints(1);
	team2->updatePoints(1);
	return	output_t<int>(0);

}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	if(playerId<=0)
		return StatusType::INVALID_INPUT;
	if (!player_hash_table.isInTable(playerId))
		return StatusType::FAILURE;

	OppNode* node = player_hash_table.get(playerId);
	std::shared_ptr<Player> player = node->getPlayer();
	int sum_games = player->getNumGamesPlayed() - player->getNumGamesPlayedBefore();
	while (node != nullptr)
	{
		sum_games += node->getGames();
		node=node->getParent();
	}
	
	return output_t<int>(sum_games);
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	if(playerId<=0 || cards<0)
		return StatusType::INVALID_INPUT;
	if (!player_hash_table.isInTable(playerId))
		return StatusType::FAILURE;
	if (player_hash_table.get(playerId)->find()->getTeam() == nullptr)
		return StatusType::FAILURE;

	std::shared_ptr<Player> player = player_hash_table.get(playerId)->getPlayer();
	player->uptadeCards(cards);

	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	if(playerId<=0)
		return StatusType::INVALID_INPUT;
	if (!player_hash_table.isInTable(playerId))
		return StatusType::FAILURE;

	std::shared_ptr<Player> player = player_hash_table.get(playerId)->getPlayer();
	return output_t<int>(player->getNumCards());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	if (teamId <= 0)
		return StatusType::INVALID_INPUT;
	if (teams_tree_id.find(teamId) == nullptr)
		return StatusType::FAILURE;

	std::shared_ptr<Team> team = teams_tree_id.find(teamId)->getValue();
	return output_t<int>(team->getPoints());
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	if(i<0 || i>=num_of_teams)
		return StatusType::FAILURE;
	
	std::shared_ptr<Team> team = teams_ability_tree.select(i+1)->getValue();
	return output_t<int>(team->getTeamId());

}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	if(playerId<=0)
		return StatusType::INVALID_INPUT;
	if (!player_hash_table.isInTable(playerId))
		return StatusType::FAILURE;
	if (player_hash_table.get(playerId)->find()->getTeam() == nullptr)
		return StatusType::FAILURE;

	OppNode* node = player_hash_table.get(playerId);
	std::shared_ptr<Player> player = node->getPlayer();
	permutation_t per = player->get_spirit_before_him();
	while (node != nullptr)
	{
		per = per*node->getPermutation();
		node=node->getParent();
	}
	
	return output_t<permutation_t>(per);
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	if( teamId1<=0 || teamId2<=0 || teamId1==teamId2)
		return StatusType::INVALID_INPUT;
	if (teams_tree_id.find(teamId1)==nullptr || teams_tree_id.find(teamId2)==nullptr)
		return StatusType::FAILURE;

	std::shared_ptr<Team> buyerTeam = teams_tree_id.find(teamId1)->getValue();
	std::shared_ptr<Team> boughtTeam = teams_tree_id.find(teamId2)->getValue();
	int sizeTeam1 = buyerTeam->getNumPlayers();
	int sizeTeam2 = boughtTeam->getNumPlayers();
	teams_ability_tree.remove(buyerTeam->getTeamsAbility());
	teams_ability_tree.remove(boughtTeam->getTeamsAbility());
	teams_tree_id.remove(teamId2);

	oppUnion(buyerTeam->getFirstPlayer(), sizeTeam1, boughtTeam->getFirstPlayer(), sizeTeam2, true);

	buyerTeam->updatePoints(boughtTeam->getPoints());
	buyerTeam->updateNumOfPlayers(boughtTeam->getNumPlayers());
	buyerTeam->updateNumOfGoalkeepers(boughtTeam->getNumGoalKeepers());
	buyerTeam->updateSumOfPlayersAbilities(boughtTeam->getPlayersAbilities());
	buyerTeam->updateTeamSpirit(boughtTeam->getTeamsSpirit());
	buyerTeam->getTeamsAbility().setTeamAbility(buyerTeam->getPlayersAbilities());

	teams_ability_tree.insert(buyerTeam->getTeamsAbility(), buyerTeam);

	return StatusType::SUCCESS;
}