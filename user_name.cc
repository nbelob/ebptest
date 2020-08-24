#include <napi.h>

Napi::Array UserNames(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Array arr = Napi::Array::New(env, 3);

  arr[1] = Napi::String::New(env, "User1");
  arr[2] = Napi::String::New(env, "Имя2");
  arr[3] = Napi::String::New(env, "User три");

  return arr;
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "userNames"), Napi::Function::New(env, UserNames));
    return exports;
};

NODE_API_MODULE(user_name, init);
