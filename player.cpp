/*
 Othello
 Team: Yoji_nectar
 */

#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    
    currBoard = new Board();
    this->us = side;
    this->oppo = (side == BLACK) ? WHITE : BLACK;
    bestMove = new Move(-1, -1);
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete currBoard;
	delete bestMove;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    currBoard->doMove(opponentsMove, oppo);
    
    bestMove->x = -1;
    bestMove->y = -1;
    searchDepth = (testingMinimax) ? 2 : 6;

    minimax(currBoard, searchDepth, us);
    
    if (bestMove->x == -1 || bestMove->y == -1) {
		return nullptr;
	}
	
    currBoard->doMove(bestMove, us);   
    Move* ans = new Move(bestMove->x, bestMove->y);
    return ans;
}


int Player::minimax(Board *board, int depth, Side side) {
	if (depth == 0) {
		if (testingMinimax) {
			return (-1) * naiveScore(board, side);
		}
		else {
			return (-1) * betterScore(board, side);
		}
	}	
	
	int bestScore = -10000;
	int score = 0;
	Move move(-1, -1);
	Side other = (side == BLACK) ? WHITE : BLACK;
	
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			move.x = i;
			move.y = j;
			if (board->checkMove(&move, side)) {
				Board *newBoard = board->copy();
				newBoard->doMove(&move, side);
				score = minimax(newBoard, depth - 1, other);
				delete newBoard;
				if (score > bestScore) {
					bestScore = score;
					if (depth == searchDepth) {
						bestMove->x = i;
						bestMove->y = j;
					}
				}
			}
		}
	}
	
	if (bestScore == -10000) {
		score = minimax(board, depth - 1, other);
		if (score > bestScore) {
			bestScore = score;	
		}
	}
	
	return (-1) * bestScore;
}

int Player::naiveScore(Board *board, Side side) {
	if (side == BLACK) {
		return board->count(BLACK) - board->count(WHITE);
	}
	else {
		return board->count(WHITE) - board->count(BLACK);
	}
}

int Player::betterScore(Board *board, Side side) {
	int cB = 0;
	int cW = 0;
	
	for (int i = 0; i < 8; i++)	{
		for (int j = 0; j < 8; j++) {
			cB += int(board->get(BLACK, i, j)) * score_matrix[i*8 + j];
			cW += int(board->get(WHITE, i, j)) * score_matrix[i*8 + j];
		}
	}
		
	if (side == BLACK) {
		return cB - cW;
	}
	else {
		return cW - cB;
	}
}
