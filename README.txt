- How and what each group member contributed to the project:

Jing Ding: Implemented minimax, improved the heuristic function, wrote a function to decide time allocation to each move, and read papers for ideas.

Shuyue Yu: Implemented alpha-beta pruning, implemented Interactive Deepening, wrote a function to decide the order of moves we will use to search, and wrote up a testing program.


- Improvements that our group has made:

Heuristic function: In early and middle games, we used a revised evaluation function that calculates the utility of a position by: 1) assigning different weights to all positions on the board,
	2) taking into account number of pieces, 3) quantifying  frontier disks and mobility, and 4) analyzing corner positions.

Alpha-beta pruning: Through testing, we find that alpha-beta greatly increases the speed of calculation. Our bot can go into deeper levels in the same amount of time. 
	Precisely, our program is able to look ahead ~10 steps in early game, 9-12 steps in middle game, and 14-16 steps in the ending.

Interactive Deepening: Our bot used to end the game with a large amount of time remaining. Thus, we use Interactive Deepening to make sure that the bot uses the given time fully and efficiently.

Time allocation: We refered to some allocation strategy available on internet and manually gave a time allocation table that our program will obey during the game. 
	In particular, we allocate more time (11-14 secs per move) to middle game calculations, less time (6-10 secs per move) to openings, and even less (whatever time remaining) to endgames. 
	(Normally the calculation for the last 10~14 moves take less than 5 seconds.)

Move sorting: Sometimes the branch we will cut in the alpha-beta pruning is searched at the end, in which case the alpha-beta pruning has little effect. 
	Thus, we want to improve the efficiency by deciding the order of moves we will search. However, the improvement is not significant. The possible reason is that the way we decide the order is not optimal.
