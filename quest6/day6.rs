use std::io;

fn main() {
    //same as in java with it's ArrayList<int[]> rows = new ArrayList<>();
    let mut grid: Vec<Vec<i32>> = Vec::new();
    
    loop{
        println!("Please enter numbers split by spaces (enter done when done)");

        let mut numbers = String::new();
        io::stdin().read_line(&mut numbers).unwrap();

        let numbers = numbers.trim();

        //makes it ignore uppcase and lowercase. 
        if numbers.eq_ignore_ascii_case("DONE") {
            break;
        }
        let row: Vec<i32> = numbers
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();
        
        grid.push(row);       
    }

    println!("Please enter the operators split by spaces");
    let mut operators = String::new();
    io::stdin().read_line(&mut operators).unwrap();

    let operators = operators.trim();

    let ops: Vec<&str> = operators
        .split_whitespace()
        .collect();

    for col in 0..ops.len() {
        if ops[col] == "*" {
            let mut result = 1;
            for row in &grid {
                result *= row[col];
            }
        println!("The value of column {} is {}", col + 1, result);
        }

        else if ops[col] == "+" {
            let mut result = 0;
            for row in &grid {
                result += row[col];
            }
        println!("The value of column {} is {}", col + 1, result);
        }

        else if ops[col] == "-" {
            let mut result = grid[0][col];
            for row in &grid[1..] {
                result -= row[col];
            }
        println!("The value of column {} is {}", col + 1, result);
        }
        
        else if ops[col] == "/" {
            let mut result = grid[0][col];
            for row in &grid[1..] {
                result /= row[col];
            }
        println!("The value of column {} is {}", col + 1, result);
        }
    }
}