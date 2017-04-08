/*
This is a binding written in c++ which can be called by NodeJS code. This binding can then wrap normal C functions
in order to connect NodeJS with C libraries
*/

#include <node.h>

namespace demo {

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Method(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "world"));
}

void init(Local<Object> exports) {
  // Adds the method "Method" which can be called by myaddon.hello()
  NODE_SET_METHOD(exports, "hello", Method);
}
/*
  myaddon is the module name this addon will have. It can be used by something like
  const myAddon = require('./build/Release/myaddon');
*/
NODE_MODULE(myaddon, init)
}  // namespace demo