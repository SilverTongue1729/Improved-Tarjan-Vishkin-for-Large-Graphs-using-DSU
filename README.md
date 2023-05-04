# Tarjan Vishkin with DSU for BCCs

## Introduction to Algorithm Engineering Project

- Keval Jain 2021111030
- Sriteja Pashya 2021111019

---

Comparing the performance of Tarjan-Vishkin algorithm with and without DSUs

## Implementation

- We first implement the Tarjan-Vishkin algorithm without DSUs
- Then we implement the Tarjan-Vishkin algorithm with DSUs

## To do

- test program to test the output
- maybe print the output sorted so that we can just use diff

- try to create a visualisation perhaps?
- dfs approach

## Ideas

- Project doc asks us to compare with other algorithms such as Tarjan's
- So we need to implement Tarjan's algorithm as well
- Also look into other algorithms such as Hopcroft-Tarjan, etc.

- What vertex to use as root for Spanning Tree?
- Perhaps use 4-Sweep to choose the root
- Cong Bader
- maintain list of non-tree edges
- such as choosing a dfs tree removes step b
- try partial dfs and bfs trees?
- check slides for another optimisation from some paper
- check with step (a,b,c) takes the most amount of time, and try to optimize it
- or actually try to find the best way to go through all the steps for all non-tree edges
- Try using Ear Decomposition to compress the graph?
