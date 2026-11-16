grid = [
    (7,1),
    (11,1),
    (11,7),
    (9,7),
    (9,5),
    (2,5),
    (2,3),
    (7,3)
]

largest = 0

for i in range(len(grid)):
    for j in range((i + 1), len(grid)):
        dx = abs(grid[i][0] - grid[j][0]) + 1
        dy = abs(grid[i][1] - grid[j][1]) + 1
        area = dx * dy

        largest = max(largest, area)

print("The largest grid has an area of", largest)