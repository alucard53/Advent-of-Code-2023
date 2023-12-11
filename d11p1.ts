import { readFileSync } from "fs"

var input = readFileSync("input.txt", "utf8").split("\n").map(i => i.trim())
input.pop()

let count = 0;

for (let i = 0; i < input.length; i++) {
    if (!input[i].includes("#")) {
        i++
        input = [...input.slice(0, i), ".".repeat(input[0].length), ...input.slice(i)]
    }
}

for (const i of input) {
    console.log(i)
}

for (let j = 0; j < input[0].length; j++) {
    let found = false
    for (let i = 0; i < input.length; i++) {
        if (input[i][j] == '#') {
            found = true;
            break;
        }
    }
    if (!found) {
        count++
        input.forEach((s, i) => {
            // console.log(i)
            input[i] = s.slice(0, j) + "." + s.slice(j)
        })
        j++
    }
}

for (const i of input) {
    console.log(i)
}

let sum = 0
for (let i = 0; i < input.length; i++) {

    for (let x = 0; x < input[0].length; x++) {

        if (input[i][x] === "#") {

            for (let j = i; j < input.length; j++) {

                for (let y = (j === i ? (x + 1) : 0); y < input[0].length; y++) {

                    if (input[j][y] == "#") {
                        sum += Math.abs(i - j) + Math.abs(x - y)
                    }
                }
            }
        }
    }
}
console.log(sum)
