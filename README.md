# Incorporating DSUs with Tarjan Vishkin for finding BCCs in graphs

## Introduction to Algorithm Engineering Project

- Keval Jain | 2021111030
- Sriteja Pashya | 2021111019

---

- Implemented non-parallel version of Tarjan-Vishkin algorithm: [An Efficient Parallel Biconnectivity Algorithm](https://www.researchgate.net/publication/220617428_An_Efficient_Parallel_Biconnectivity_Algorithm).
- Incorporated DSUs when adding edges to G’.
- Implemented [Tarjan's Algorithm](https://en.wikipedia.org/wiki/Tarjan%27s_algorithm).
- Compared performance of both on various types of graphs of various sizes.
- Result: Tarjan-Vishkin with DSUs performances better than Tarjan's on Large Graphs.

## Execution

- For each code, run the command `g++ -std=c++17 -Ofast filename.cpp -o filename`.
- Then run `./filename < input_file > output_file`.
- To generate random graphs use `randomgraph.cpp` and run `./randomgraph > input_file`.
- Number of vertices and edges can be changed in the code.

## Assumptions

- The graph need not be connected.
- Graph need not be simple.
- Graph doesn't have self-loops.
