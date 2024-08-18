#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include <dlfcn.h>

PG_MODULE_MAGIC;

PG_FUNCTION_INFO_V1(currency_convert);

Datum
currency_convert(PG_FUNCTION_ARGS)
{
   text     currency = PG_GETARG_TEXT(0);
   float4   input_currency = PG_GETARG_FLOAT4(0);
   void *handle;
   handle = dlopen ("/home/up56/currconv-ext/libgetconv.so", RTLD_NOW | RTLD_GLOBAL);
   if (!handle) {
      fputs (dlerror(), stderr);
      exit(1);
   }
   char*(*getbody)(char*) = dlsym(handle, "GetBody");
   char* body = getbody(text_to_cstring(currency));
   PG_RETURN_TEXT_P(cstring_to_text(body));
}
