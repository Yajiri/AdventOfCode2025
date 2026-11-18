use std::fs;

fn matches(a: &[i32], b: &[i32]) -> bool {
    if a.len() != b.len() {
        return false; 
    }
    for (x, y) in a.iter().zip(b.iter()) {
        if x != y {
        return false;
        }
    }
    true
}

fn solve_and_return_best(target: &[i32], buttons: &[Vec<usize>]) -> i32 {
    let mut best = i32::MAX;

    let combinations = 1usize << buttons.len();

    for mask in 0..combinations {
        let mut state = vec![0; target.len()];
        let mut presses: i32 = 0;

        for button in 0..buttons.len() {
            if (mask & (1usize << button)) != 0 {
                presses += 1;
                for &light in &buttons[button]{
                    state[light] ^= 1;
                }
            }
        }
        if matches(&state, target) {
            best = best.min(presses);
        }
    }
    best
}

fn main() {
    let contents = fs::read_to_string("input.txt")
        .expect("This file can't be read!");

    let mut targets: Vec<Vec<i32>> = Vec::new();

    let mut all_buttons: Vec<Vec<Vec<usize>>> = Vec::new();

    for line in contents.lines() {
        let target_start = line.find("[").unwrap();
        let target_end = line.find("]").unwrap();
        let target_str = &line[target_start + 1..target_end];
        let target: Vec<i32> = target_str
            .chars()
            .map(|c| match c {
                '#' => 1,
                '.' => 0,
                _ => panic!("Unexpected character"),
            })
            .collect();
            targets.push(target);
        let mut machine_buttons: Vec<Vec<usize>> = Vec::new();
        let mut remaining = &line[target_end +1..];
        while let Some(start) = remaining.find('(') {
            let after_start = &remaining[start + 1..];
            if let Some(end) = after_start.find(')') {
                let button_str = &after_start[..end];
                let button: Vec <usize> = button_str
                    .split(',')
                    .map(|x| x.trim().parse::<usize>().unwrap())
                    .collect();
                machine_buttons.push(button);
                remaining = &after_start[end + 1..];
            } else {
                break;
            }
        }
        all_buttons.push(machine_buttons);
    }

    if !targets.is_empty() {
        println!("First target = {:?}", targets[0]);
    }

    //need to add my buttons, targets and names 
    let mut total_value = 0i32;
    //making it look more rusty instead of the solution bellow

    //need this instead of the name loop we have in staric, since the amount of inputs isn't set in stone. 
    for i in 0..targets.len() {
        let best = solve_and_return_best(&targets[i], &all_buttons[i]);
        println!("Machine {} requires {} presses.", i + 1, best);
        total_value += best;
    }
    
    println!("The total amount of presses for starting all of the lights correctly is at least {}", total_value);
}