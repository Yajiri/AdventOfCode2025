use std::fs::File;
use std::io::{self, BufRead, BufReader};

struct Pair {
    distance: i64,
    i: usize,
    j: usize,
}

fn dist_2(a: [i64; 3], b: [i64; 3]) -> i64 {
    let dx = (a[0] - b[0]) as i64;
    let dy = (a[1] - b[1]) as i64;
    let dz = (a[2] - b[2]) as i64;

    dx * dx + dy * dy + dz * dz
}

fn get_shortest_10(points: &[[i64; 3]]) -> Vec<Pair> {
    let mut pairs: Vec<Pair> = Vec::new();
    for i in 0..points.len() {
        for j in (i + 1)..points.len() {
            let d = dist_2(points[i], points[j]);
            pairs.push(Pair { distance: d, i, j });
        }
    }
    pairs.sort_by_key(|p| p.distance);

    for k in 0..pairs.len().min(1000) {
        let p = &pairs[k];
        println!("distance = {}, i = {}, j = {}", p.distance, p.i, p.j);
    }

    let n = pairs.len().min(1000);
    pairs.into_iter().take(n).collect()
}

fn solution(points: &[[i64; 3]]) -> i64 {
    let pairs = get_shortest_10(points);

    let mut graph: Vec<Vec<usize>> = vec![Vec::new(); points.len()];

    for p in &pairs {
        graph[p.i].push(p.j);
        graph[p.j].push(p.i);
    }

    use std::collections::HashSet;
    let mut visited: HashSet<usize> = HashSet::new();
    let mut sizes: Vec<i64> = Vec::new();

    for start in 0..points.len() {
        if visited.contains(&start) {
            continue;
        }

        let mut stack: Vec<usize> = Vec::new();
        stack.push(start);

        let mut size: i64 = 0;

        while let Some(node) = stack.pop() {
            if visited.contains(&node) {
                continue;
            }
            visited.insert(node);
            size += 1;

            for &neighbor in &graph[node] {
                if !visited.contains(&neighbor) {
                    stack.push(neighbor);
                }
            }
        }
        sizes.push(size);
        println!("component starting at {} has size {}", start, size);
    }

    if sizes.len() < 3 {
        return 0;
    }
    sizes.sort_by(|a, b| b.cmp(a));

    sizes[0] * sizes[1] * sizes[2]
}

fn read_points_from_file(filename: &str, max_points: usize) -> io::Result<Vec<[i64; 3]>> {
    let file = File::open(filename)?;
    let reader = BufReader::new(file);

    let mut points: Vec<[i64; 3]> = Vec::new();

    for line_result in reader.lines() {
        if points.len() >= max_points {
            break;
        }

        let line = line_result?;
        let parts:Vec<&str> = line.split(',').collect();

        if parts.len() != 3 {
            continue;
        }

        let x = parts[0].trim().parse::<i64>().unwrap();
        let y = parts[1].trim().parse::<i64>().unwrap();
        let z = parts[2].trim().parse::<i64>().unwrap();

        points.push([x,y,z]);
    }
    Ok(points)
}

//this will show me if there are any errors. 
fn main() -> std::io::Result<()>{
    //going to change this into being an input... from .txt file...
    let points = read_points_from_file("input.txt", 1000)?;

    let ans = solution(&points);
    println!("solution = {}", ans);

    Ok(())
}
//This one will panic if the reading fails. 
/*fn main() {
    let points = read_points_from_file("input.txt", 1000).unwrap();
    let ans = solution(&points);
    println!("solution = {}", ans);
} */
