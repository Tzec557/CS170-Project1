# CS170-Project1

# 8 puzzle search algorithm

## Your challenges in this project
- Understanding and implementing A* search with different heuristics (Misplaced Tile vs. Euclidean Distance).

- Balancing readability and performance, especially with priority queue operations in A*.

## Your design (objects and methods)
- Node class:

        Stores current puzzle state, pointer to parent, depth (g), heuristic value (h), and total cost (f = g + h).

        Methods: comparison operator for priority queue, printing state for trace output.

- Problem class:

        Holds initial and goal states, and provides getNeighbors(node) and goalTest(state).

- Search Algorithms:

         uniformCostSearch(Problem): h(n) = 0.

         A* Misplaced(Problem): h(n) = number of misplaced tiles.

         A* Euclidean(Problem): h(n) = sum of Euclidean distances of tiles from goal positions.

## Did you try optimizing your code by using special data structures that make searching for and comparing states faster?

- Used priority queue for frontier to always expand the node with the lowest f.

- Used set of vectors for explored states to efficiently check for repeats.

## Did you implement a graph search (keeping record of all explored nodes), or did you use a tree search algorithm? If you tried both, you can compare the number of nodes created, and number of nodes expanded for each version (tree search and graph search). Note that you don’t ned to implement and compare both tree and graph searches. But if you did, you can write about your observations.

### Implementation details and observations

#### Uniform Cost Search (UCS)

This uses a closed set and inserts a state into that set when it is popped from the priority queue. -> Graph-search

- We avoid re-expanding any state that has already been expanded.
- We did not perform a “decrease-key” / frontier update when a better path to an already enqueued state is found -> instead, dupes may accumulate in the priority queue, and the smallest-g copy is popped first.
- Correctness is preserved because nodes are popped in nondecreasing g, and we only close a node when popped, but the lack of explicit frontier updates can increase memory and push operations.

#### A* Misplaced Tile

This uses the same closed set and computes h for each child before pushing; hence, this is also a Graph-search.

- Since the misplaced-tile heuristic is admissible, using a closed set is safe -> the first time a state is popped, its g is optimal, and it won’t need to be reopened.
- We added a simple tie-break so runs are reproducible.
- As with UCS, the code does not perform an explicit decrease-key on the frontier, so dupe states may be pushed if discovered through different paths; but A* still expands far fewer nodes than UCS due to the heuristic.

#### A* Euclidean

This heuristic is admissible and is consistent for unit-cost tile moves, so A* with a closed set is guaranteed to find an optimal solution.

- It never overestimates the number of moves because the straight-line distance is a lower bound on grid Manhattan moves.
- Euclidean distance provides a stronger estimate than the misplaced-tile count, so A*-Euclidean expands far fewer nodes than A*-misplaced and far fewer than UCS.
- However, per-node computation is slightly more expensive and should be handled consistently to ensure reproducible comparisons.


## Comparing Heuristic Functions in terms of time and space and analyzing the results with diagrams and/or tables. Sample tables and diagrams follow.
<img width="500" height="600" alt="截屏2025-11-03 下午4 51 46" src="https://github.com/user-attachments/assets/d24beea2-8b20-44c4-8e0c-d260bb2a7928" /><img width="471" height="328" alt="截屏2025-11-03 下午4 05 20" src="https://github.com/user-attachments/assets/82e0fa9c-327c-4ae2-867f-8ee8bec0ddc7" />

From the table comparing different search algorithms across multiple puzzles, we can see that A* with heuristics (Misplaced Tile and Euclidean) consistently expands fewer nodes and uses less memory than Uniform Cost Search. The Euclidean heuristic often results in slightly fewer nodes expanded than the Misplaced Tile, indicating it is a slightly more informed heuristic.


<img width="600" height="700" alt="截屏2025-11-03 下午3 48 10" src="https://github.com/user-attachments/assets/9377c6c5-01fb-4bff-b358-15c6bda92d0a" />

The A* Euclidean Distance heuristic expanded the fewest nodes among all algorithms, showing it is the most efficient at guiding the search toward the goal. The A* Misplaced Tile heuristic also performed better than Uniform Cost Search, but not as efficiently as A* Euclidean. This demonstrates that stronger heuristics reduce the search space and improve performance.

<img width="618" height="610" alt="截屏2025-11-03 下午3 47 52" src="https://github.com/user-attachments/assets/51ea45a5-b35d-462d-9bff-fa2ad7b7c636" />

From the multi-line graph comparing maximum queue sizes, we observe that Uniform Cost Search consistently consumes the most memory, as it explores many unnecessary states. The A* algorithms, guided by heuristics, use significantly less memory. Between the two heuristics, A* with Euclidean Distance maintains the smallest queue sizes, demonstrating the advantage of using a more accurate heuristic to focus the search and reduce space complexity.

## Finding:

Heuristic-based searches (A*) are significantly more efficient than Uniform Cost Search in terms of time, space, and number of nodes expanded. For simple puzzles, all algorithms performed similarly, but as puzzle difficulty increased, the A* algorithms found solutions faster and expanded fewer nodes. 
