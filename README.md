# CS170-Project1
8 puzzle search algorithm

Items you can include in your report:

Your challenges in this project
- Understanding and implementing A* search with different heuristics (Misplaced Tile vs. Euclidean Distance).

- Balancing readability and performance, especially with priority queue operations in A*.

Your design (objects and methods)
- Node class:

        - Stores current puzzle state, pointer to parent, depth (g), heuristic value (h), and total cost (f = g + h).

        - Methods: comparison operator for priority queue, printing state for trace output.

- Problem class:

        - Holds initial and goal states, and provides getNeighbors(node) and goalTest(state).

- Search Algorithms:

        - uniformCostSearch(Problem): h(n) = 0.

        - aStarMisplaced(Problem): h(n) = number of misplaced tiles.

        - aStarEuclidean(Problem): h(n) = sum of Euclidean distances of tiles from goal positions.

Did you try optimizing your code by using special data structures that make searching for and comparing states faster?

- Used priority queue for frontier to always expand the node with the lowest f.

- Used set of vectors for explored states to efficiently check for repeats.

Did you implement a graph search (keeping record of all explored nodes), or did you use a tree search algorithm? If you tried both, you can compare the number of nodes created, and number of nodes expanded for each version (tree search and graph search). Note that you don’t ned to implement and compare both tree and graph searches. But if you did, you can write about your observations.

Comparing Heuristic Functions in terms of time and space and analyzing the results with diagrams and/or tables. Sample tables and diagrams follow.

Your findings.

Hint: Your findings for this project will be something like this:

• For shallow problems, it does not matter too much what heuristic you use, if any.

• As the problems get harder, heuristics help more and more.

• A good heuristic is better than a weak heuristic