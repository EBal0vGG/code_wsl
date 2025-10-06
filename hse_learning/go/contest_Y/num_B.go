package main

import (
	"fmt"
)

func main() {
	var N int
	fmt.Scan(&N)

	Q := make([]uint32, N)
	for i := 0; i < N; i++ {
		fmt.Scan(&Q[i])
	}

	C := make([]uint8, N)
	for i := 0; i < N; i++ {
		var tmp int
		fmt.Scan(&tmp)
		C[i] = uint8(tmp)
	}

	var A, B uint32
	fmt.Scan(&A, &B)

	var result uint64 = 0
	for i := 0; i < N; i++ {
		Di := A + (uint32(C[i])+1)*(B-A)/255
		result += uint64(Q[i]) * uint64(Di)
	}

	fmt.Println(result)
}
