package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func getArr(line string, start int) []int64 {
	var arr []int64
	for _, v := range strings.Split(line[start:], " ") {
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
	seeds := getArr(scanner.Text(), 7)

	fmt.Println(seeds)
	scanner.Scan()

	for scanner.Scan() {

		vis := make([]bool, len(seeds))
		for line := " "; line != ""; line = scanner.Text() {

			if line != " " {
				row := getArr(line, 0)
				// fmt.Println(row)

				for i := range seeds {
					if !vis[i] && row[1] <= seeds[i] && seeds[i] <= row[1]+row[2] {
						vis[i] = true
						// fmt.Println(seeds[i], row)
						seeds[i] = row[0] + (seeds[i] - row[1])
					}
				}
			}
			scanner.Scan()
		}
		fmt.Println()
		fmt.Println(seeds)
		fmt.Println()
	}
	min := math.MaxInt64
	for _, seed := range seeds {
		min = int(math.Min(float64(min), float64(seed)))
	}
    fmt.Println(min)
}
