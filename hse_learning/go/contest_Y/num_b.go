package main

import (
	"bufio"
	"container/heap"
	"fmt"
	"os"
)

type Item struct {
	t int64 // время затопления
	x int
	y int
}
type PQ []Item

func (pq PQ) Len() int            { return len(pq) }
func (pq PQ) Less(i, j int) bool  { return pq[i].t < pq[j].t }
func (pq PQ) Swap(i, j int)       { pq[i], pq[j] = pq[j], pq[i] }
func (pq *PQ) Push(x interface{}) { *pq = append(*pq, x.(Item)) }
func (pq *PQ) Pop() interface{} {
	old := *pq
	n := len(old)
	it := old[n-1]
	*pq = old[:n-1]
	return it
}

func max(a, b int64) int64 {
	if a > b {
		return a
	}
	return b
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	var n, m int
	fmt.Fscan(in, &n, &m)

	h := make([][]int64, n)
	ans := make([][]int64, n)
	for i := range h {
		h[i] = make([]int64, m)
		ans[i] = make([]int64, m)
		for j := 0; j < m; j++ {
			fmt.Fscan(in, &h[i][j])
			ans[i][j] = 1 << 60 // "бесконечность"
		}
	}

	pq := &PQ{}
	heap.Init(pq)

	// все клетки с водой = стартовые
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if h[i][j] == 0 {
				ans[i][j] = 0
				heap.Push(pq, Item{0, i, j})
			}
		}
	}
	pushBoundary := func(i, j int) {
		if ans[i][j] > h[i][j] {
			ans[i][j] = h[i][j]
			heap.Push(pq, Item{h[i][j], i, j})
		}
	}
	for i := 0; i < n; i++ {
		pushBoundary(i, 0)
		if m > 1 {
			pushBoundary(i, m-1)
		}
	}
	for j := 0; j < m; j++ {
		pushBoundary(0, j)
		if n > 1 {
			pushBoundary(n-1, j)
		}
	}

	dx := [4]int{1, -1, 0, 0}
	dy := [4]int{0, 0, 1, -1}

	for pq.Len() > 0 {
		it := heap.Pop(pq).(Item)
		t, x, y := it.t, it.x, it.y
		if t != ans[x][y] {
			continue // устаревшее значение
		}
		for k := 0; k < 4; k++ {
			nx, ny := x+dx[k], y+dy[k]
			if nx < 0 || nx >= n || ny < 0 || ny >= m {
				continue
			}
			// Кандидат: max(время затопления текущей клетки, высота соседней клетки)
			cand := max(t, h[nx][ny])
			if cand < ans[nx][ny] {
				ans[nx][ny] = cand
				heap.Push(pq, Item{cand, nx, ny})
			}
		}
	}

	// вывод
	for i := 0; i < n; i++ {
		for j := 0; j < m; j++ {
			if j > 0 {
				fmt.Fprint(out, " ")
			}
			fmt.Fprint(out, ans[i][j])
		}
		fmt.Fprintln(out)
	}
}
