package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
)

func main() {
    reader := bufio.NewReader(os.Stdin)
    text, _ := reader.ReadString('\n')

    pairs := countCharPairs(text)

    if len(pairs) > 0 {
        mostFrequent := findMostFrequentPair(pairs)
        fmt.Println(mostFrequent)
    } else {
        fmt.Println("Нет подходящих пар для анализа.")
    }
}

func countCharPairs(text string) map[string]int {
    pairs := make(map[string]int)

    for i := 0; i < len(text)-1; i++ {
        if text[i] != ' ' && text[i+1] != ' ' {
            pair := text[i : i+2]
            pairs[pair]++
        }
    }

    return pairs
}

// findMostFrequentPair возвращает ключ (пару символов) с максимальным значением
func findMostFrequentPair(pairs map[string]int) string {
    var maxKey string
    maxValue := 0

    for k, v := range pairs {
        if v > maxValue {
            maxValue = v
            maxKey = k
        }
    }

    return maxKey
}
