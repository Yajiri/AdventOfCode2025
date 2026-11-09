use std::fs;

fn main() {
    let mut fresh_items = 0;
    let contents = fs::read_to_string("input.txt")
            .expect("This file can't be found.");
        
    let mut ranges: Vec<(i64,i64)> = Vec::new();
    let mut numbers: Vec<i64> = Vec::new();
    let mut reading_ranges = true;

    for line in contents.lines() {
        let line = line.trim();

        if line.is_empty() {
            reading_ranges = false;
            continue;
        }

        if reading_ranges {
            let mut parts = line.split('-');

            let start: i64 = parts.next().unwrap().parse().unwrap();
            let end: i64 = parts.next().unwrap().parse().unwrap();

            ranges.push((start, end));
        } else {
            numbers.push(line.parse().unwrap());
        }
    }

    for number in numbers {
        for (start, end) in &ranges {
            if number >= *start && number <= *end {
                fresh_items = fresh_items + 1;
                break;
            }
        }
    }
    println!("Number of fresh items: {}", fresh_items);
}