#include <cstdlib>
#include <set>
#include <climits>

#include "../state/state.hpp"
#include "./alphabeta.hpp"

enum minimaxop
{
    MAXimize,
    MINimize,
};

/**
 * @brief get a legal action by submission
 * 
 * @param state Now state
 * @param depth You may need this for other policy
 * @return Move 
 */

int alphabeta(State* root, int depth, int alpha, int beta, int op, int selfplayer)
{
    if(root->player == selfplayer && root->game_state == WIN) return INT_MAX-1; 
    if(root->player != selfplayer && root->game_state == WIN) return -INT_MAX+1; 
    if(!root->legal_actions.size()) root->get_legal_actions();
    if(depth == 0 || !root->legal_actions.size())
    {
        return root->evaluate(selfplayer);
    }
    if(op == MAXimize)
    {
        int value = -INT_MAX+1; 
        for(auto move: root->legal_actions)
        {   
            value = std::max(value, alphabeta(root->next_state(move), depth-1, alpha, beta, MINimize, selfplayer));
            alpha = std::max(value, alpha);
            if(alpha >= beta) break;
        }        
        return value;
    }
    else //op == MINimize
    {
        int value = INT_MAX-1; 
        for(auto move: root->legal_actions)
        {
            value = std::min(value, alphabeta(root->next_state(move), depth-1, alpha, beta, MAXimize, selfplayer));
            beta = std::min(value, beta);
            if(alpha >= beta) break;
        }
       return value;
    }
}

Move Alphabeta::get_move(State* state, int depth)
{
    Move minimaxmove;
    int rootalpha = -INT_MAX; 
    //int rootbeta = INT_MAX; 

    if(!state->legal_actions.size()) state->get_legal_actions();

    for(auto move: state->legal_actions)
    {   
        int childvalue = alphabeta(state->next_state(move), depth-1, -INT_MAX+1, INT_MAX-1, MINimize, state->player);
        if(childvalue > rootalpha)
        {
            rootalpha = childvalue;
            minimaxmove = move;
        }
    }

    return minimaxmove;
}