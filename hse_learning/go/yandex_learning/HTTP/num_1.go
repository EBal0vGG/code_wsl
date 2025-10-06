package main

// import "fmt"

func BuildHTTPRequest(method, url, host, headers, body string) string {
	result := method + " " + url + " HTTP/1.1\r\n"
	result += "Host: " + host + "\r\n"
	result += headers
	result += "\r\n"
	result += body

	return result
}

// func main() {
// 	res_str := BuildHTTPRequest("POST", "/api/users", "example.com",
//   								"Content-Type: application/json\r\nAuthorization: Bearer abc123\r\n",
//   								`{"name":"John Doe","email":"johndoe@example.com","password":"123456"}`)
// 	fmt.Println(res_str)
// }
