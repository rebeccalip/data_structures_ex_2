#include "oppositeTree.h"

OppNode::~OppNode()
{
    delete this->player;
}

OppNode* OppNode::find()
{
    /*
    returns the highest parent, and change all the node's parent in the
    path between the given node and the highest parent
    */

    permutation_t all_per = permutation_t::neutral();
    permutation_t part_per = permutation_t::neutral();
    permutation_t temp_per = permutation_t::neutral();
    OppNode* node = this;
    OppNode* temp_node = this;
    OppNode* root;
    int sum_all_rank_games=0, sum_part_rank_games=0, temp_rank_games=0;

    //first find the father
    while (node->getParent() != nullptr)
    {
        all_per = node->getPermutation()*all_per;
        sum_all_rank_games += node->getGames();
        node = node->getParent();
    } 
    root = node;
    part_per = all_per;
    sum_part_rank_games = sum_all_rank_games;
    node = this;

    //update all the needed data
    while (node->getParent() != nullptr)
    {
        temp_node = node->getParent();
        node->SetParent(root);
        temp_per = node->getPermutation()*temp_per;
        temp_rank_games += node->getGames();
        node->setPermutation(part_per);
        node->setGames(sum_part_rank_games);
        part_per = temp_per.inv()*part_per;
        sum_all_rank_games -= temp_rank_games;
        node = temp_node;
        
    } 
    return root;     
}

OppNode* oppUnion(OppNode* firstHead, int firstSize, OppNode* secondHead, int secondSize, bool FirstBuySecond)
{
    /*
    *@FirstBuySecond - first team buys the second team
    //TODO: think if the data the union tree points to is also a parameter to the function

    */

   // 1 of 4 case
   if(FirstBuySecond && firstSize >= secondSize)
   {
        secondHead->SetParent(firstHead);
        secondHead->setPermutation(firstHead->getPermutation().inv()*firstHead->getTeam()->getTeamsSpirit());
        //firstHead->setPermutation(permutation_t::neutral());
        
        //games
        secondHead->setGames(secondHead->getGames() - firstHead->getGames());

        //team
        secondHead->setTeam(nullptr);

        return firstHead;

        // try to do give null or defalut value to the second head data
        
   }
   // 2 of 4 case
   else if(!FirstBuySecond && secondSize >= firstSize)
   {
        firstHead->SetParent(secondHead);
        firstHead->setPermutation(secondHead->getTeam()->getTeamsSpirit()*permutation_t::neutral());
        secondHead->setPermutation(permutation_t::neutral());

        //games
       firstHead->setGames(firstHead->getGames() - secondHead->getGames());

       //team
       firstHead->setTeam(nullptr);

       return secondHead;
   }
   // 3 of 4 case
   else if(FirstBuySecond && secondSize > firstSize)
   {
        firstHead->SetParent(secondHead);
        secondHead->setPermutation(firstHead->getTeam()->getTeamsSpirit()*permutation_t::neutral());
        firstHead->setPermutation(firstHead->getTeam()->getTeamsSpirit().inv());
        
        //games
        firstHead->setGames(firstHead->getGames() - secondHead->getGames());

        //teams
        secondHead->setTeam(firstHead->getTeam());
        firstHead->getTeam()->setFirstPlayer(secondHead);
        firstHead->setTeam(nullptr);

        return secondHead;
   }
   // 4 of 4 case - first bigger than second and second buys first
   else
   {
        secondHead->SetParent(firstHead);
        firstHead->setPermutation(secondHead->getTeam()->getTeamsSpirit()*permutation_t::neutral());
        secondHead->setPermutation(secondHead->getTeam()->getTeamsSpirit().inv());

        //games
        secondHead->setGames(secondHead->getGames() - firstHead->getGames());

        //teams
        firstHead->setTeam(secondHead->getTeam());
        secondHead->getTeam()->setFirstPlayer(firstHead);
        secondHead->setTeam(nullptr);

        return firstHead;
   }
   
}
