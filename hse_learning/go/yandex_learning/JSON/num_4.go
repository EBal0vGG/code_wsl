package main

import (
	"encoding/json"
	// "fmt"
	"io"
	// "bytes"
)

// type Student struct {
//     Name  string `json:"name"`
//     Grade int    `json:"grade"`
// }

func EncodeStudentsToWriter(w io.Writer, students []Student) error {
	encoder := json.NewEncoder(w)
	err := encoder.Encode(students)

	return err
}

// func main() {
// 	students := []Student{
//         {Name: "Alice", Grade: 7},
//         {Name: "Bob", Grade: 8},
//         {Name: "Charlie", Grade: 9},
//     }


// 	var buf bytes.Buffer

// 	fmt.Println(EncodeStudentsToWriter(&buf, students), buf.String())
// }
