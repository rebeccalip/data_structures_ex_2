#ifndef OPPOSITETREE_H_
#define OPPOSITETREE_H_

#include "player.h"
#include "team.h"
#include "wet2util.h"

class OppNode
{
    private:
        OppNode* parent;
        Player* player;
        Team* team;
        permutation_t permutation;
        int games;
        // need to think if add and ID to oppNode
    
    public:
        OppNode() = default;
        OppNode(OppNode* otherParent, Player* player) : parent(otherParent), player(player), permutation(permutation_t::neutral()), games(0){};
        OppNode(const OppNode& other) = default;
        ~OppNode() = default;
        OppNode& operator=(const OppNode& other) = default; 

        // Getters and Setters
        Player* getPlayer() const { return this->player};
        void setPlayer(Player* player) {this->player = player};
        Team* getTeam() const { return this->team};
        void setTeam(Team* team) {this->team = team};
        const permutation_t& getPermutation() const { return this->permutation};
        void setPermutation(const permutation_t& permut) {this->permutation = permut};
        int getGames() const {return this->games};
        void setGames(int games) {this->games = games};
        OppNode* getParent() const { return this->parent};
        void SetParent(OppNode* parent) {this->parent = parent};

        OppNode* find(); 
};


#endif // OPPOSITETREE