#pragma once
#include "../state/state.hpp"
#include <queue>
#include <set>

/**
 * @brief Policy class for alphabeta policy, 
 * your policy class should have get_move method
 */

/// @brief Policy class for alphabeta policy, 
class Alphabeta
{
    public:
    static Move get_move(State *state, int depth);
};