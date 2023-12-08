use std::collections::HashMap;
use std::fs;
// removed whitespaces, brackets, equal, signs and commas from input(vim hax)
//
fn main() {
    let content = fs::read_to_string("input.txt").unwrap();
    let input: Vec<&str> = content.lines().collect();

    let dirs = input[0];

    let mut map: HashMap<&str, [&str; 2]> = HashMap::new();

    for i in 2..input.len() {
        let line: Vec<&str> = (&input[i]).split(" ").collect();

        map.insert(line[0], [line[1], line[2]]);
    }

    let mut pos = "AAA";
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
