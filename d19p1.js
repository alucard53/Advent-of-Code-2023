import { readFileSync } from "fs";

var input = readFileSync('input.txt', 'utf8').split('\n\r').map(i => i.trim())

const workflows = new Map();

for (const i of input[0].split('\n').map(i => i.trimEnd())) {
    const j = i.indexOf('{')
    workflows.set(i.substring(0, j), i.substring(j + 1, i.length - 1).split(','))
}
console.log(workflows, '\n')

const partProperties = input[1].split('\n')
let count = 0
const selected = []

//vimmed the second part of the input into JSON
for (const p of partProperties) {
    const part = JSON.parse(p)

    let curr_workflow = 'in'
    let steps = workflows.get(curr_workflow);
    for (let i = 0; i < steps.length; i++) {
        if (steps[i].includes(':')) {
            const [condition, action] = steps[i].split(':')
            let prop, num
            if (condition.includes('<')) {
                [prop, num] = condition.split('<')
                if (part[prop] < Number(num)) {
                    if (action === 'A') {
                        count++
                        selected.push(part)
                        break
                    } if (action === 'R') {
                        break
                    }
                    i = -1
                    steps = workflows.get(action)
                    curr_workflow = action
                }
            } else {
                [prop, num] = condition.split('>')
                if (part[prop] > Number(num)) {
                    if (action === 'A') {
                        selected.push(part)
                        count++
                        break
                    } if (action === 'R') {
                        break
                    }
                    i = -1
                    steps = workflows.get(action)
                    curr_workflow = action
                }

            }
        } else {
            if (steps[i] === 'A') {
                selected.push(part)
                count++
                break
            } if (steps[i] === 'R') {
                break
            }
            curr_workflow = steps[i]
            steps = workflows.get(steps[i])
            i = -1
        }
    }
}
console.log(count)
console.log(selected)
let sum = 0
for (const i of selected) {
    for (const j in i) {
        sum += i[j]
    }
}
console.log(sum)
