fn main() {
    let mut grid: Vec<Vec<char>> = vec! [
        ".......S.......".chars().collect(),
        "...............".chars().collect(),
        ".......^.......".chars().collect(),
        "...............".chars().collect(),
        "......^.^......".chars().collect(),
        "...............".chars().collect(),
        ".....^.^.^.....".chars().collect(),
        "...............".chars().collect(),
        "....^.^...^....".chars().collect(),
        "...............".chars().collect(),
        "...^.^...^.^...".chars().collect(),
        "...............".chars().collect(),
        "..^...^.....^..".chars().collect(),
        "...............".chars().collect(),
        ".^.^.^.^.^...^.".chars().collect(),
        "...............".chars().collect()
    ];
    let rows = grid.len();
    let cols = grid[0].len();

    let mut count = 0;
    for i in 0..cols {
        if grid[0][i] == 'S'{
            println!("The S can be found in ({})", i);

            grid[1][i] = '|';

            let row: String = grid[1].iter().collect();
            println!("{}", row);
            break;
        }
    }
    for r in 0..(rows -1) {
        for c in 0..cols{
            if grid[r][c] == '|' {
                if grid[r+1][c] == '^' {
                    if c > 0 {
                        grid[r+1][c-1] = '|';
                    } if c < cols {
                        grid[r+1][c+1] = '|';
                    }
                count += 1;
                continue;
                }
                else if grid[r+1][c] == '.' {
                    grid[r+1][c] = '|';
                }
            }
        }
    }
    println!("The beam splits {} amount of times", count);
}