import networkx as nx
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Define the graph as an adjacency list
graph = {
    'A': ['B', 'D'],
    'B': ['A', 'C'],
    'C': ['B', 'D'],
    'D': ['A', 'C']
}

# Define the DFS function


def dfs(graph, node, visited, edge_colors):
    visited.append(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            edge_colors[(node, neighbor)] = 'r'
            yield edge_colors
            yield from dfs(graph, neighbor, visited, edge_colors)


# Create the graph object using NetworkX and set its position using a circular layout
pos = nx.circular_layout(graph)
G = nx.Graph(graph)
G.pos = pos

# Set the initial edge color to black
edge_colors = {e: 'black' for e in G.edges()}

# Set up the figure and axis for the animation
fig, ax = plt.subplots()
ax.set_xlim(-1.2, 1.2)
ax.set_ylim(-1.2, 1.2)

# Draw the initial graph with the initial edge colors and positions
nx.draw(G, with_labels=True, edge_color=edge_colors.values(), pos=pos)

# Set the initial color of all edges to black
for u, v in G.edges():
    edge_colors[(u, v)] = 'black'

# Set up the animation function to update the edge colors for each visited edge
visited = []


def update(frame):
    global visited, edge_colors
    if frame == 0:
        return
    visited.append('A')
    generator = dfs(G.adj, 'A', visited, edge_colors)
    for e in generator:
        edge_colors = e
        ax.clear()  # Clear the axis before drawing the updated graph
        # Pass the position dictionary to the nx.draw() function
        nx.draw(G, with_labels=True, edge_color=edge_colors.values(), pos=pos)
        plt.pause(1)
    return


# Create and run the animation
ani = FuncAnimation(fig, update, frames=range(5), blit=False)
plt.show()
