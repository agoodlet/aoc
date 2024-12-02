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

func checkDiff(a int, b int) (string, float64) {
	direction := "increasing"
	diff := a - b

	if diff < 0 {
		direction = "decreasing"
	}

	return direction, math.Abs(float64(diff))
}

func main() {
	file, err := os.Open("./data")
	check(err)
	defer file.Close()
	var safe int
	var unsafe int

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lastIter := ""
		charArray := strings.Fields(scanner.Text())
		numUnsafe := 0
		for i, char := range charArray {
			if i+1 < len(charArray) {
				charInt, err := strconv.Atoi(char)
				check(err)
				nextCharInt, err := strconv.Atoi(charArray[i+1])
				check(err)

				increasing, diff := checkDiff(charInt, nextCharInt)
				if diff < 1 || diff > 3 {
					numUnsafe++
					continue
				}

				// if increasing does not equal the previous iteration of increasing
				if lastIter != "" && lastIter != increasing {
					numUnsafe++
					continue
				}
				lastIter = increasing
			}
		}
		if numUnsafe > 1 {
			unsafe++
			fmt.Println("unsafe")
		} else {
			safe++
			fmt.Println("safe")
		}
	}

	fmt.Println(safe, unsafe)
}
