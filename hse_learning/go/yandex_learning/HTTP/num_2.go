package main

// import "fmt"

func  BuildHTTPResponse(statusLine, headers, body string) string {
	result := statusLine + "\r\n"
	result += headers
	result += "\r\n"
	result += body

	return result
}

// func main() {
// 	res_str := BuildHTTPResponse("HTTP/1.1 404 Not Found", 
// 								"Content-Type: text/html\r\nDate: Tue, 3 Jun 2025 19:00:00 GMT\r\n", 
// 								"<h1>Not Found</h1>")

// 	fmt.Println(res_str)
// }
