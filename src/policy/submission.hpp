#pragma once
#include "../state/state.hpp"
#include <queue>
#include <set>

/**
 * @brief Policy class for minimax policy, 
 * your policy class should have get_move method
 */

class Submission
{
    public:
    static Move get_move(State *state, int depth);
};

int submission(State* root, int depth, int alpha, int beta, int op, int selfplayer);