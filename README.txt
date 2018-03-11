-How and what each group member contributes to the project:

Jing Ding: Implement minimax; Improve the heuristic function; Write the function to decide how much time should be allocated to each search; Reading papers for ideas.

Shuyue Yu: Implement alpha-beta pruning; Implement Interactive Deepening; Write the function to decide the order of moves we will use to search; Write the testing program.


-Improvements that our group has made:

Alpha-beta pruning: Through testing, we find that alpha-beta successfully increase the speed of calculation. Our bot can go into deeper levels in the same amount of time.

Interactive Deepening: Our bot used to end the game with a large amount of time remaining. Thus, we use Interactive Deepening to make sure that the bot uses the given time fully and efficiently.

Write the function to decide the order of moves we will use to search: We found out sometimes the branch we will cut in the alpha-beta pruning is searched at the end, which means that the alpha-beta pruning has no effect. Thus, we want to improve the efficiency by deciding the order of moves we will search. However, the improvement is not very obvious. The possible reason is that the way we decide the order is not good enough.
