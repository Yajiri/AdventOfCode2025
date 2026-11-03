fn main() {

    let ranges = [
        (3,5),
        (10,14),
        (16,20),
        (12,18)
    ];

    //let numbers = [1, 5, 8 ,11 ,17, 32]; This is a hardcoded version as they asked for in the Day 5 adventofcode.
    //I wanted it to be input based, hoping that is okey!
    println!("Enter numbers separated by spaces:");

    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    
    let numbers: Vec<i32> = input
            .split_whitespace()
            .map(|s| s.parse().unwrap())
            .collect();

    for number in numbers {
        let mut fresh = false;

        for (start, end) in ranges {
            if number >= start && number <= end {
                fresh = true;
                break;
            }
        }
        if fresh {
            println!("The number {} is a fresh item!", number);
        } else {
            println!("The number {} is not a fresh item!", number);
        }
    }
}