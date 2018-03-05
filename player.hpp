#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int minimax(Board *board, int depth, Side side);
    int naiveScore(Board *board, Side side);
    int betterScore(Board *board, Side side);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Board *currBoard;

private:
	int searchDepth;
    Side us;
    Side oppo;
    Move *bestMove;
    
    int score_matrix[64] = {
	 99,  -8,  8,  6,  6,  8,  -8,  99,
	 -8, -24, -4, -3, -3, -4, -24,  -8,
	  8,  -4,  7,  4,  4,  7,  -4,   8,
	  6,  -3,  4,  0,  0,  4,  -3,   6,
	  6,  -3,  4,  0,  0,  4,  -3,   6,
	  8,  -4,  7,  4,  4,  7,  -4,   8,
	 -8, -24, -4, -3, -3, -4, -24,  -8,
	 99,  -8,  8,  6,  6,  8,  -8,  99,
    };
};

#endif
