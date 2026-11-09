use std::fs;

fn main() {
    let input = fs::read_to_string("input.txt")
        .expect("This file can't be found.");

    let mut total = 0;

    for line in input.lines() {
        if line.is_empty() {
            continue;
        }

        let bytes = line.as_bytes();
        let len = bytes.len();

    let mut largest = 0;
    let mut second_largest = 0;
    let mut start_index = 0;

    for i in 0..(len - 1) {
        if bytes[i] == b'9' {
            largest = 9;
            start_index = i + 1;
            break;
            }

        let digit = (bytes[i] -b'0') as i64;

        if digit > largest {
            largest = digit;
            start_index = i + 1;
            }
        }

    for i in start_index..len {
        let digit = (bytes[i] -b'0') as i64;

        if digit > second_largest {
            second_largest = digit;
            }
        }

    let value = largest * 10 + second_largest;
    total += value;
    }
    println!("The largest possible number is: {}", total);
}