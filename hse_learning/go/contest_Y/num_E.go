package main

import (
	"bufio"
	"fmt"
	"os"
	"strings"
	"unicode"
)

var digitToLetters = []string{
	"",     // 0
	"",     // 1
	"ABC",  // 2
	"DEF",  // 3
	"GHI",  // 4
	"JKL",  // 5
	"MNO",  // 6
	"PQRS", // 7
	"TUV",  // 8
	"WXYZ", // 9
}

func encodeWord(word string) string {
	var encoded strings.Builder
	for _, c := range word {
		c = unicode.ToUpper(c)
		for digit := 2; digit <= 9; digit++ {
			if strings.ContainsRune(digitToLetters[digit], c) {
				pos := strings.IndexRune(digitToLetters[digit], c)
				for i := 0; i <= pos; i++ {
					encoded.WriteByte(byte('0' + digit))
				}
				break
			}
		}
	}
	return encoded.String()
}

func decodeMessage(s string, encodedDictionary map[string]string) string {
	n := len(s)
	dp := make([]bool, n+1)
	dp[0] = true

	maxLen := 0
	for k := range encodedDictionary {
		if len(k) > maxLen {
			maxLen = len(k)
		}
	}

	for i := 0; i < n; i++ {
		if !dp[i] {
			continue
		}
		for length := 1; length <= maxLen && i+length <= n; length++ {
			sub := s[i : i+length]
			if _, ok := encodedDictionary[sub]; ok {
				dp[i+length] = true
			}
		}
	}

	if !dp[n] {
		return ""
	}

	var result []string
	i := n
	for i > 0 {
		found := false
		for length := 1; length <= maxLen && i-length >= 0; length++ {
			sub := s[i-length : i]
			if word, ok := encodedDictionary[sub]; ok && dp[i-length] {
				result = append([]string{word}, result...)
				i -= length
				found = true
				break
			}
		}
		if !found {
			return ""
		}
	}

	return strings.Join(result, " ")
}

func main() {
	scanner := bufio.NewScanner(os.Stdin)
	scanner.Scan()
	s := scanner.Text()

	scanner.Scan()
	var n int
	fmt.Sscanf(scanner.Text(), "%d", &n)

	encodedDictionary := make(map[string]string)
	for i := 0; i < n; i++ {
		scanner.Scan()
		word := scanner.Text()
		encodedWord := encodeWord(word)
		encodedDictionary[encodedWord] = word
	}

	result := decodeMessage(s, encodedDictionary)
	fmt.Println(result)
}
