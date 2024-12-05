package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strconv"
	"strings"
)

func check(e error) {
	if e != nil {
		panic(e)
	}
}

func checkDiff(a int, b int) (string, int) {
	direction := "increasing"
	diff := a - b

	if diff < 0 {
		direction = "decreasing"
	}

	return direction, int(math.Abs(float64(diff)))
}

// take in an index and remove it from the array
func filter(list []string, index int) []string {
	list[index] = list[len(list)-1]
	return list[:len(list)-1]
}

// only run this fun on unsafe lists
func checkDampener(list []string) {
	for i := range list {
		newList := filter(list, i)
		// pass into func to determine if safe
		checkSafe(newList)
		// if any of these are now safe we can mark this as safe
	}
}

func checkSafe(list []string) bool {
	numUnsafe := 0
	lastIter := ""
	// loop through array
	for i, e := range list {
		if i+1 < len(list) {
			charInt, err := strconv.Atoi(e)
			check(err)
			nextCharInt, err := strconv.Atoi(list[i+1])
			check(err)

			// find diff between i and i+1
			increasing, diff := checkDiff(charInt, nextCharInt)

			// if all diffs are 0 > x > 3 we are safe
			if diff < 1 || diff > 3 {
				numUnsafe++
				continue
			}
			// if all diffs are positive we are safe
			// if all diffs are negative we are safe
			if lastIter != "" && lastIter != increasing {
				numUnsafe++
				continue
			}

			lastIter = increasing

		}
	}
	// otherwise we are unsafe
	return numUnsafe <= 0
}

func main() {
	file, err := os.Open("./testData")
	check(err)
	defer file.Close()
	var safe int
	var unsafe int

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		charArray := strings.Fields(scanner.Text())
		if !checkSafe(charArray) {
			unsafe++
			fmt.Println("unsafe")
		} else {
			safe++
			fmt.Println("safe")
		}
	}

	fmt.Println(safe, unsafe)
}
