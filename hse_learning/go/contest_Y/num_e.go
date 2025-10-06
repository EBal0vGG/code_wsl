package main

import (
	"bufio"
	"fmt"
	"os"
)

var (
	n, k int
	g    [][]int
	used []bool
	tin  []int
	low  []int
	timer int
	bridges [][2]int
)

func dfs(v, p int) {
	used[v] = true
	tin[v] = timer
	low[v] = timer
	timer++
	for _, to := range g[v] {
		if to == p {
			continue
		}
		if used[to] {
			if low[v] > tin[to] {
				low[v] = tin[to]
			}
		} else {
			dfs(to, v)
			if low[v] > low[to] {
				low[v] = low[to]
			}
			if low[to] > tin[v] {
				if v < to {
					bridges = append(bridges, [2]int{v, to})
				} else {
					bridges = append(bridges, [2]int{to, v})
				}
			}
		}
	}
}

func main() {
	in := bufio.NewReader(os.Stdin)
	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	fmt.Fscan(in, &n, &k)

	g = make([][]int, n+1)
	for i := 0; i < k; i++ {
		var u, v int
		fmt.Fscan(in, &u, &v)
		if u == v {
			continue
		}
		g[u] = append(g[u], v)
		g[v] = append(g[v], u)
	}

	used = make([]bool, n+1)
	tin = make([]int, n+1)
	low = make([]int, n+1)
	timer = 1
	bridges = make([][2]int, 0)

	for i := 1; i <= n; i++ {
		if !used[i] {
			dfs(i, -1)
		}
	}

	// Строим компоненты 2-edge-connected (без мостов)
	comp := make([]int, n+1)
	for i := range comp {
		comp[i] = -1
	}
	compNum := 0
	compVerts := make([][]int, n+1)

	var dfsComp func(v, c int)
	dfsComp = func(v, c int) {
		comp[v] = c
		compVerts[c] = append(compVerts[c], v)
		for _, to := range g[v] {
			if comp[to] != -1 {
				continue
			}
			// Проверяем, является ли ребро мостом
			isBridge := false
			a, b := v, to
			if a > b {
				a, b = b, a
			}
			for _, bridge := range bridges {
				if bridge[0] == a && bridge[1] == b {
					isBridge = true
					break
				}
			}
			if !isBridge {
				dfsComp(to, c)
			}
		}
	}

	for i := 1; i <= n; i++ {
		if comp[i] == -1 {
			dfsComp(i, compNum)
			compNum++
		}
	}

	// Строим дерево компонент
	tree := make([][]int, compNum)
	compDegree := make([]int, compNum)
	
	for _, bridge := range bridges {
		u := comp[bridge[0]]
		v := comp[bridge[1]]
		tree[u] = append(tree[u], v)
		tree[v] = append(tree[v], u)
		compDegree[u]++
		compDegree[v]++
	}

	// Находим листья дерева (компоненты со степенью 1)
	leaves := []int{}
	for i := 0; i < compNum; i++ {
		if compDegree[i] == 1 || compDegree[i] == 0 {
			leaves = append(leaves, i)
		}
	}

	// Если только одна компонента - ничего не делаем
	if len(leaves) <= 1 {
		fmt.Fprintln(out, 0)
		return
	}

	// Соединяем листья попарно
	result := [][2]int{}
	
	// Функция для нахождения подходящей пары вершин
	findConnection := func(compA, compB int) (int, int) {
		// Берем первую вершину из каждой компоненты
		return compVerts[compA][0], compVerts[compB][0]
	}

	// Соединяем листья попарно
	for i := 0; i < len(leaves)-1; i += 2 {
		a, b := findConnection(leaves[i], leaves[i+1])
		result = append(result, [2]int{a, b})
	}

	// Если нечетное количество листьев, соединяем последний с предпоследним
	if len(leaves)%2 == 1 {
		a, b := findConnection(leaves[len(leaves)-1], leaves[len(leaves)-2])
		result = append(result, [2]int{a, b})
	}

	// Вывод результата
	fmt.Fprintln(out, len(result))
	for _, pair := range result {
		fmt.Fprintln(out, pair[0], pair[1])
	}
}