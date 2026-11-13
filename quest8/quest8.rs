#[derive(Debug)]
struct Pair {
    distance: i64,
    i: usize,
    j: usize,
}

fn dist_2(a: [i32; 3], b: [i32; 3]) -> i64 {
    let dx = (a[0] - b[0]) as i64;
    let dy = (a[1] - b[1]) as i64;
    let dz = (a[2] - b[2]) as i64;

    dx * dx + dy * dy + dz * dz
}

fn get_shortest_10(points: &[[i32; 3]]) -> Vec<Pair> {
    let mut pairs: Vec<Pair> = Vec::new();
    for i in 0..points.len() {
        for j in (i + 1)..points.len() {
            let d = dist_2(points[i], points[j]);
            pairs.push(Pair { distance: d, i, j });
        }
    }
    pairs.sort_by_key(|p| p.distance);

    for k in 0..pairs.len().min(10) {
        let p = &pairs[k];
        println!("distance = {}, i = {}, j = {}", p.distance, p.i, p.j);
    }

    let n = pairs.len().min(10);
    pairs.into_iter().take(n).collect()
}

fn solution(points: &[[i32; 3]]) -> i64 {
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

fn main() {
    let points: Vec<[i32; 3]> = vec![
        [162,817,812],
        [57,618,57],
        [906,360,560],
        [592,479,940],
        [352,342,300],
        [466,668,158],
        [542,29,236],
        [431,825,988],
        [739,650,466],
        [52,470,668],
        [216,146,977],
        [819,987,18],
        [117,168,530],
        [805,96,715],
        [346,949,466],
        [970,615,88],
        [941,993,340],
        [862,61,35],
        [984,92,344],
        [425,690,689],
    ];

    let ans = solution(&points);
    println!("solution = {}", ans);
}
