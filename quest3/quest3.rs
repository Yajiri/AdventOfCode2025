use std::io;

fn main() {
    let mut largest = 0;
    let mut second_largest = 0;
    let mut start_index = 0;

    println!("Please enter the number sequence: ");
    let mut string_of_numbers = String::new();
    io::stdin()
        .read_line(&mut string_of_numbers)
        .expect("Failed to read input");
    
    let string_of_numbers = string_of_numbers.trim();
    let bytes = string_of_numbers.as_bytes();
    let len = bytes.len();

    for i in 0..(len - 1) {
        if bytes[i] == b'9' {
            largest = 9;
            start_index = i + 1;
            break;
        }

        let digit = (bytes[i] -b'0') as i32;

        if digit > largest {
            largest = digit;
            start_index = i + 1;
        }
    }

    for i in start_index..len {
        let digit = (bytes[i] -b'0') as i32;

        if digit > second_largest {
            second_largest = digit;
        }
    }
    println!("The largest possible number is: {}{}", largest, second_largest);
}