package main

import (
	"C"
	"fmt"
	"net/http"
	"unsafe"
)

//export GetBody
func GetBody(api_body *C.char, currency *C.char) {
	//переменная для тела запроса
	var body string
	//переводим Си-строку с изначальной ввалютой в Go-строку
	curr := C.GoString(currency)
	//формируем запрсос
	url := fmt.Sprintf("https://v6.exchangerate-api.com/v6/831604053925ff6a3be209cc/latest/%s", curr)
	//посылаем запрос и проверяем на ошибки
	resp, err := http.Get(url)
	if err != nil {
		body = err.Error()
	}
	defer resp.Body.Close()
	//получаем запрос из входящего потока
	for {
		bs := make([]byte, 4096)
		n, err := resp.Body.Read(bs)
		body += string(bs[:n])
		if n == 0 || err != nil {
			break
		}
	}
	/*преобразовывеам Си-указатель в универсальный указатель Golang'a, тут же приводим его в массив байтов
	и копируем в него слайс с телом запроса + нулевой-символ*/
	copy((*[4096]byte)(unsafe.Pointer(api_body))[:], body+"\x00")
}
func main() {}
