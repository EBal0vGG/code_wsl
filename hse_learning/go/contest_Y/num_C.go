package main

import (
	"fmt"
	"sort"
)

type Taxi struct {
	lastTimestamp int64
	position      int
}

func main() {
	var N, L, S int
	if _, err := fmt.Scan(&N, &L, &S); err != nil {
		panic(err)
	}

	taxis := make(map[int]Taxi)
	orderResults := make([][]int, 0)

	for i := 0; i < N; i++ {
		var typ string
		var timestamp int64
		if _, err := fmt.Scan(&typ, &timestamp); err != nil {
			panic(err)
		}

		if typ == "TAXI" {
			var taxiId, position int
			if _, err := fmt.Scan(&taxiId, &position); err != nil {
				panic(err)
			}
			taxis[taxiId] = Taxi{lastTimestamp: timestamp, position: position}
		} else if typ == "ORDER" {
			var orderId int
			var orderPosition, orderTime int
			if _, err := fmt.Scan(&orderId, &orderPosition, &orderTime); err != nil {
				panic(err)
			}
			_ = orderId // чтобы избежать ошибки «declared and not used»

			availableTaxis := make([]int, 0)
			for taxiId, taxi := range taxis {
				timeDiff := timestamp - taxi.lastTimestamp
				maxDistance := timeDiff * int64(S)
				minPos := taxi.position
				maxPos := (taxi.position + int(maxDistance)) % L

				var isIn bool
				if minPos <= maxPos {
					isIn = minPos <= orderPosition && orderPosition < maxPos
				} else {
					isIn = orderPosition >= minPos || orderPosition < maxPos
				}

				var worstPosition int
				if maxDistance >= int64(L) {
					worstPosition = (orderPosition + 1) % L
				} else {
					if isIn {
						worstPosition = (orderPosition + 1) % L
					} else {
						worstPosition = minPos
					}
				}

				distance := (orderPosition - worstPosition + L) % L

				if distance <= orderTime*S {
					availableTaxis = append(availableTaxis, taxiId)
				}
			}

			if len(availableTaxis) == 0 {
				orderResults = append(orderResults, []int{-1})
			} else {
				sort.Ints(availableTaxis)
				if len(availableTaxis) > 5 {
					availableTaxis = availableTaxis[:5]
				}
				orderResults = append(orderResults, availableTaxis)
			}
		}
	}

	for _, result := range orderResults {
		for i, val := range result {
			if i > 0 {
				fmt.Print(" ")
			}
			fmt.Print(val)
		}
		fmt.Println()
	}
}
