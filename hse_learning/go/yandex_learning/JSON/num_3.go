package main

import (
	"encoding/json"
	// "fmt"
	"io"
	// "strings"
)

type Student struct {
    Name  string `json:"name"`
    Grade int    `json:"grade"`
}

func DecodeStudentFromReader(r io.Reader) (Student, error) {
	decoder := json.NewDecoder(r)

	var student Student
	err := decoder.Decode(&student)

	return student, err
}

// func main() {
// 	jsonStr := `{"name": "John", "age": 30}`

// 	reader := strings.NewReader(jsonStr)

// 	fmt.Println(DecodeStudentFromReader(reader))
// }