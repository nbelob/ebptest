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

  int ia = 0;
  Napi::Array arr = Napi::Array::New(env, 15);

/*
  arr[ia++] = Napi::String::New(env, "User1");
  arr[ia++] = Napi::String::New(env, "Имя2");
  arr[ia++] = Napi::String::New(env, "User три");
*/

//******************

   LPUSER_INFO_0 pBuf = NULL;
   LPUSER_INFO_0 pTmpBuf;
   DWORD dwLevel = 0;
   DWORD dwPrefMaxLen = MAX_PREFERRED_LENGTH;
   DWORD dwEntriesRead = 0;
   DWORD dwTotalEntries = 0;
   DWORD dwResumeHandle = 0;
   DWORD i;
   DWORD dwTotalCount = 0;
   NET_API_STATUS nStatus;
   LPTSTR pszServerName = NULL;

   do // begin do
   {
      nStatus = NetUserEnum((LPCWSTR) pszServerName,
                            dwLevel,
                            FILTER_NORMAL_ACCOUNT, // global users
                            (LPBYTE*)&pBuf,
                            dwPrefMaxLen,
                            &dwEntriesRead,
                            &dwTotalEntries,
                            &dwResumeHandle);
      //
      // If the call succeeds,
      //
      if ((nStatus == NERR_Success) || (nStatus == ERROR_MORE_DATA))
      {
         if ((pTmpBuf = pBuf) != NULL)
         {
            //
            // Loop through the entries.
            //
            for (i = 0; (i < dwEntriesRead); i++)
            {
               assert(pTmpBuf != NULL);

               if (pTmpBuf == NULL)
               {
                  //fprintf(stderr, "An access violation has occurred\n");
                  break;
               }
               //
               //  Print the name of the user account.
               //
               //wprintf(L"\t-- %s\n", pTmpBuf->usri0_name);

               //--
               arr[ia++] = Napi::String::New(env, (const char16_t *) pTmpBuf->usri0_name);
               //--

               pTmpBuf++;
               dwTotalCount++;
            }
         }
      }
      //
      // Free the allocated buffer.
      //
      if (pBuf != NULL)
      {
         NetApiBufferFree(pBuf);
         pBuf = NULL;
      }
   }
   // Continue to call NetUserEnum while
   //  there are more entries.
   //
   while (nStatus == ERROR_MORE_DATA); // end do
   //
   // Check again for allocated memory.
   //
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
