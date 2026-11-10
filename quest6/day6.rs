use std::fs;

fn main() {
    let contents = fs::read_to_string("input.txt")
            .expect("This file can't be found");
 
    let mut numbers: Vec<Vec<i64>> = Vec::new();
    let mut final_result = 0 as i64;
    //collects all lines in a string variable.
    let all_lines: Vec<&str> = contents.lines().collect();

    //sets the last line to be the operator line
    let operators: Vec<char> = all_lines
        .last()
        .unwrap()
        .split_whitespace()
        .map(|s| s.chars().next().unwrap())
        .collect();
    
    //rolls through everything except the last line and adds them to the numbers grid
    for line in &all_lines[..all_lines.len() - 1] {
        let row: Vec<i64> = line
            .split_whitespace()
            .map(|s| s.parse::<i64>().unwrap())
            .collect();
        numbers.push(row);
    }

    for col in 0..operators.len() {
        if operators[col] == '*' {
            let mut result = 1;
            for row in &numbers {
                result *= row[col];
            }
        final_result = final_result + result;
        //println!("The value of column {} is {}", col + 1, result);
        }

        else if operators[col] == '+' {
            let mut result = 0;
            for row in &numbers {
                result += row[col];
            }
        final_result = final_result + result;
        //println!("The value of column {} is {}", col + 1, result);
        }

        else if operators[col] == '-' {
            let mut result = numbers[0][col];
            for row in &numbers[1..] {
                result -= row[col];
            }
        final_result = final_result + result;
        //println!("The value of column {} is {}", col + 1, result);
        }
        
        else if operators[col] == '/' {
            let mut result = numbers[0][col];
            for row in &numbers[1..] {
                result /= row[col];
            }
        final_result = final_result + result;
        //println!("The value of column {} is {}", col + 1, result);
        }
    }
    println!("The final result is: {}", final_result);
}