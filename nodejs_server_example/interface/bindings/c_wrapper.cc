#include <node.h>
#include <iostream>

// include libtest header file (libtest is written in c and compiled into libmytest.a which is declared in binding.gyp)
extern "C" {
    #include "/Users/Giorgio/Documents/GSoC/gsoc-preparation/static_lib/libtest.h"
}

namespace demo {

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void IHello(const FunctionCallbackInfo<Value>& args) {
    printHello();
}

// This is the implementation of the "add" method
// Input arguments are passed using the
// const FunctionCallbackInfo<Value>& args struct
void IAdd(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  // Check the number of arguments passed.
  if (args.Length() < 2) {
    // Throw an Error that is passed back to JavaScript
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong number of arguments")));
    return;
  }

  // Check the argument types
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // Perform the operation
  int value = add(args[0]->NumberValue(), args[1]->NumberValue());
  Local<Number> num = Number::New(isolate, value);

  // Set the return value (using the passed in
  // FunctionCallbackInfo<Value>&)
  args.GetReturnValue().Set(num);
}

void IMult2(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 1) {
      // Throw an Error that is passed back to JavaScript
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
    }

    // Check the argument types
    if (!args[0]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong arguments")));
      return;
    }

    // Perform the operation
    int value = args[0]->NumberValue();
    multiplyWith2(&value);
    Local<Number> num = Number::New(isolate, value);

    // Set the return value (using the passed in
    // FunctionCallbackInfo<Value>&)
    args.GetReturnValue().Set(num);
}
extern "C" void dummy(char*, void* const);
void dummy(char* value, void* ar){

    std::cout << ar << "\n";
    const FunctionCallbackInfo<Value>& args = (FunctionCallbackInfo<Value>&)ar;

    Isolate* isolate = args.GetIsolate();
    std::cout << "Iso:" << isolate << "\n";

    Local<Function> cb = Local<Function>::Cast(args[0]);
    std::cout << &args << "\n";

    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, value) };
    cb->Call(Null(isolate), argc, argv);
    std::cout << &args << "\n";
}

// this still has some issues
void IMakeCallback(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();

    // Check the number of arguments passed.
    if (args.Length() < 1) {
      // Throw an Error that is passed back to JavaScript
      isolate->ThrowException(Exception::TypeError(
          String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
    }

    std::cout << "Iso:" << isolate << "\n";
    std::cout << &args << "\n";
    void* ar = (void*)&args;
    std::cout << ar << "\n";

    registerObserver(&dummy, ar);
}

void Init(Local<Object> exports) {
  // declare all methods here
  NODE_SET_METHOD(exports, "printHello", IHello);
  NODE_SET_METHOD(exports, "add", IAdd);
  NODE_SET_METHOD(exports, "mul2", IMult2);
  // NODE_SET_METHOD(exports, "makeCallback", IMakeCallback);
}

NODE_MODULE(c_wrapper, Init)

}  // namespace demo