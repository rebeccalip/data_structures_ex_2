#ifndef OPPOSITETREE_H_
#define OPPOSITETREE_H_

#include "player.h"
#include "team.h"
#include "wet2util.h"
#include <memory>

class Team;
class Player;

class OppNode
{
    private:
        OppNode* parent;
        std::shared_ptr<Player> player;
        std::shared_ptr<Team> team;
        permutation_t permutation;
        int games;
        // need to think if add and ID to oppNode
    
    public:
        OppNode() = default;
        OppNode(OppNode* otherParent, std::shared_ptr<Player>& player) : parent(otherParent), player(player), permutation(permutation_t::neutral()), games(0){};
        OppNode(const OppNode& other) = default;
        ~OppNode() = default;
        OppNode& operator=(const OppNode& other) = default; 

        // Getters and Setters
        const std::shared_ptr<Player>& getPlayer() const { return this->player;};
        void setPlayer(std::shared_ptr<Player>& player) {this->player = player;};
        const std::shared_ptr<Team>& getTeam() const { return this->team;};
        void setTeam(const std::shared_ptr<Team>& team) {this->team = team;};
        const permutation_t& getPermutation() const { return this->permutation;};
        void setPermutation(const permutation_t& permut) {this->permutation = permut;};
        int getGames() const {return this->games;};
        void setGames(int games) {this->games = games;};
        OppNode* getParent() const { return this->parent;};
        void SetParent(OppNode* parent) {this->parent = parent;};

        OppNode* find(); 
};

OppNode* oppUnion(OppNode* firstHead, int firstSize, OppNode* secondHead, int secondSize, bool FirstBuySecond);

#endif // OPPOSITETREE