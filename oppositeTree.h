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
        Player* player;
        Team* team;
        permutation_t permutation;
        int games;
        // need to think if add and ID to oppNode
    
    public:
        OppNode() = default;
        OppNode(OppNode* otherParent, Player* player)
        {
            parent = otherParent;
            this->player = player;
            this->permutation = permutation_t::neutral();
            this->games = 0;
            this->team = nullptr;
        }
        OppNode(const OppNode& other) = default;
        ~OppNode();
        OppNode& operator=(const OppNode& other) = default; 

        // Getters and Setters
        Player* getPlayer() const { return this->player;};
        void setPlayer(Player* player) {this->player = player;};
        Team* getTeam() { return this->team;};
        void setTeam(Team* team) {this->team = team;};
        permutation_t getPermutation() const { return this->permutation;};
        void setPermutation(permutation_t permut) {this->permutation = permut;};
        int getGames() {return this->games;};
        void setGames(int games) {this->games = games;};
        OppNode* getParent() { return this->parent;};
        void SetParent(OppNode* parent) {this->parent = parent;};

        OppNode* find(); 
};

OppNode* oppUnion(OppNode* firstHead, int firstSize, OppNode* secondHead, int secondSize, bool FirstBuySecond);

#endif // OPPOSITETREE