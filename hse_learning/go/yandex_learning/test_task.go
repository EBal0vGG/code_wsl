package main

import (
	"context"
	"fmt"
	"sync"
)

type task struct {
	idx int
	val int
}

func ParallelMapCtx(ctx context.Context, inputs []int, fn func(int) int, workers int) ([]int, error) {
	if workers <= 0 {
		workers = 1
	}

	tasks := make(chan task)
	results := make([]int, len(inputs))
	var wg sync.WaitGroup

	// Запускаем пул воркеров
	for w := 0; w < workers; w++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for {
				select {
				case <-ctx.Done():
					return
				case t, ok := <-tasks:
					if !ok {
						return
					}
					res := fn(t.val)
					results[t.idx] = res
				}
			}
		}()
	}

	// Отправляем задания
	go func() {
		defer close(tasks)
		for i, v := range inputs {
			select {
			case <-ctx.Done():
				return
			case tasks <- task{idx: i, val: v}:
			}
		}
	}()

	// Ждём завершения
	wg.Wait()

	// Проверяем контекст
	if err := ctx.Err(); err != nil {
		return nil, err
	}

	return results, nil
}

// --- Пример использования ---
func main() {
	ctx := context.Background()
	inputs := []int{1, 2, 3, 4, 5}

	res, err := ParallelMapCtx(ctx, inputs, func(x int) int {
		return x * x
	}, 2)

	if err != nil {
		fmt.Println("Ошибка:", err)
		return
	}

	fmt.Println("Результат:", res) // [1 4 9 16 25]
}
