grid = [
    list(".......S......."),
    list("..............."),
    list(".......^......."),
    list("..............."),
    list("......^.^......"),
    list("..............."),
    list(".....^.^.^....."),
    list("..............."),
    list("....^.^...^...."),
    list("..............."),
    list("...^.^...^.^..."),
    list("..............."),
    list("..^...^.....^.."),
    list("..............."),
    list(".^.^.^.^.^...^."),
    list("...............")   
]

rows = len(grid)
cols = len(grid[0])

count = 0

for i in range(cols):
    if grid[0][i] == 'S':
        print("S can be found at (0,", i, ")", sep="")

        grid[1][i] = '|'

        print("".join(grid[1]))

for r in range(rows - 1):
    for c in range(cols):
        if grid[r][c] == '|':
            if grid[r+1][c] =='^':
                if c > 0:
                    grid[r+1][c-1] = '|'
                if c + 1 < cols:
                    grid[r+1][c+1] = '|'
                count += 1
                continue
            elif grid[r+1][c] == '.':
                grid[r+1][c] = '|'
print("The beam split", count, "amount of times")
