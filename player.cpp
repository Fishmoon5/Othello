/*
 Othello
 Team: Yoji_nectar
 */

#include "player.hpp"

#define TEST_DEPTH 2
#define DEPTH 3
#define INF 1000000
#define ENDING 2000001

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    
    currBoard = new Board();
    searchDepth = DEPTH;
    this->us = side;
    this->oppo = (side == BLACK) ? WHITE : BLACK;
    bestMove = new Move(-1, -1);
    bestNext = new Move(-1, -1);
    expectedTime = 5.0;
}

/*
 * Destructor for the player.
 */
Player::~Player() {
	delete currBoard;
	delete bestMove;
    delete bestNext;
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

//    bool isEnd = (currBoard->empty <= DEPTH);
//    minimax(currBoard, DEPTH, us, isEnd);
//    int alpha = -INF;
//    int beta = INF;
//    absearch(currBoard, DEPTH, alpha, beta, us, isEnd);
    IDsearch();
//    adv_absearch(currBoard, TEST_DEPTH, alpha, beta, us, isEnd);

    if (bestMove->x == -1 || bestMove->y == -1) {
		return nullptr;
	}
	
    currBoard->doMove(bestMove, us);   
    Move* ans = new Move(bestMove->x, bestMove->y);
    return ans;
}


int Player::minimax(Board *board, int depth, Side side, bool isEnd) {
	if (depth == 0) {
		if (isEnd) {
			return (-1) * naiveScore(board, side);
		}
		else {
			return (-1) * dynamicScore(board, side);
		}
	}	
	
	int bestScore = -INF;
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
				score = minimax(newBoard, depth - 1, other, isEnd);
				delete newBoard;
				if (score > bestScore) {
					bestScore = score;
					if (depth == DEPTH) {
						bestMove->x = i;
						bestMove->y = j;
					}
				}
			}
		}
	}
	
	if (bestScore == -INF) {
		score = minimax(board, depth - 1, other, isEnd);
		if (score > bestScore) {
			bestScore = score;	
		}
	}
	
	return (-1) * bestScore;
}

int Player::absearch(Board *board, int depth, int alpha, int beta, Side side, bool isEnd) {
    if (difftime(time(NULL), begin) >= expectedTime)
        return ENDING;
    
    if (depth == 0) {
        if (isEnd) {
            return (-1) * naiveScore(board, side);
        }
        else {
            return (-1) * dynamicScore(board, side);
        }
    }
    
    int score = 0;
    Move move(-1, -1);
    Side other = (side == BLACK) ? WHITE : BLACK;
    
    bool moved = false;
    for (int j = 0; j < 8; ++j) {
        for (int i = 0; i < 8; ++i) {
            move.x = i;
            move.y = j;
            if (board->checkMove(&move, side)) {
                Board *newBoard = board->copy();
                newBoard->doMove(&move, side);
                score = absearch(newBoard, depth - 1, -beta, -alpha, other, isEnd);
                delete newBoard;


                if (score == ENDING)
                    return ENDING;

                moved = true;
                if (score > alpha) {
                    alpha = score;
//                    if (depth == searchDepth) {
  //                      bestNext->x = i;
    //                    bestNext->y = j;
      //              }
                }

                if (alpha >= beta) {
                    return (-1) * beta;
                }
            }
        }
    }
    
    if (!moved) {
        score = absearch(board, depth - 1, -beta, -alpha, other, isEnd);
        if (score == ENDING)
            return ENDING;

        if (score > alpha) {
            alpha = score;  
        }
        else if (score >= beta) {
            return (-1) * beta;
        }
    }
    
    return (-1) * alpha;
}


void Player::twosteps(Board *board, Side side, bool isEnd) {
    
    Move move1(-1, -1);
    int score = 0;
    Side other = (side == BLACK) ? WHITE : BLACK;

    for (int x1 = 0; x1 < 8; x1++) {
        for (int y1 = 0; y1 < 8; y1++) {
            move1.x = x1;
            move1.y = y1;
            if (board->checkMove(&move1, side)) {
                Board *newBoard1 = board->copy();
                newBoard1->doMove(&move1, side);
                score = minimax(newBoard1, 1, other, isEnd);

                TwoMoves t;
                t.first = move1;
                t.score = score;
                init.push_back(t);

                delete newBoard1;
            }
        }
    }
}

int Player::adv_absearch(Board *board, int depth, int alpha, int beta, Side side, bool isEnd) {
    init.clear();
    twosteps(currBoard, us, (currBoard->empty <= 2));
    sort(init.begin(), init.end());
    int score = 0;
    Side other = (side == BLACK) ? WHITE : BLACK;

    for (unsigned int i = 0; i < init.size(); i++) {
        Move move = init[i].first;
        
        Board *newBoard = board->copy();
        newBoard->doMove(&move, side);
        score = absearch(newBoard, depth-1, -beta, -alpha, other, isEnd);
        delete newBoard;

        if (score == ENDING)
            return ENDING;

        if (score > alpha) {
            alpha = score;
            bestNext->x = move.x;
            bestNext->y = move.y;
        }

        if (alpha >= beta) {
            return (-1) * beta;
        }
    }
    return (-1) * alpha;
}

void Player::IDsearch() {
    time(&begin);
    searchDepth = DEPTH;
    bestMove->x = -1;
    bestMove->y = -1;
    bestNext->x = -1;
    bestNext->y = -1;

    while(searchDepth <= 20) {
        expectedTime = 9.0;
        bool isEnd = (currBoard->empty <= searchDepth);
        int alpha = -INF;
        int beta = INF;

        int re = adv_absearch(currBoard, searchDepth, alpha, beta, us, isEnd);

        if (re == ENDING) {
            std::cerr << searchDepth << std::endl;
            break;
        }
        bestMove->x = bestNext->x;
        bestMove->y = bestNext->y;
        searchDepth++;
    }

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
			cB += int(board->get(BLACK, i, j)) * scoreMatrix[i*8 + j];
			cW += int(board->get(WHITE, i, j)) * scoreMatrix[i*8 + j];
		}
	}
		
	if (side == BLACK) {
		return cB - cW;
	}
	else {
		return cW - cB;
	}
}

int Player::dynamicScore(Board *board, Side side) {
	int bPiece = 0, wPiece = 0, bFront = 0, wFront = 0; 
	int bCorner = 0, wCorner = 0, bClose = 0, wClose = 0, bMob, wMob;
	int i, j, k, x, y;
	double raw = 0, piece, front, corner, close, mob, score;
	
	int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
	
	// pieces and frontier disks
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			if (board->occupied(i, j)) {
				if (board->get(BLACK, i, j)) {
					raw += scoreMatrix2[i*8 + j];
					bPiece++;
				} else {
					raw -= scoreMatrix2[i*8 + j];
					wPiece++;
				}
				
				for (k = 0; k < 8; k++) {
					x = i + dx[k];
					y = j + dy[k];
					if (board->onBoard(x, y) && !board->occupied(x, y)) {
						if (board->get(BLACK, i, j)) {
							bFront++;
						} else {
							wFront++;
						}
						break;
					}
				}
			}
		}
	}
	
	if (bPiece > wPiece) {
		piece = (100.0 * bPiece) / (bPiece + wPiece);
	}
	else if (bPiece < wPiece) {
		piece = -(100.0 * wPiece) / (bPiece + wPiece);
	}
	else piece = 0;
	
	if (bFront > wFront)
		front = -(100.0 * bFront)/(bFront + wFront);
	else if(bFront < wFront)
		front = (100.0 * wFront)/(bFront + wFront);
	else front = 0;
	
	// corners
	if(board->get(BLACK, 0, 0)) bCorner++;
	else if(board->get(WHITE, 0, 0)) wCorner++;
	if(board->get(BLACK, 0, 7)) bCorner++;
	else if(board->get(WHITE, 0, 7)) wCorner++;
	if(board->get(BLACK, 7, 0)) bCorner++;
	else if(board->get(WHITE, 7, 0)) wCorner++;
	if(board->get(BLACK, 7, 7)) bCorner++;
	else if(board->get(WHITE, 7, 7)) wCorner++;
	
	corner = 25 * (bCorner - wCorner);
	
	// squares close to corners
	if(!board->occupied(0, 0))   {
		if(board->get(BLACK, 0, 1)) bClose++;
		else if(board->get(WHITE, 0, 1)) wClose++;
		if(board->get(BLACK, 1, 1)) bClose++;
		else if(board->get(WHITE, 1, 1)) wClose++;
		if(board->get(BLACK, 1, 0)) bClose++;
		else if(board->get(WHITE, 1, 0)) wClose++;
	}
	if(!board->occupied(0, 7))   {
		if(board->get(BLACK, 0, 6)) bClose++;
		else if(board->get(WHITE, 0, 6)) wClose++;
		if(board->get(BLACK, 1, 6)) bClose++;
		else if(board->get(WHITE, 1, 6)) wClose++;
		if(board->get(BLACK, 1, 7)) bClose++;
		else if(board->get(WHITE, 1, 7)) wClose++;
	}
	if(!board->occupied(7, 0))   {
		if(board->get(BLACK, 7, 1)) bClose++;
		else if(board->get(WHITE, 7, 1)) wClose++;
		if(board->get(BLACK, 6, 1)) bClose++;
		else if(board->get(WHITE, 6, 1)) wClose++;
		if(board->get(BLACK, 6, 0)) bClose++;
		else if(board->get(WHITE, 6, 0)) wClose++;
	}
	if(!board->occupied(7, 7))   {
		if(board->get(BLACK, 7, 6)) bClose++;
		else if(board->get(WHITE, 7, 6)) wClose++;
		if(board->get(BLACK, 6, 6)) bClose++;
		else if(board->get(WHITE, 6, 6)) wClose++;
		if(board->get(BLACK, 6, 7)) bClose++;
		else if(board->get(WHITE, 6, 7)) wClose++;
	}
	
	close = -12.5 * (bClose - wClose);
	
	// mobility
	bMob = board->numMoves(BLACK);
	wMob = board->numMoves(WHITE);
	if (bMob > wMob) {
		mob = (100.0 * bMob) / (bMob + wMob);
	}
	else if (bMob < wMob) {
		mob = -(100.0 * wMob) / (bMob + wMob);
	}
	else {
		mob = 0;
	}
	
	score = (10 * raw) + (10 * piece) + (74.396 * front) 
			+ (801.724 * corner) + (382.026 * close) + (78.922 * mob);
	if (side == BLACK) {
		return score;
	}
	else {
		return -score;
	}
}
