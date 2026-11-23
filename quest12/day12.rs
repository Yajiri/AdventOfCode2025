use std::fs;
use std::time::{Duration, Instant};

type Net = Vec<Vec<char>>;
type Board = Vec<Vec<usize>>;

struct Puzzle {
    width: usize,
    height: usize,
    // requirements[i] = how many copies of nets[i] must be placed
    requirements: Vec<usize>,
}

// Returns true if all counts are zero: i.e. we have placed all required pieces.
fn all_counts_zero(counts: &[usize]) -> bool {
    counts.iter().all(|&c| c == 0)
}

// Rotate a net 90 degrees clockwise.
// Input:  h x w
// Output: w x h
fn rotate_90(net: &Net) -> Net {
    let h = net.len();
    let w = net[0].len();
    // After rotation, width and height are swapped
    let mut rotated = vec![vec!['.'; h]; w];
    for y in 0..h {
        for x in 0..w {
            rotated[x][h - 1 - y] = net[y][x];
        }
    }
    rotated
}

// Generate all 4 unique rotations of a net (0°, 90°, 180°, 270°).
// Some nets might be symmetric, in which case duplicates are filtered out.
fn generate_rotations(net: &Net) -> Vec<Net> {
    let mut forms: Vec<Net> = Vec::new();

    let mut current = net.clone();
    for _ in 0..4 {
        // Only keep this orientation if we haven't seen it already
        if !forms.iter().any(|f| *f == current) {
            forms.push(current.clone());
        }
        current = rotate_90(&current);
    }

    forms
}

// Count how many '#' cells are in a net.
fn net_area(net: &Net) -> usize {
    net.iter()
        .map(|row| row.iter().filter(|&&c| c == '#').count())
        .sum()
}

// Check if a given net (in its current orientation) can be placed on the board
// starting at (start_x, start_y) without going out of bounds and without
// overlapping previously placed pieces.
fn fits(
    board: &Board,
    net: &Net,
    start_x: usize,
    start_y: usize,
) -> bool {
    for net_y in 0..net.len() {
        for net_x in 0..net[0].len() {
            // Only consider filled cells of the net
            if net[net_y][net_x] != '#' {
                continue;
            }

            let board_x = start_x + net_x;
            let board_y = start_y + net_y;

            // Out of bounds: net doesn't fit here
            if board_y >= board.len() || board_x >= board[0].len() {
                return false;
            }

            // Overlap: this cell is already used by some piece
            if board[board_y][board_x] > 0 {
                return false;
            }
        }
    }

    true
}

// Place a net on the board at (start_x, start_y).
fn place_piece(
    board: &mut Board,
    net: &Net,
    start_x: usize,
    start_y: usize,
) {
    for net_y in 0..net.len() {
        for net_x in 0..net[0].len() {
            if net[net_y][net_x] == '#' {
                board[start_y + net_y][start_x + net_x] += 1;
            }
        }
    }
}

// Undo placement of a net from the board at (start_x, start_y).
fn remove_piece(
    board: &mut Board,
    net: &Net,
    start_x: usize,
    start_y: usize,
) {
    for net_y in 0..net.len() {
        for net_x in 0..net[0].len() {
            if net[net_y][net_x] == '#' {
                board[start_y + net_y][start_x + net_x] -= 1;
            }
        }
    }
}

// Backtracking solver:
// - board: current state of the puzzle
// - nets_with_rotations[piece_index]: all orientations of that piece
// - counts[piece_index]: how many copies of that piece still need to be placed
// - nodes_explored: counter of recursive calls / placement attempts
// - node_limit: hard cap to avoid infinite search
fn solve(
    board: &mut Board,
    nets_with_rotations: &[Vec<Net>],
    counts: &mut Vec<usize>,
    nodes_explored: &mut u64,
    node_limit: u64,
) -> bool {
    // Hard cutoff: stop if we've explored too many nodes
    if *nodes_explored > node_limit {
        return false;
    }

    // Base case: all required pieces are placed
    if all_counts_zero(counts) {
        return true;
    }

    // Try to place one more piece of each type that remains
    for piece_index in 0..nets_with_rotations.len() {
        // Skip pieces that we don't need anymore
        if counts[piece_index] == 0 {
            continue;
        }

        // Try all rotations of this piece
        for net in &nets_with_rotations[piece_index] {
            // Try all positions on the board
            for y in 0..board.len() {
                for x in 0..board[0].len() {
                    *nodes_explored += 1;
                    if *nodes_explored > node_limit {
                        return false;
                    }

                    // If it doesn't fit here, skip
                    if !fits(board, net, x, y) {
                        continue;
                    }

                    // Place the piece and recurse
                    place_piece(board, net, x, y);
                    counts[piece_index] -= 1;

                    if solve(
                        board,
                        nets_with_rotations,
                        counts,
                        nodes_explored,
                        node_limit,
                    ) {
                        return true; // Found a complete solution
                    }

                    // Backtrack: undo placement and restore count
                    counts[piece_index] += 1;
                    remove_piece(board, net, x, y);
                }
            }
        }
    }

    // No placement worked for the remaining pieces
    false
}

// Parse the input file:
// - Nets are blocks like:
//     4:
//     ##.
//     .##
//     ..#
//
//   The number before ':' can be ignored; we just take the following
//   contiguous non-empty lines of '#' and '.' as the shape.
//
// - Puzzles are lines like:
//     48x44: 56 56 65 51 44 50
fn parse_input(path: &str) -> (Vec<Net>, Vec<Puzzle>) {
    let contents = fs::read_to_string(path).expect("Failed to read input file");
    let mut nets: Vec<Net> = Vec::new();
    let mut puzzles: Vec<Puzzle> = Vec::new();

    let mut lines = contents.lines().peekable();

    while let Some(line) = lines.next() {
        let line = line.trim();
        if line.is_empty() {
            continue;
        }

        // Net header: "<number>:"
        if line.ends_with(':') && line.chars().all(|c| c.is_ascii_digit() || c == ':') {
            // Read following non-empty lines of '#' and '.' as the net shape
            let mut net_rows: Vec<Vec<char>> = Vec::new();
            while let Some(&next_line) = lines.peek() {
                let next_line_trimmed = next_line.trim();
                if next_line_trimmed.is_empty() {
                    lines.next();
                    break;
                }
                // If line has only '#' or '.', treat it as part of the net
                if next_line_trimmed
                    .chars()
                    .all(|c| c == '#' || c == '.')
                {
                    net_rows.push(next_line_trimmed.chars().collect());
                    lines.next();
                } else {
                    break;
                }
            }
            if !net_rows.is_empty() {
                nets.push(net_rows);
            }
            continue;
        }

        // Puzzle line: "WIDTHxHEIGHT: a0 a1 a2 ..."
        if let Some(colon_pos) = line.find(':') {
            let (dims_part, rest) = line.split_at(colon_pos);
            let dims_part = dims_part.trim();
            let rest = &rest[1..]; // skip ':'

            if let Some(x_pos) = dims_part.find('x') {
                let (w_str, h_str) = dims_part.split_at(x_pos);
                let w_str = w_str.trim();
                let h_str = &h_str[1..]; // skip 'x'

                if let (Ok(width), Ok(height)) = (w_str.parse::<usize>(), h_str.parse::<usize>()) {
                    let requirements: Vec<usize> = rest
                        .split_whitespace()
                        .map(|s| s.parse::<usize>().expect("Invalid requirement number"))
                        .collect();

                    puzzles.push(Puzzle {
                        width,
                        height,
                        requirements,
                    });
                    continue;
                }
            }
        }

        // Any other line format is ignored.
    }

    (nets, puzzles)
}

fn main() {
    let mut counter = 0;

    // Read nets and puzzles from input.txt
    let (nets, puzzles) = parse_input("input.txt");

    if nets.is_empty() {
        println!("No nets parsed from input.txt");
        return;
    }
    if puzzles.is_empty() {
        println!("No puzzles parsed from input.txt");
        return;
    }

    // Precompute rotations for each net.
    let nets_with_rotations: Vec<Vec<Net>> =
        nets.iter().map(|n| generate_rotations(n)).collect();

    // Precompute the area (number of '#' cells) of each original net.
    let net_areas: Vec<usize> = nets.iter().map(|n| net_area(n)).collect();

    // Node limit and time limit
    let node_limit: u64 = 55_000_000;
    let time_limit = Duration::from_secs(10);

    for puzzle in &puzzles {
        let board_area = puzzle.width * puzzle.height;

        // Compute total required '#' area for this puzzle.
        let required_area: usize = puzzle
            .requirements
            .iter()
            .enumerate()
            .map(|(i, &count)| {
                if i >= net_areas.len() {
                    panic!("Puzzle requires net index {} but only {} nets were parsed",
                           i, net_areas.len());
                }
                count * net_areas[i]
            })
            .sum();

        println!(
            "Puzzle {}x{} – required area: {}, board area: {}",
            puzzle.width, puzzle.height, required_area, board_area
        );

        // Only prune impossible (too big) cases; allow holes.
        if required_area > board_area {
            println!(
                "No solution for {}x{} (pieces require more area than the board)\n",
                puzzle.width, puzzle.height
            );
            continue;
        }

        let mut board: Board = vec![vec![0; puzzle.width]; puzzle.height];
        let mut counts = puzzle.requirements.clone();
        let mut nodes_explored: u64 = 0;
        let start = Instant::now();

        let solved = solve(
            &mut board,
            &nets_with_rotations,
            &mut counts,
            &mut nodes_explored,
            node_limit,
        );

        let elapsed = start.elapsed();

        if solved {
            counter += 1;
            println!(
                "Solved {}x{} in {:?}, nodes explored: {}",
                puzzle.width, puzzle.height, elapsed, nodes_explored
            );
            for row in &board {
                for cell in row {
                    if *cell > 0 {
                        print!("#");
                    } else {
                        print!(".");
                    }
                }
                println!();
            }
        } else {
            if nodes_explored > node_limit || elapsed > time_limit {
                println!(
                    "Stopped search for {}x{} (limit reached), nodes explored: {}, time: {:?}",
                    puzzle.width, puzzle.height, nodes_explored, elapsed
                );
            } else {
                println!(
                    "No solution found for {}x{} (exhaustive within limits), nodes explored: {}, time: {:?}",
                    puzzle.width, puzzle.height, nodes_explored, elapsed
                );
            }
        }

        println!();
    }
    println!("Total solved puzzles: {}", counter);
}
