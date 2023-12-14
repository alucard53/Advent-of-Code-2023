use std::{collections::HashMap, fs};

fn tilt(input: &mut Vec<Vec<u8>>, m: usize, n: usize) {
    for j in 0..n {
        let mut last: i32 = -1;
        for i in 0..m {
            if input[i][j] != '.' as u8 {
                if input[i][j] == 'O' as u8 && last + 1 != i as i32 {
                    (input[i][j], input[(last + 1) as usize][j]) =
                        (input[(last + 1) as usize][j], input[i][j]);
                    last += 1;
                } else {
                    last = i as i32;
                }
            }
        }
    }
    for i in 0..m {
        let mut last: i32 = -1;
        for j in 0..n {
            if input[i][j] != '.' as u8 {
                if input[i][j] == 'O' as u8 && last + 1 != j as i32 {
                    (input[i][j], input[i][(last + 1) as usize]) =
                        (input[i][(last + 1) as usize], input[i][j]);
                    last += 1;
                } else {
                    last = j as i32;
                }
            }
        }
    }
    for j in 0..n {
        let mut last: i32 = m as i32;
        for i in (0..m).rev() {
            if input[i][j] != '.' as u8 {
                if input[i][j] == 'O' as u8 && last - 1 != i as i32 {
                    (input[i][j], input[(last - 1) as usize][j]) =
                        (input[(last - 1) as usize][j], input[i][j]);
                    last -= 1;
                } else {
                    last = i as i32;
                }
            }
        }
    }
    for i in 0..m {
        let mut last: i32 = n as i32;
        for j in (0..n).rev() {
            if input[i][j] != '.' as u8 {
                if input[i][j] == 'O' as u8 && last - 1 != (j) as i32 {
                    (input[i][j], input[i][(last - 1) as usize]) =
                        (input[i][(last - 1) as usize], input[i][j]);
                    last -= 1;
                } else {
                    last = j as i32;
                }
            }
        }
    }
}

fn main() {
    let file = fs::read_to_string("input.txt").unwrap();
    let mut input: Vec<_> = file.lines().map(|l| l.to_string().into_bytes()).collect();

    let m = input.len();
    let n = input[0].len();

    let mut sum = 0;

    let mut cycles: HashMap<usize, Vec<Vec<u8>>> = HashMap::new();
    let mut seen: HashMap<Vec<Vec<u8>>, usize> = HashMap::new();
    let mut found = 0;
    for i in 0..1000000000 {
        tilt(&mut input, m, n);
        if seen.contains_key(&input) {
            let first_seen = seen.get(&input).unwrap();
            found = ((1000000000 - i - 1) % (i - first_seen)) + first_seen;
            break;
        }
        seen.insert(input.clone(), i);
        cycles.insert(i, input.clone());
    }

    let final_cycle = cycles.get(&found).unwrap();

    for j in 0..n {
        for i in 0..m {
            if final_cycle[i][j] == 'O' as u8 {
                sum += m - i;
            }
        }
    }
    println!("{sum}");
}
