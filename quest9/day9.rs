use std::fs;

fn main() {
    let contents = fs::read_to_string("input.txt")
        .expect("This file can't be read");

    let mut grid: Vec<(i64,i64)> = Vec::new();
    for line in contents.lines() {
        let line = line.trim();
 
        let mut parts = line.split(",");
        let red_tile_row: i64 = parts.next().unwrap().parse().unwrap();
        let red_tile_col: i64 = parts.next().unwrap().parse().unwrap();

        grid.push((red_tile_row, red_tile_col));
    }

    let mut largest = 0;

        for i in 0..grid.len() {
            for j in (i+1)..grid.len() {
                let dx = (grid[i].0 - grid[j].0).abs() + 1;
                let dy = (grid[i].1 - grid[j].1).abs() + 1;

                let area = dx * dy;

                if area > largest {
                largest = area;
            }
        }
    }
    println!("The largest grid is {}", largest);
}