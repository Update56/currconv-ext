package main

import (
	"C"
	"fmt"
	"net/http"
	"unsafe"
)

//export GetBody
func GetBody(api_body *C.char, currency *C.char) {

	var body string
	curr := C.GoString(currency)

	url := fmt.Sprintf("https://v6.exchangerate-api.com/v6/831604053925ff6a3be209cc/latest/%s", curr)

	resp, err := http.Get(url)
	if err != nil {
		body = err.Error()
	}
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
