use std::collections::HashMap;
use std::fs;
use std::mem::drop;

// removed whitespaces, brackets, equal, signs and commas from input(vim hax)

fn is_start(s: &str) -> bool {
    s.chars().last() == Some('A')
}
fn is_end(s: &str) -> bool {
    s.chars().last() == Some('Z')
}

fn get_loop<'a>(map: &'a HashMap<&'a str, [&'a str; 2]>, dirs: &'a str, mut pos: &'a str) -> i32 {
    let mut moves = 0;
    loop {
        for i in dirs.chars() {
            if i == 'L' {
                pos = map.get(pos).unwrap()[0];
            } else {
                pos = &map.get(pos).unwrap()[1];
            }
            moves += 1;
            if is_end(pos) {
                return moves;
            }
        }
    }
}

fn main() {
    let content = fs::read_to_string("input.txt").unwrap();
    let input: Vec<&str> = content.lines().collect();

    let dirs = input[0];

    let mut map: HashMap<&str, [&str; 2]> = HashMap::new();

    let mut pos: Vec<&str> = Vec::new();

    for i in 2..input.len() {
        let line: Vec<&str> = (&input[i]).split(" ").collect();

        if is_start(&line[0]) {
            pos.push(line[0]);
        }

        map.insert(line[0], [line[1], line[2]]);
    }

    drop(input);

    for i in pos.iter() {
        print!("{}, ", get_loop(&map, &dirs, i));
    }
    // https://www.calculator.net/lcm-calculator.html
    // lmao
}
