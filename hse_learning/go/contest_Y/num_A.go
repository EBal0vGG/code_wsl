package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	var n, m, x, y int
	fmt.Scan(&n, &m, &x, &y)

	reader := bufio.NewReader(os.Stdin)
	windows := make([][]byte, n*x)

	for i := 0; i < n*x; i++ {
		line, _ := reader.ReadString('\n')
		windows[i] = []byte(line[:len(line)-1])
	}

	ans := 0

	for floor := 0; floor < n; floor++ {
		startRow := floor * x
		for apt := 0; apt < m; apt++ {
			startCol := apt * y
			light := 0

			for i := 0; i < x; i++ {
				for j := 0; j < y; j++ {
					ch := windows[startRow+i][startCol+j]
					if ch == 'X' {
						light++
					}
				}
			}

			if light*2 >= x*y {
				ans++
			}
		}
	}

	fmt.Println(ans)
}
