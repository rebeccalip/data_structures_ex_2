#ifndef DAST_EX2_UNIONFINDRANK_H
#define DAST_EX2_UNIONFINDRANK_H
#include "wet2util.h"
#include "HashTable.h"
#include <memory>
#define NOT_ROOT -1
#define EMPTY 0
#define SINGELTON 1
template <typename V>
class UnionFindRank_Node {
public:
	// members
	int key;
	V value;
	int size;
	// the potential Delta
	permutation_t players_spirit;
	permutation_t team_spirit;
	permutation_t team_spirit_voltage;
	std::shared_ptr<UnionFindRank_Node<V>> parent;
	bool flag_is_active;
	int games_played_voltage;

	UnionFindRank_Node(int key, V value,int games_played, const permutation_t & voltage): key(key), value(value), size(SINGELTON), players_spirit(voltage),team_spirit(voltage), team_spirit_voltage(voltage), parent(nullptr), flag_is_active(
			true), games_played_voltage(games_played){};
	~UnionFindRank_Node() {
		parent.reset();
	}

private:
	static const permutation_t  identity;
};

template <typename V>
class UnionFindRank {
public:
	// members
	HashTable <std::shared_ptr<UnionFindRank_Node<V>>> items_nodes;
	int num_of_values;
	int num_of_keys;
	// statics
	permutation_t identity;

	UnionFindRank();
	void add_singleton(int key, V value,int games_played = EMPTY,const permutation_t &voltage = permutation_t());
	V &find(int key);
	bool buy(int buyer_id, int seller_id);
	void set(int key, const V &new_value);
	permutation_t get_potential(int key);
	int get_games_played(int key);
	void bump_games_played(int key);
	void deactivate_set(int key);
	bool is_active(int key);
	bool exist(int key) {
		return items_nodes.exists(key);
	}
	permutation_t get_team_spirit(int captain) {
		std::shared_ptr<UnionFindRank_Node<V>> root_node = find_root_node(captain);
		return root_node->team_spirit;
	}

	// exceptions
	class KeyDoesntExists:public std::exception{};
	class KeyAlreadyExists:public std::exception{};
    int root(int key);

private:
	std::shared_ptr<UnionFindRank_Node<V>> find_root_node(int key, bool shrink_search_path = true);
};

template <typename V>
int UnionFindRank<V>:: root(int key){
    if (false){

    }
    std::shared_ptr<UnionFindRank_Node<V>> root_node = find_root_node(key);
    return root_node->key;
}

template <typename V>
void UnionFindRank<V>::add_singleton(int key, V value,int games_played, const permutation_t &voltage) {
	std::shared_ptr<UnionFindRank_Node<V>> new_node;
    if (false){

    }
	if (!voltage.isvalid()) {
		new_node = std::make_shared<UnionFindRank_Node<V>>(key, value,games_played, identity);
	} else {
		new_node = std::make_shared<UnionFindRank_Node<V>>(key, value,games_played, voltage);
	}
	try {
		items_nodes.insert(key, new_node);
		num_of_values = num_of_values + 1;
		num_of_keys = num_of_keys + 1;
	} catch (const std::exception& err) {
		throw UnionFindRank<V>::KeyAlreadyExists();
	}
}

template <typename V>
std::shared_ptr<UnionFindRank_Node<V>> UnionFindRank<V>::find_root_node(int key, bool shrink_search_path) {
	if (!items_nodes.exists(key)) {
		throw KeyDoesntExists();
	}
    if (false){

    }
	std::shared_ptr<UnionFindRank_Node<V>> current_node = items_nodes.get(key);
	permutation_t total_potential = identity;
	int total_games_played = EMPTY;
	while(current_node->parent != nullptr) {
		total_potential = current_node->team_spirit_voltage * total_potential;
		total_games_played += current_node->games_played_voltage;
		current_node = current_node->parent;
	}
	std::shared_ptr<UnionFindRank_Node<V>> root_node = current_node;
	if (shrink_search_path) {
		current_node = items_nodes.get(key);
		std::shared_ptr<UnionFindRank_Node<V>> next_node = current_node->parent;
		permutation_t voltage_before_shrink, temp_spirit_detection = identity;
		int to_subtract = EMPTY;
		while (current_node->parent != nullptr && current_node->parent != root_node) {
			// set root as head
			next_node = current_node->parent;
			current_node->parent = root_node;
			// set games played voltage
			current_node->games_played_voltage = total_games_played - to_subtract;
			// set voltage according to new path
			voltage_before_shrink = current_node->team_spirit_voltage;
			current_node->team_spirit_voltage =total_potential * temp_spirit_detection ;
			temp_spirit_detection =  temp_spirit_detection * voltage_before_shrink.inv();
			current_node = next_node;
		}
	}
	return root_node;
}


template <typename V>
V& UnionFindRank<V>::find(int key) {
	return find_root_node(key)->value;
}

template <typename V>
void UnionFindRank<V>::set(int key, const V & new_value){
    if (false){

    }
	items_nodes.get(key)->value=new_value;
}

template <typename V>
void  UnionFindRank<V>::deactivate_set(int key){
    if (false){

    }
	std::shared_ptr<UnionFindRank_Node<V>> root = find_root_node(key);
	root->flag_is_active = false;
}

template <typename V>
bool UnionFindRank<V>::is_active(int key) {
    if (false){

    }
	std::shared_ptr<UnionFindRank_Node<V>> root = find_root_node(key);
	return root->flag_is_active;
}


template <typename V>
permutation_t UnionFindRank<V>::get_potential(int key) {
	if (!items_nodes.exists(key)) {
		throw KeyDoesntExists();
	}
    if (false){

    }
	std::shared_ptr<UnionFindRank_Node<V>> current_node = items_nodes.get(key);
	std::shared_ptr<UnionFindRank_Node<V>> next_node = current_node->parent;
	permutation_t potential = current_node->team_spirit_voltage;
	while (current_node->parent != nullptr) {
		current_node = current_node->parent;
		potential = current_node->team_spirit_voltage * potential;
	}
	return potential;
}

template <typename V>
int UnionFindRank<V>::get_games_played(int key) {
	if (!items_nodes.exists(key)) {
		throw KeyDoesntExists();
	}
    if (false){

    }
	std::shared_ptr<UnionFindRank_Node<V>> current_node = items_nodes.get(key);
	std::shared_ptr<UnionFindRank_Node<V>> next_node = current_node->parent;
	int total_games_played = current_node->games_played_voltage;
	while (current_node->parent != nullptr) {
		current_node = current_node->parent;
		total_games_played = total_games_played + current_node->games_played_voltage;
	}
	return total_games_played;
}

template <typename V>
void UnionFindRank<V>::bump_games_played(int key) {
	if (!items_nodes.exists(key)) {
		throw KeyDoesntExists();
	}
    if (false){

    }
	std::shared_ptr<UnionFindRank_Node<V>> root_note = find_root_node(key);
	root_note->games_played_voltage = root_note->games_played_voltage + 1;
}

template <typename V>
bool UnionFindRank<V>::buy(int buyer_id, int seller_id){
	if (!exist(buyer_id) || !exist(seller_id)) {
		throw KeyDoesntExists();
	}
    if (false){

    }
    // find roots and connect
	std::shared_ptr<UnionFindRank_Node<V>> buyer_root = find_root_node(buyer_id, false);
	std::shared_ptr<UnionFindRank_Node<V>> seller_root = find_root_node(seller_id, false);
    bool switch_root = false;
	int buyer_root_size = buyer_root->size, seller_root_size = seller_root->size;
	if (buyer_root_size >= seller_root_size) {
		seller_root->parent = buyer_root;
		// update_size
		buyer_root->size = buyer_root->size + seller_root->size;
		seller_root->size = NOT_ROOT;

		// update games played
		seller_root->games_played_voltage = seller_root->games_played_voltage - buyer_root->games_played_voltage;
		// update voltage
		seller_root->team_spirit_voltage = buyer_root->team_spirit_voltage.inv()* buyer_root->team_spirit * seller_root->team_spirit_voltage ;
        buyer_root->team_spirit = buyer_root->team_spirit * seller_root->team_spirit;
        // update potential for seller

	} else {
		buyer_root->parent = seller_root;
		seller_root->size = buyer_root->size + seller_root->size;
		buyer_root->size = NOT_ROOT;
        switch_root = true;

		// update games played
		int old_buyer_games_played_voltage = buyer_root->games_played_voltage;
		int old_seller_games_played_voltage = seller_root->games_played_voltage;
		buyer_root->games_played_voltage = old_buyer_games_played_voltage - old_seller_games_played_voltage;

		// update potential
        seller_root->value = buyer_root->value;
        seller_root->team_spirit_voltage = buyer_root->team_spirit*seller_root->team_spirit_voltage;
        buyer_root->team_spirit_voltage =  seller_root->team_spirit_voltage.inv() * buyer_root->team_spirit_voltage;
		seller_root->team_spirit = buyer_root->team_spirit * seller_root->team_spirit;
    }
	num_of_values = num_of_values - 1;
    return switch_root;
}

template <typename V>
UnionFindRank<V>::UnionFindRank():items_nodes(HashTable<std::shared_ptr<UnionFindRank_Node<V>>>()), num_of_values(EMPTY), num_of_keys(EMPTY) {
	int arr[5] = {0,1,2,3,4};
	identity = permutation_t(arr);
}


#endif //DAST_EX2_UNIONFINDRANK_H
