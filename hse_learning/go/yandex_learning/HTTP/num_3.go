package main

import (
	// "fmt"
	"strings"
	"strconv"
)

func ParseHTTPStatus(statusLine string) (code int, reason string) {
	parts := strings.SplitN(statusLine, " ", 3)
	code, _ = strconv.Atoi(parts[1])
	reason = parts[2]
	return code, reason
}

// func main() {
// 	fmt.Println(ParseHTTPStatus("HTTP/1.1 418 I'm a teapot"))
// }