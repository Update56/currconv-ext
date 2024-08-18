package main

import (
	"C"
	"net/http"
	"unsafe"
)

//export GetBody
func GetBody(api_body *C.char) {
	var body string
	resp, _ := http.Get("https://v6.exchangerate-api.com/v6/831604053925ff6a3be209cc/latest/RUB")
	defer resp.Body.Close()
	for {
		bs := make([]byte, 4096)
		n, err := resp.Body.Read(bs)
		body += string(bs[:n])
		if n == 0 || err != nil {
			break
		}
	}
	copy((*[8192]byte)(unsafe.Pointer(api_body))[:], body+"\x00")
}
func main() {}
