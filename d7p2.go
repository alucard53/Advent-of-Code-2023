package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

var chars = map[byte]int{
	'A': 13,
	'K': 12,
	'Q': 11,
	'T': 10,
	'9': 9,
	'8': 8,
	'7': 7,
	'6': 6,
	'5': 5,
	'4': 4,
	'3': 3,
	'2': 2,
	'J': 1,
}

type Hand struct {
	cards    string
	bid      int
	strength int
}

type Hands []Hand

func (h Hands) Len() int { return len(h) }

func (h Hands) Less(i int, j int) bool {
	if h[i].strength == h[j].strength {
		for c := 0; c < 5; c++ {
			if h[i].cards[c] != h[j].cards[c] {
				return chars[h[i].cards[c]] < chars[h[j].cards[c]]
			}
		}
	}
	return h[i].strength < h[j].strength
}

func (h Hands) Swap(i int, j int) { h[i], h[j] = h[j], h[i] }

func getStrength(hand string) int {
	cards := make(map[rune]int)

	for _, c := range hand {
		cards[c]++
	}

	counts := make([]int, 6)
	maxCard, maxCount := 'J', 0
	for card, count := range cards {
		counts[count]++
		if card != 'J' && count > maxCount {
			maxCount = count
			maxCard = card
		}
	}

	if maxCard != 'J' {
		counts[maxCount]--
		counts[maxCount+cards['J']]++
		counts[cards['J']]--
	}

	if counts[5] == 1 {
		return 7
	} else if counts[4] == 1 {
		return 6
	} else if counts[3] == 1 {
		if counts[2] == 1 {
			return 5
		} else {
			return 4
		}
	} else if counts[2] > 0 {
		return counts[2] + 1
	}
	return 1
}

func main() {
	for k, v := range chars {
		fmt.Printf("%c : %d\n", k, v)
	}
	f, err := os.Open("input.txt")

	if err != nil {
		fmt.Println(err)
		return
	}

	defer f.Close()
	scanner := bufio.NewScanner(f)

	var hands Hands

	for scanner.Scan() {
		line := strings.Split(scanner.Text(), " ")
		i, _ := strconv.Atoi(line[1])
		hands = append(hands, Hand{line[0], i, getStrength(line[0])})
	}

	sort.Sort(hands)

	var winnings int64 = 0
	for i, h := range hands {
		winnings += (int64(i+1) * int64(h.bid))
	}
	fmt.Println("Winnnings =", winnings)
}
