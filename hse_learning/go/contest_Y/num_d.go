package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n int
	fmt.Fscan(in, &n)

	h := make([]int, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &h[i])
	}

	res := make([]int, n)
	for i := range res {
		res[i] = -1
	}

	stackEven := []int{}
	stackOdd := []int{}

	for i := n - 1; i >= 0; i-- {
		if i%2 == 0 {
			// Чётные индексы
			for len(stackEven) > 0 && h[stackEven[len(stackEven)-1]] <= h[i] {
				stackEven = stackEven[:len(stackEven)-1]
			}
			if len(stackEven) > 0 {
				res[i] = stackEven[len(stackEven)-1] - i
			}
			stackEven = append(stackEven, i)
		} else {
			// Нечётные индексы
			for len(stackOdd) > 0 && h[stackOdd[len(stackOdd)-1]] <= h[i] {
				stackOdd = stackOdd[:len(stackOdd)-1]
			}
			if len(stackOdd) > 0 {
				res[i] = stackOdd[len(stackOdd)-1] - i
			}
			stackOdd = append(stackOdd, i)
		}
	}

	for i := 0; i < n; i++ {
		if i > 0 {
			fmt.Fprint(out, " ")
		}
		fmt.Fprint(out, res[i])
	}
	fmt.Fprintln(out)
}
