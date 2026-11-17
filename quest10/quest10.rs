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
    let targets: Vec<Vec<i32>> = vec![
    vec![0, 1, 1, 0],
    vec![0, 0, 0, 1, 0],
    vec![0, 1, 1, 1, 0, 1],
];
    let all_buttons: Vec<Vec<Vec<usize>>> = vec![
    vec![
        vec![3],
        vec![1, 3],
        vec![2],
        vec![2, 3],
        vec![0, 2],
        vec![0, 1],
    ],

    vec![
        vec![0, 2, 3, 4],
        vec![2, 3],
        vec![0, 4],
        vec![0, 1, 2],
        vec![1, 2, 3, 4],
    ],

    vec![
        vec![0, 1, 2, 3, 4],
        vec![0, 3, 4],
        vec![0, 1, 2, 4, 5],
        vec![1, 2],
    ],
];
    // I know it's really config 0-2 but 1-3 looks better in print.
    let names = vec![
    "Config 1 [.##.]",
    "Config 2 [...#.]",
    "Config 3 [.###.#]",
];

    //need to add my buttons, targets and names 
    let mut total_value = 0i32;
    //making it look more rusty instead of the solution bellow
    for ((target, buttons), name) in targets
        .iter()
        .zip(all_buttons.iter())
        .zip(names.iter())
    {
        let best = solve_and_return_best(target, buttons);

        println!("The quickest solution for {} is {} amount of presses!",
                name,
                best);
            total_value += best;
    }
    /*for i in 0..targets.len() {
        let best = solve_and_return_best(&targets[i], &all_buttons[i]);
        println!("The quickest solution for {} is {} amount of presses", names[i], best);
        total_value += best;
    }*/
    println!("The total amount of presses for starting all of the lights correctly is at least {}", total_value);
}