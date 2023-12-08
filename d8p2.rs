use std::collections::HashMap;
use std::fs;
use std::mem::{drop, take};

// removed whitespaces, brackets, equal, signs and commas from input(vim hax)
//
fn is_start(s: &String) -> bool {
    s.chars().last() == Some('A')
}
fn is_end(s: &String) -> bool {
    s.chars().last() == Some('Z')
}

fn get_loop<'a>(map: &'a HashMap<String, [String; 2]>, dirs: &String, mut pos: &'a String) -> i32 {
    let mut moves = 0;
    while !is_end(pos) {
        for i in dirs.chars() {
            if i == 'L' {
                pos = &map.get(pos).unwrap()[0];
            } else {
                pos = &map.get(pos).unwrap()[1];
            }
            if is_end(pos) {
                println!("{:?}", pos);
            }
            moves += 1;
        }
    }
    moves
}

fn main() {
    let input: Vec<String> = fs::read_to_string("input.txt")
        .unwrap()
        .lines()
        .map(|a| a.to_string())
        .collect();

    let dirs = input[0].clone();

    let mut map: HashMap<String, [String; 2]> = HashMap::new();

    let mut pos: Vec<String> = Vec::new();

    for i in 2..input.len() {
        let line: Vec<String> = (&input[i]).split(" ").map(|i| i.to_string()).collect();

        if is_start(&line[0]) {
            pos.push(line[0].clone());
        }

        map.insert(line[0].clone(), [line[1].clone(), line[2].clone()]);
    }

    drop(input);

    for i in pos.iter() {
        print!("{}, ", get_loop(&map, &dirs, i));
    }
    // https://www.calculator.net/lcm-calculator.html
    // lmao
}
