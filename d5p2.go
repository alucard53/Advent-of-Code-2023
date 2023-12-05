package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func getArr(line string) []int64 {
	var arr []int64
	for _, v := range strings.Split(line, " ") {
		i, _ := strconv.Atoi(v)
		arr = append(arr, int64(i))
	}
	return arr
}

func main() {
	f, err := os.Open("input.txt")

	if err != nil {
		fmt.Println(err)
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)

	scanner.Scan()

	line := strings.Split(scanner.Text()[7:], " ")
	var seedRanges [][]int64
	for i := 0; i < len(line)-1; i += 2 {
		a, _ := strconv.Atoi(line[i])
		b, _ := strconv.Atoi(line[i+1])
		seedRanges = append(seedRanges, []int64{int64(a), int64(a + b - 1)})
	}
	fmt.Println(seedRanges)

	scanner.Scan()

	for scanner.Scan() {

		vis := make([]bool, len(seedRanges))

		for line := " "; line != ""; line = scanner.Text() {
			if line != " " {
				row := getArr(line)

				for i := 0; i < len(seedRanges); i++ {
					if vis[i] {
						continue
					}

					f := row[0] - row[1]

					if seedRanges[i][0] < row[1] && row[1]+row[2]-1 < seedRanges[i][1] {
						vis[i] = true
						vis = append(vis, false, false)
						seedRanges = append(seedRanges,
							[]int64{seedRanges[i][0], row[1] - 1})
						seedRanges = append(seedRanges,
							[]int64{row[1] + row[2], seedRanges[i][1]})
						seedRanges[i][0] = row[0]
						seedRanges[i][1] = row[0] + row[2] - 1

					} else if row[1] <= seedRanges[i][0] && seedRanges[i][1] <= row[1]+row[2]-1 {
						vis[i] = true
						seedRanges[i][0] = seedRanges[i][0] + f
						seedRanges[i][1] = seedRanges[i][1] + f

					} else if row[1] <= seedRanges[i][0] && seedRanges[i][0] <= row[1]+row[2]-1 {
						vis[i] = true
						vis = append(vis, false)
						seedRanges = append(seedRanges, []int64{row[1] + row[2], seedRanges[i][1]})
						seedRanges[i][0] = seedRanges[i][0] + f
						seedRanges[i][1] = row[0] + row[2] - 1

					} else if row[1] <= seedRanges[i][1] && seedRanges[i][1] <= row[1]+row[2]-1 {
						vis[i] = true
						vis = append(vis, false)

						seedRanges = append(seedRanges, []int64{seedRanges[i][0], row[1] - 1})
						seedRanges[i][0] = row[0]
						seedRanges[i][1] = seedRanges[i][1] + f
					}
				}
			}
			scanner.Scan()
		}

	}

	min := int64(math.MaxInt64)
	for _, v := range seedRanges {
		if v[0] < min {
			min = v[0]
		}
	}
	fmt.Println(min)
}
