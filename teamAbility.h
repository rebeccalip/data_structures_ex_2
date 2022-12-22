#ifndef TEAMABILITY_H_
#define TEAMABILITY_H_

class TeamAbility
{
private:
    int team_ability;
    int team_id;

    friend bool operator<(const TeamAbility& ability1,const TeamAbility& ability2);
    friend bool operator==(const TeamAbility& ability1,const TeamAbility& ability2);

public:
    TeamAbility() = default;
    explicit TeamAbility(int team_ability, int team_id);
    TeamAbility& operator=(const TeamAbility&) = default;
    ~TeamAbility() = default;
    void updateTeamAbility(int extra);

    int getTeamId() ;
    int getTeamAbility();

    
};

bool operator<(const TeamAbility& ability1 ,const TeamAbility& ability2);
bool operator>(const TeamAbility& ability1 ,const TeamAbility& ability2);
bool operator==(const TeamAbility& ability1 ,const TeamAbility& ability2);




#endif 