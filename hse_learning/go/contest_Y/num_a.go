package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	in := bufio.NewReader(os.Stdin)

	var n, m int
	if _, err := fmt.Fscan(in, &n, &m); err != nil {
		return
	}

	val := make([]int64, n)
	for i := 0; i < n; i++ {
		fmt.Fscan(in, &val[i])
	}

	// список смежности
	adj := make([][]int, n)
	for i := 0; i < m; i++ {
		var a, b int
		fmt.Fscan(in, &a, &b)
		a--
		b--
		adj[a] = append(adj[a], b)
		adj[b] = append(adj[b], a)
	}

	// dp[mask][u] упакуем в один срез
	totalMasks := 1 << n
	negInf := int64(-1 << 60)
	dp := make([]int64, totalMasks*n)
	for i := range dp {
		dp[i] = negInf
	}
	idx := func(mask, u int) int { return mask*n + u }

	startMask := 1 << 0 // начинаем обязательно с острова 1 (индекс 0)
	dp[idx(startMask, 0)] = val[0]

	var ans int64 = val[0]

	for mask := 0; mask < totalMasks; mask++ {
		// рассматриваем только подмножества, содержащие стартовую вершину
		if (mask & 1) == 0 {
			continue
		}
		for u := 0; u < n; u++ {
			cur := dp[idx(mask, u)]
			if cur == negInf {
				continue
			}
			// можно завершить тут
			if cur > ans {
				ans = cur
			}
			// идём к ещё не посещённым соседям
			for _, w := range adj[u] {
				if (mask>>w)&1 == 1 {
					continue
				}
				nm := mask | (1 << w)
				ni := idx(nm, w)
				newVal := cur + val[w]
				if newVal > dp[ni] {
					dp[ni] = newVal
				}
			}
		}
	}

	fmt.Println(ans)
}
