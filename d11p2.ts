import { readFileSync } from "fs"

var input = readFileSync("input.txt", "utf8").split("\n").map(i => i.trim())
input.pop()

const emptyRows: number[] = []
const emptyCols: number[] = []

input.forEach((line, i) => {
    if (!line.includes("#")) {
        emptyRows.push(i)
    }
})

for (let j = 0; j < input[0].length; j++) {
    let found = false
    for (let i = 0; i < input.length; i++) {
        if (input[i][j] == '#') {
            found = true;
            break;
        }
    }
    if (!found) {
        emptyCols.push(j)
    }
}

let sum = 0
for (let i = 0; i < input.length; i++) {
    for (let x = 0; x < input[0].length; x++) {

        if (input[i][x] === "#") {

            for (let j = i; j < input.length; j++) {
                for (let y = (j === i ? (x + 1) : 0); y < input[0].length; y++) {

                    if (input[j][y] == "#") {
                        let x1 = Math.max(x, y)
                        let x2 = Math.min(x, y)

                        let g = getEmpty(emptyRows, i, j) * 999999
                        let f = getEmpty(emptyCols, x2, x1) * 999999

                        sum += (j + g - i) + (x1 + f - x2)
                    }
                }
            }
        }
    }
}

function getEmpty(arr: number[], l: number, r: number): number {
    let count = 0
    arr.forEach(i => count += l < i && i < r ? 1 : 0)
    return count
}
