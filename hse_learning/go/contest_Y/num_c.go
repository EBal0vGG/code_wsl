package main

import (
	"bufio"
	"fmt"
	"os"
)

type DSU struct {
	p []int
	sz []int
}

func NewDSU(n int) *DSU {
	p := make([]int, n)
	sz := make([]int, n)
	for i := 0; i < n; i++ {
		p[i] = i
		sz[i] = 1
	}
	return &DSU{p, sz}
}

func (d *DSU) Find(x int) int {
	if d.p[x] != x {
		d.p[x] = d.Find(d.p[x])
	}
	return d.p[x]
}

func (d *DSU) Union(a, b int) {
	ra, rb := d.Find(a), d.Find(b)
	if ra == rb {
		return
	}
	if d.sz[ra] < d.sz[rb] {
		ra, rb = rb, ra
	}
	d.p[rb] = ra
	d.sz[ra] += d.sz[rb]
}

func main() {
	in := bufio.NewReader(os.Stdin)
	var n int
	fmt.Fscan(in, &n)

	// список слов для каждого запроса
	requestWords := make([][]string, n)

	// считываем запросы
	for i := 0; i < n; i++ {
		var m int
		fmt.Fscan(in, &m)
		words := make([]string, m)
		for j := 0; j < m; j++ {
			fmt.Fscan(in, &words[j])
		}
		requestWords[i] = words
	}

	dsu := NewDSU(n)
	wordToReq := make(map[string]int) // слово -> первый встретившийся запрос

	// связываем запросы по общим словам
	for i := 0; i < n; i++ {
		for _, w := range requestWords[i] {
			if prev, ok := wordToReq[w]; ok {
				dsu.Union(i, prev)
			} else {
				wordToReq[w] = i
			}
		}
	}

	// собираем слова по компонентам
	wordsInComp := make(map[int]map[string]struct{})
	for i := 0; i < n; i++ {
		root := dsu.Find(i)
		if wordsInComp[root] == nil {
			wordsInComp[root] = make(map[string]struct{})
		}
		for _, w := range requestWords[i] {
			wordsInComp[root][w] = struct{}{}
		}
	}

	// считаем ответ
	numContexts := len(wordsInComp)
	maxSize := 0
	for _, set := range wordsInComp {
		if len(set) > maxSize {
			maxSize = len(set)
		}
	}

	fmt.Printf("%d %d\n", numContexts, maxSize)
}
