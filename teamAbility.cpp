#include "teamAbility.h"

TeamAbility::TeamAbility(int team_ability, int team_id)
{
    team_ability = team_ability;
    team_id = team_id;
}

void TeamAbility::setTeamAbility(int extra)
{
    team_ability += extra ;
}

void TeamAbility::setTeamId(int id)
{
    team_id = id ;
}

int TeamAbility::getTeamId() 
{
    return team_id;
}
int TeamAbility::getTeamAbility()
{
    return team_ability;
}

bool operator<(const TeamAbility& ability1 ,const TeamAbility& ability2)
{
    if(ability1.team_ability < ability2.team_ability)
        return true;
    if(ability1.team_ability > ability2.team_ability)
        return false;
    if(ability1.team_id < ability2.team_id)
        return true;
    return false;

}

bool operator>(const TeamAbility& ability1 ,const TeamAbility& ability2)
{
    return ability2<ability1;
}

bool operator==(const TeamAbility& ability1 ,const TeamAbility& ability2)
{
    return (ability1.team_ability==ability2.team_ability && ability1.team_id==ability2.team_id);
}