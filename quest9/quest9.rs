fn main() {
    //let grid: [(i32, i32); 8] = I could do this instead of the _i32 inside the grid. 
    let grid = [
        (7_i32,1_i32),   //the _i32 just shows that both values and all following values in this grid, will be integers. 
        (11,1),
        (11,7),
        (9,7),
        (9,5),
        (2,5),
        (2,3),
        (7,3)
    ];

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