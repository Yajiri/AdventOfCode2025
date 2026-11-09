use std::fs;

fn main(){
    let contents = fs::read_to_string("input.txt")
        .expect("This file can't be read.");
    
    let ranges:Vec<(i64, i64)> = contents
        .trim()
        .split(',')
        .map(|token| {
            let mut parts = token.split('-');

            let start: i64 = parts.next().unwrap().parse().unwrap();
            let end: i64 = parts.next().unwrap().parse().unwrap();

            (start, end)
        })
        .collect();
        

let mut invalid_number_value: i64 = 0;
/*so really quick the i64 thing has to do with storage volume normally it stays as i32 (32-bit) 
but the size of the number might exceed it so u64 makes it save as a (64-bit) */
    for (start, end) in ranges {    
        for n in start..=end {
            let s = n.to_string();

            if s.len() % 2 == 0{
                let half = s.len() /2;
                let first_half = &s[..half];
                let second_half = &s[half..];
                if first_half == second_half{
                    println!("{}", n);
                    invalid_number_value = invalid_number_value + n;
                }
            }
        }
    }
    println!("Sum = {}", invalid_number_value)
}