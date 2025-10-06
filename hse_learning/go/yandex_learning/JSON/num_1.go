package main

import (
    "encoding/json"
	// "fmt"
)

func SerializeIntSlice(nums []int) ([]byte, error) {
	res, err:= json.Marshal(nums)
	return res, err
}

// func main() {
// 	result, err := SerializeIntSlice([]int{1, 2, 3, 4, 6})
// 	if err != nil {
// 		fmt.Println(err)
// 		return
// 	}
// 	fmt.Println(result)
// }