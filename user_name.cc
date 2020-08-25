#include <napi.h>

#ifndef UNICODE
#define UNICODE
#endif
#pragma comment(lib, "netapi32.lib")

#include <stdio.h>
#include <assert.h>
#include <windows.h>
#include <lm.h>

Napi::Array UserNames(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Array arr = Napi::Array::New(env);

//******************

   LPUSER_INFO_0 pBuf = NULL;
   LPUSER_INFO_0 pTmpBuf;
   DWORD dwLevel = 0;
   DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwResumeHandle = 0;
   DWORD i;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   do
   {
      nStatus = NetUserEnum((LPCWSTR) pszServerName,
                            dwLevel,
                            FILTER_NORMAL_ACCOUNT, // global users
                            (LPBYTE*)&pBuf,
                            dwPrefMaxLen,
                            &dwEntriesRead,
                            &dwTotalEntries,
                            &dwResumeHandle);

      if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
      {
         if ((pTmpBuf = pBuf) != NULL)
         {
            for (i = 0; (i < dwEntriesRead); i++)
            {
               assert(pTmpBuf != NULL);

               if (pTmpBuf == NULL)
               {
                  break;
               }
               //
               arr[i] = Napi::String::New(env, (const char16_t *) pTmpBuf->usri0_name);
               //
               pTmpBuf++;
            }
         }
      }
      if (pBuf != NULL)
      {
         NetApiBufferFree(pBuf);
         pBuf = NULL;
      }
   }
   while (nStatus == ERROR_MORE_DATA);
   if (pBuf != NULL)
      NetApiBufferFree(pBuf);

//******************

  return arr;
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "userNames"), Napi::Function::New(env, UserNames));
    return exports;
};

NODE_API_MODULE(user_name, init);
