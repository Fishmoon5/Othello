#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <time.h>
#include "common.hpp"
#include "board.hpp"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int minimax(Board *board, int depth, Side side, bool isEnd);
    int absearch(Board *board, int depth, int alpha, int beta, Side side, bool isEnd);
    void IDsearch(double timeAlloc);
    int naiveScore(Board *board, Side side);
    int betterScore(Board *board, Side side);
	int dynamicScore(Board *board, Side side);

    // Flag to tell if the player is running within the test_minimax context
    Board *currBoard;

private:
	int searchDepth;
    Side us;
    Side oppo;
    Move *bestMove;
    Move *bestNext;
    
    double timeFracEven;
    double timeFracOdd;
    time_t begin;
    double expectedTime;
    
    double allocation[60] = {
   0.0005, 0.01900, 0.01977, 0.02053, 0.02130, 0.02207, 0.02284,
		   0.02360, 0.02437, 0.02514, 0.02591, 0.02667, 0.02744,
		   0.02821, 0.02898, 0.02974, 0.03051, 0.03128, 0.03205,
		   0.03281, 0.03358, 0.03435, 0.03517, 0.03588, 0.03665,
		   0.03742, 0.03819, 0.03895, 0.03972, 0.04049, 0.04126,
		   0.04202, 0.04279, 0.04356, 0.04433, 0.04509, 0.04586,
		   0.04663, 0.04740, 0.04816, 0.04893, 0.04970, 0.05047,
		   0.05123, 0.05300, 0.04500, 0.04600, 0.05100, 0.04900,
		   0.05200, 0.02000, 0.01500, 0.01400, 0.00700, 0.00600,
		   0.00500, 0.00750, 0.00600, 0.01000, 0.00900};
		
    
    int scoreMatrix[64] = {
	 99,  -8,  8,  6,  6,  8,  -8,  99,
	 -8, -24, -4, -3, -3, -4, -24,  -8,
	  8,  -4,  7,  4,  4,  7,  -4,   8,
	  6,  -3,  4,  0,  0,  4,  -3,   6,
	  6,  -3,  4,  0,  0,  4,  -3,   6,
	  8,  -4,  7,  4,  4,  7,  -4,   8,
	 -8, -24, -4, -3, -3, -4, -24,  -8,
	 99,  -8,  8,  6,  6,  8,  -8,  99
    };
    
	int scoreMatrix2[64] = {
	 20, -3, 11,  8,  8, 11, -3, 20,
	 -3, -7, -4,  1,  1, -4, -7, -3,
	 11, -4,  2,  2,  2,  2, -4, 11,
	  8,  1,  2, -3, -3,  2,  1,  8,
	  8,  1,  2, -3, -3,  2,  1,  8,
	 11, -4,  2,  2,  2,  2, -4, 11,
	 -3, -7, -4,  1,  1, -4, -7, -3,
	 20, -3, 11,  8,  8, 11, -3, 20
    };
};

#endif
