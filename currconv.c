#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(currency_convert);

Datum
currency_convert(PG_FUNCTION_ARGS)
{
   text     *input_currency = PG_GETARG_TEXT_PP(0); //изначальная валюта
   text     *output_currency = PG_GETARG_TEXT_PP(1); //требуемая валюта
   float4   money = PG_GETARG_FLOAT4(2); //сумма денег

   char     api_body[4096]; //массив для тела запроса
   void     *handle; //указатель на начало библиотеки
   char     str_cur[8]; //вспомогательный массив (в.м.) с названием конечной валютой (нужен для парсинга) 
   char     *istr; //в.м. с обрезаным тело до нужной валюты (нужен для парсинга)
   char     floatchar [32]; //в.м. с числом в виде набора символов
   char     char_res [32]; //в.м. для вывода в виде текста

   //открываем библиотеку, по пути полученому из переменной окружения
   handle = dlopen (strcat(getenv("LD_LIBRARY_PATH"), "/postgresql/libgetconv.so"), RTLD_NOW | RTLD_GLOBAL);
   if (!handle) {
      fputs (dlerror(), stderr);
      exit(1);
   }
   //объявляем указатель на функцию
   void (*getbody) (char[], char[])= dlsym(handle, "GetBody");
   //вызываем go-функцию
   getbody(api_body, text_to_cstring(input_currency));
   
   //получаем массив с названием конечной валютой и знаками ( "USD": )
   sprintf(str_cur, "\"%s\":", text_to_cstring(output_currency));
   //побрезаем тело ответа до первого вхождения 
   istr = strstr(api_body, str_cur);
   
   //записываем числа валюты начиная с 6 элемента - чисел и до запятой ("USD":90.6483,")
   for (size_t i = 6 , j = 0; istr[i] != ','; i++, j++)
   {
      floatchar[j] = istr[i];
   }
   //переводим массив с цифрами в число, умножаем на входную число, сумма денег, и записываем в массив
   sprintf(char_res, "%f", atof(floatchar) * money);
   PG_RETURN_TEXT_P(cstring_to_text(char_res));
}