# Library for use in the PostgreSQL extension
This library is created for education0entertainment purposes, to demonstrate the compatibility of C and Golang, and to check whether a library written in Golang will function in the PostgreSQL extension written with C functions.
The library is a currency converter. To get the current rate, the API service exchangerate-api.com is used. A GET request is sent with an api key and target currency. The request body is then returned to C.
# Библиотека для использования в расширении PostgreSQL
Эта библиотека создана в обучающе-развлекательных целях, для демонстрации совместимости Си и Golang, а также проверки, будет ли функционировать библиотека написанная на Golang в расширении PostgreSQL написанном с Си-функциями.
Библиотека представляет с собой конвертер валют. Для получения актуального курса, используется API-сервис exchangerate-api.com Посылается GET-запрос с api-ключом и целевой валютой. Далее тело запроса возрващается в Си.
