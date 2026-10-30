use std::io;

fn main(){
    let mut start_point = 50;
    let mut x = 0;

    loop{
        println!("Command:");

        let mut command = String::new();
        io::stdin()
            .read_line(&mut command)
            .expect("Failed to read input");
        
            let command = command.trim().to_uppercase();

            if command = "DONE" {
                break;
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