grid = [
    "..@@.@@@@.",
    "@@@.@.@.@@",
    "@@@@@.@.@@",
    "@.@@@@..@.",
    "@@.@@@@.@@",
    ".@@@@@@@.@",
    ".@.@.@.@@@",
    "@.@@@.@@@@",
    ".@@@@@@@@.",
    "@.@.@@@.@."  
];

rows = len(grid)
cols = len(grid[0])

dr = [-1,-1,-1,0,0,1,1,1]
dc = [-1,0,1,-1,1,-1,0,1]

count = 0;

for r in range(rows):
    for c in range(cols):
        if grid[r][c] != '@':
            continue

        neighbors = 0

        for i in range(len(dr)):
            nr = r + dr[i]
            nc = c + dc[i]

            if (nr >= 0 and nr < rows and 
                nc >= 0 and nc < cols and 
                grid[nr][nc] == '@'):
                neighbors += 1

        removable = neighbors < 4
        if removable:
            count += 1
            print("(", r, c, ") can be removed", sep="")
print(count, "can be removed")