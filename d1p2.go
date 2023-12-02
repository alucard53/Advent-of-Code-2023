package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
)

func is_digit(c byte) bool {
	return 48 <= c && c <= 57
}

func is_digit_text(s string) int {
	if strings.Contains(s, "one") {
		return 1
	}
	if strings.Contains(s, "two") {
		return 2
	}
	if strings.Contains(s, "three") {
		return 3
	}
	if strings.Contains(s, "four") {
		return 4
	}
	if strings.Contains(s, "five") {
		return 5
	}
	if strings.Contains(s, "six") {
		return 6
	}
	if strings.Contains(s, "seven") {
		return 7
	}
	if strings.Contains(s, "eight") {
		return 8
	}
	if strings.Contains(s, "nine") {
		return 9
	}
	return 0
}

func main() {
	f, err := os.Open("input.txt")
	if err != nil {
		return
	}
	defer f.Close()

	scanner := bufio.NewScanner(f)
	sum := 0
	for scanner.Scan() {
		line := scanner.Text()
		fmt.Println(line)
		n := 0
		s := ""

		for i := 0; i < len(line); i++ {
			if is_digit(line[i]) {
				n = (int(line[i]) - 48) * 10
				break
			}
			s = s + string(line[i])
			is_digit := is_digit_text(s)
			if is_digit > 0 {
				n = is_digit * 10
				break
			}
		}

		s = ""
		for i := len(line) - 1; i >= 0; i-- {
			if is_digit(line[i]) {
				n += int(line[i]) - 48
				break
			}
			s = string(line[i]) + s
			is_digit := is_digit_text(s)
			if is_digit > 0 {
				n += is_digit
				break
			}
		}
		fmt.Println(n)
		sum += n
	}
	fmt.Println(sum)
}
