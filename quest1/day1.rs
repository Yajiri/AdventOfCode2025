use std::fs;
//fs stands for file system, used in order to read from a file. fs::read_to_string
//use std::io this let's you do stdin(), stdout(), BufReader, Read, Write.

fn main(){
let commands = fs::read_to_string("input.txt")
    .expect("could not read the input file");

    let mut start_point = 50;
    let mut x = 0;

    for command in commands.lines() {
            let command = command.trim().to_uppercase();

            if command.is_empty() {
                continue;
            }

            let direction = command.chars().next().unwrap();
            let move_steps: i32 = command[1..].parse().unwrap();

            if direction == 'L'{
                start_point = (start_point + move_steps) % 100;

                if start_point == 0 {
                    x += 1;
                }
            } else if direction == 'R' {
                start_point = ((start_point - move_steps) % 100 + 100) % 100;

                if start_point == 0 {
                    x += 1;
                }
            }
    }
    println!("Stopped at 0: {} amount of times", x);
}