import networkx as nx
import matplotlib.pyplot as plt

# Define the graph as an adjacency list
graph = {
    'A': ['B', 'D'],
    'B': ['A', 'C'],
    'C': ['B', 'D'],
    'D': ['A', 'C']
}

# Define the DFS function


def dfs(graph, node, visited):
    visited.append(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            G.edges[node, neighbor]['color'] = 'r'
            dfs(graph, neighbor, visited)


# Create the graph object using NetworkX
G = nx.Graph(graph)

# Set the initial edge color to black
edge_colors = ['black' for _ in G.edges()]

# Draw the graph with the initial edge colors
nx.draw(G, with_labels=True, edge_color=edge_colors)

# Set the initial color of all edges to black
for u, v in G.edges():
    G.edges[u, v]['color'] = 'black'

# Perform the DFS algorithm and update the edge colors for each visited edge
visited = []
dfs(G.adj, 'A', visited)
edge_colors = ['r' if G.edges[e]['color']
               == 'r' else 'black' for e in G.edges()]

# Draw the graph with the updated edge colors
nx.draw(G, with_labels=True, edge_color=edge_colors)

# Show the final graph
plt.show()
