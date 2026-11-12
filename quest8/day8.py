from pathlib import Path

script_dir = Path(__file__).parent
input_file = script_dir / "input.txt"

points = []

with open(input_file, "r") as f:
    for line in f:
        line = line.strip()

        if line:
            points.append(tuple(map(int, line.split(","))))

def dist2(a, b):
    dx = a[0] - b[0]
    dy = a[1] - b[1]
    dz = a[2] - b[2]

    return dx * dx + dy * dy + dz * dz

best_dist = float('inf')
best_pair = None

pairs = []

for i in range(len(points)):
    for j in range(i + 1, len(points)):
        d = dist2(points[i], points[j])
        pairs.append((d, i, j))

#Sorts by distance
pairs.sort()

#Saves the 10 shortest
shortest_10 = pairs[:1000]

print("The 10 shortest connections: ")
for d, a, b in shortest_10:
    print(points[a], "<->", points[b], "distance² =", d)

#Graph
graph = {i: [] for i in range(len(points))}

for d, a, b in shortest_10:
    graph[a].append(b)
    graph[b].append(a)

#find connected components
visited = set()
sizes = []

for start in range(len(points)):
    if start in visited:
        continue

    stack = [start]
    size = 0

    while stack:
        node = stack.pop()

        if node in visited:
            continue

        visited.add(node)
        size += 1

        for neighbor in graph[node]:
            if neighbor not in visited:
                stack.append(neighbor)

    sizes.append(size)

sizes.sort(reverse=True)

print("\nCircuit sizes:", sizes)

answer = sizes[0] * sizes[1] * sizes[2]

print("\nAnswer:", answer)
