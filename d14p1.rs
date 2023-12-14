use std::fs;

fn main() {
    let file = fs::read_to_string("input.txt").unwrap();
    let mut input: Vec<_> = file.lines().map(|l| l.to_string().into_bytes()).collect();

    let m = input.len();
    let n = input[0].len();

    for j in 0..n {
        let mut last: i32 = -1;
        for i in 0..m {
            if input[i][j] != '.' as u8 {
                if input[i][j] == 'O' as u8 && last + 1 != (i) as i32 {
                    (input[i][j], input[(last + 1) as usize][j]) = (input[(last + 1) as usize][j], input[i][j]);
                    last += 1;
                } else {
                    last = i as i32;
                }
            }
        }
    }

    let mut sum = 0;
    for j in 0..n {
        for i in 0..m {
            if input[i][j] == 'O' as u8 {
                sum += m - i;
            }
        }
    }
    println!("{sum}");
}
