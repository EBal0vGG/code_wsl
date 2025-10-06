package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Рекурсивная функция для генерации разбиений
func generatePartitions(n, max int, prefix []int, out *bufio.Writer) {
	if n == 0 {
		// Формируем строку из текущего разбиения
		parts := make([]string, len(prefix))
		for i, num := range prefix {
			parts[i] = strconv.Itoa(num)
		}
		// Печатаем в нужном формате
		out.WriteString(strings.Join(parts, " + ") + "\n")
		return
	}

	// Пробуем все возможные слагаемые от min(n, max) до 1
	for i := 1; i <= min(n, max); i++ {
		generatePartitions(n-i, i, append(prefix, i), out)
	}
}

func main() {
	// Чтение входного числа
	var n int
	fmt.Scan(&n)

	out := bufio.NewWriter(os.Stdout)
	defer out.Flush()

	generatePartitions(n, n, []int{}, out)
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}
