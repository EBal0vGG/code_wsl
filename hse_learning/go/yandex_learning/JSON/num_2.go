package main

import (
	"encoding/json" 
	// "fmt"
)

func DeserializeStringMap(data string) (map[string]string, error) {
	res_data := make(map[string]string)
	err := json.Unmarshal([]byte(data), &res_data)
	return res_data, err
}

// func main() {
// 	fmt.Println(DeserializeStringMap(`{"ffff": "11", "aaaa": "22"}`))
// }
