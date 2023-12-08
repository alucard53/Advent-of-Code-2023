use std::collections::HashMap;
use std::fs;
use std::mem::drop;

// removed whitespaces, brackets, equal, signs and commas from input(vim hax)
//
fn main() {
    let input: Vec<String> = fs::read_to_string("input.txt")
        .unwrap()
        .lines()
        .map(|a| a.to_string())
        .collect();

    let dirs = input[0].clone();

    let mut map: HashMap<String, [String; 2]> = HashMap::new();

    for i in 2..input.len() {
        let line: Vec<String> = (&input[i]).split(" ").map(|i| i.to_string()).collect();

        map.insert(line[0].clone(), [line[1].clone(), line[2].clone()]);
    }

    drop(input);

    let start = String::from("AAA");
    let mut pos = &start;
    let mut moves: usize = 0;

    while pos != "ZZZ" {
        for i in dirs.chars() {
            if i == 'L' {
                pos = &map.get(pos).unwrap()[0];
            } else {
                pos = &map.get(pos).unwrap()[1];
            }
            moves += 1;
        }
    }
    println!("{moves}");
}
