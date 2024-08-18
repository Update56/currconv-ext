#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include <dlfcn.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(convert_from_rub);

Datum
convert_from_rub(PG_FUNCTION_ARGS)
{
   float4   input_currency = PG_GETARG_FLOAT4(0);
   char	   string[32];
   float    rates[3];

   void *handle;
   handle = dlopen ("/home/up56/currconv-ext/libgetconv.so", RTLD_NOW | RTLD_GLOBAL);
   if (!handle) {
      fputs (dlerror(), stderr);
      exit(1);
   }

   void(*getconv)(float[]) = dlsym(handle, "Getconv");
   getconv(rates);

   for (short int i = 0; i < 3; i++)
   {
      rates[i] = rates[i] * input_currency;
   }
   sprintf(string, "%f\n%f\n%f\n", rates[0], rates[1], rates[2]);
   PG_RETURN_TEXT_P(cstring_to_text(string));
}
