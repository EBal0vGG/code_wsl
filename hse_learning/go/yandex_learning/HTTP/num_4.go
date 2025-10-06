package main

import (
	"fmt"
	"strings"
)

func shellEscapeSingleQuotes(s string) string {
	return strings.ReplaceAll(s, "'", `'"'"'`)
}

func MakeCurlCommand(method, url, headers, body string) string {
	var parts []string
	parts = append(parts, "curl")

	if strings.ToUpper(method) != "GET" {
		parts = append(parts, "-X", method)
	}

	if headers != "" {
		lines := strings.Split(strings.TrimSpace(headers), "\n")
		for _, h := range lines {
			h = strings.TrimSpace(h)
			if h != "" {
				escaped := shellEscapeSingleQuotes(h)
				parts = append(parts, "-H", fmt.Sprintf("'%s'", escaped))
			}
		}
	}

	if body != "" {
		escaped := shellEscapeSingleQuotes(body)
		parts = append(parts, "--data", fmt.Sprintf("'%s'", escaped))
	}

	parts = append(parts, url)

	return strings.Join(parts, " ")
}

func main() {
	cmd := MakeCurlCommand(
		"POST",
		"https://example.com/api/users",
		"Content-Type: application/json\nAuthorization: Bearer abc123\n",
		`{"name":"John Doe","email":"johndoe@example.com","password":"123456"}`,
	)
	fmt.Println(cmd)
}
