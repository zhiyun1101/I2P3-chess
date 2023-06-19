#include <cstdlib>
#include <set>
#include <climits>

#include "../state/state.hpp"
#include "./minimax.hpp"

enum minimaxop
{
    MAXimize,
    MINimize,
};

/**
 * @brief get a legal action by minimax
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int minimax(State* root, int depth, int op, int selfplayer)
{
    if((root->player == selfplayer) && (root->game_state == WIN))
    {
       return INT_MAX; 
    }
    if((root->player != selfplayer) && (root->game_state == WIN))
    {
       return -INT_MAX; 
    }
    if(!root->legal_actions.size()) root->get_legal_actions();
    if(depth == 0 || !root->legal_actions.size())
    {
        return root->evaluate(selfplayer);
    }
    if(op == MAXimize)
    {
        int value = -INT_MAX; 
        for(auto move: root->legal_actions)
        {   
            value = std::max(value, minimax(root->next_state(move), depth-1, MINimize, selfplayer));
        }
        return value;
    }
    else //op == MINimize
    {
        int value = INT_MAX; 
        for(auto move: root->legal_actions)
        {
            value = std::min(value, minimax(root->next_state(move), depth-1, MAXimize, selfplayer));
        }
       return value;
    }
}

Move Minimax::get_move(State* state, int depth)
{
    Move minimaxmove;
    int rootvalue = -INT_MAX; 

    if(!state->legal_actions.size()) state->get_legal_actions();

    for(auto move: state->legal_actions)
    {   
        int childvalue = minimax(state->next_state(move), depth-1, MINimize, state->player);
        if(childvalue > rootvalue)
        {
            rootvalue = childvalue;
            minimaxmove = move;
        }
    }

    return minimaxmove;
}