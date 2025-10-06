package main

/*
Напишите функцию WriteToLogFile(message string, fileName string) error, 
которая пишет в указанный файл строку message. 
Если файл существует, строка должна быть добавлена, иначе создан новый файл.
*/

import (
	// "log"
	"os"
)

func WriteToLogFile(message string, fileName string) error {
    file, err := os.OpenFile(fileName, os.O_CREATE|os.O_WRONLY|os.O_APPEND, 0644)
    if err != nil {
        return err
    }
    defer file.Close()

    file.WriteString(message + "\n")

	return nil
}

// func main() {
// 	if err := WriteToLogFile("Error 2", "log_test.txt"); err != nil {
// 		log.Printf("%v\n", err)
// 		return
// 	}

// 	log.Println("Successfully")
// }