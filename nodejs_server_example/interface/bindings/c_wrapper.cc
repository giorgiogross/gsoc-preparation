#include <nan.h> // remember to include the nan directory in the binding.gyp file
#include "../lib/exchange.h"

// include libtest header file (libtest is written in c and compiled into libmytest.a which is declared in binding.gyp)
extern "C" {
    #include "../lib/libtest.h"
}

using namespace Nan;
using namespace v8;

/*
Delegate calls to printHello()
*/
NAN_METHOD(IHello) {
  printHello();
}

/*
This is the delegation to the "add" method
Input arguments can be read using the info object

@param a        first value
@param b        second value
@return result
*/
NAN_METHOD(IAdd) {
  // error checking
  Nan::Maybe<int> v1 = Nan::To<int>(info[0]);
  Nan::Maybe<int> v2 = Nan::To<int>(info[0]);
  if(info.Length() < 2) {
          return;
  }

  // delegate call
  int res = add(v1.FromJust(), v2.FromJust());

  // return result
  Local<Number> resVal = Nan::New(res);
  info.GetReturnValue().Set(resVal);
}

/*
Delegates to multiplyWith2

@param a        pointer to the variable which will be doubled
@return void
*/
NAN_METHOD(IMult2) {
  // error checking
  Nan::Maybe<int> v1 = Nan::To<int>(info[0]);
  if(info.Length() < 1) {
          return;
  }

  // delegate call
  int val = v1.FromJust();
  multiplyWith2(&val);

  // return result
  Local<Number> resVal = Nan::New(val);
  info.GetReturnValue().Set(resVal);
}

/*
Synchronous callback.

@param callback     pointer to the Exchange object which will be called
*/
NAN_METHOD(IMakeCallback) {
    Nan:: HandleScope scope;

    v8::Local<v8::String> res = Nan::New<v8::String>("-").ToLocalChecked();

    Exchange x(
        [&](void * data) {
            res = Nan::New<v8::String>((char*)data).ToLocalChecked();
       });

    makeCallback((void*)&x);
    info.GetReturnValue().Set(res);
}

// Async worker to process async callbacks (e.g. registering and then calling observers)
class MyWorker : public AsyncWorker {
    public:
        MyWorker(Callback *callback) // init worker
        : AsyncWorker(callback) {}

        ~MyWorker() {}

        // called by libuv to dispatch the worker
        void Execute () {

            // this code is running in its own thread and is separated from the node code. That means JS can't access
            // our variables and we can't access JS variables. We manage now all our memory on our own.

            Exchange x(
                [&](void* data) {
                    result = (char*) data;
                }
            );

            // the "real" callback is the Exchange object, not the JS callback function! We call the exchange object's
            // functions when an event occurs. When we return Execute() ends and HandleOKCallback is called. There we
            // pass the parameters given to Exchange on to the JS callback function.
            doAsyncOperation((void*)&x);
        }

        // Called after the async worker finished. This function is then executed in the event loop
        void HandleOKCallback () {
            Nan:: HandleScope scope;

            v8::Local<v8::String> res = Nan::New<v8::String>(result).ToLocalChecked();
            Local<Value> argv[] = {
                res
            };

            callback->Call(1, argv);

        }
    private:
        char* result;
};

/*
Simple async callback.

@param callback     pointer to the Exchange object which will be called
*/
NAN_METHOD(IRegisterObserver) {
    Callback *callback = new Callback(info[0].As<Function>());

    AsyncQueueWorker(new MyWorker(callback));
}

/*
Declares the methods to be exported to JS.

@param Init         the init function
*/
NAN_MODULE_INIT(Init) {
  Nan::Set(target, New<String>("printHello").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(IHello)).ToLocalChecked());
  Nan::Set(target, New<String>("add").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(IAdd)).ToLocalChecked());
  Nan::Set(target, New<String>("mul2").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(IMult2)).ToLocalChecked());
  Nan::Set(target, New<String>("makeCallback").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(IMakeCallback)).ToLocalChecked());
  Nan::Set(target, New<String>("makeAsyncCallback").ToLocalChecked(),
      GetFunction(New<FunctionTemplate>(IRegisterObserver)).ToLocalChecked());
}

NODE_MODULE(c_wrapper_addon, Init)