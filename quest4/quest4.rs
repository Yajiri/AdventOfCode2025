fn main() {
    let grid: Vec<Vec<char>> = vec![
    "..@@.@@@@.".chars().collect(),
    "@@@.@.@.@@".chars().collect(),
    "@@@@@.@.@@".chars().collect(),
    "@.@@@@..@.".chars().collect(),
    "@@.@@@@.@@".chars().collect(),
    ".@@@@@@@.@".chars().collect(),
    ".@.@.@.@@@".chars().collect(),
    "@.@@@.@@@@".chars().collect(),
    ".@@@@@@@@.".chars().collect(),
    "@.@.@@@.@.".chars().collect()
];

let rows = grid.len();
let cols = grid[0].len();

let dr = [-1,-1,-1,0,0,1,1,1];
let dc = [-1,0,1,-1,1,-1,0,1]; 

let mut count = 0;

for r in 0..rows{
    for c in 0..cols {
        if grid[r][c] != '@'{
            continue; 
        }
        let mut neighbors = 0;

        for i in 0..dr.len() {
            let nr = r as i32 + dr[i];
            let nc = c as i32 + dc[i];

            if nr >= 0 
                && nr < rows as i32 
                && nc >= 0 
                && nc < cols as i32 
                && grid[nr as usize][nc as usize] == '@'
                {
                    neighbors += 1;
            }
        }
    let removable = neighbors < 4;
    if removable {
        count += 1;
        println!("({},{}) can be removed.", r, c);
            }
        }
    }
    println!("{} can be removed.", count);
}