# Write a Program to Implement Travelling Salesman Problem using Python.

print("Name : Manoj KC")
print("Level : Bsc. Csit(4th sem) ")
print("Section : B")

from sys import maxsize
from itertools import permutations

# Number of vertices in the graph
V = 4

# Function to implement the Traveling Salesman Problem
def travellingSalesmanProblem(graph, s):
    # Store all vertices except the source vertex
    vertex = []
    for i in range(V):
        if i != s:
            vertex.append(i)

    # Initialize the minimum path as a large number
    min_path = maxsize

    # Generate all permutations of vertices (cities) except the source
    next_permutation = permutations(vertex)

    # Iterate over all permutations to calculate the minimum path
    for i in next_permutation:
        # Store the current path weight (cost)
        current_pathweight = 0

        # Start from the source
        k = s

        # Calculate the cost of the path for the current permutation
        for j in i:
            current_pathweight += graph[k][j]
            k = j

        # Add the cost of returning to the source
        current_pathweight += graph[k][s]

        # Update the minimum path if a shorter path is found
        min_path = min(min_path, current_pathweight)

    return min_path

# Driver Code
if __name__ == "__main__":
    # Matrix representation of the graph (distance matrix)
    graph = [[0, 10, 15, 20],
             [10, 0, 35, 25],
             [15, 35, 0, 30],
             [20, 25, 30, 0]]

    # Starting point (source)
    s = 0

    # Output the minimum cost of the TSP
    print(travellingSalesmanProblem(graph, s))
