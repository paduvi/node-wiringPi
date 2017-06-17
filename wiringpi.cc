#include <node.h>
#include <wiringPi.h>

namespace demo {

using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void Pin_Mode(const FunctionCallbackInfo<Value>& args) {
//  Isolate* isolate = args.GetIsolate();
//  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
  pinMode( args[0]->NumberValue(), args[1]->NumberValue() );
}


void Digital_Write(const FunctionCallbackInfo<Value>& args) {
//  Isolate* isolate = args.GetIsolate();
//  args.GetReturnValue().Set(String::NewFromUtf8(isolate, "hello world"));
  digitalWrite( args[0]->NumberValue(), args[1]->NumberValue() );
}

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Local<Object> obj = Object::New(isolate);

  // omit this to make it anonymous
  obj->Set(String::NewFromUtf8(isolate, "HIGH"), Number::New(isolate, HIGH));
  obj->Set(String::NewFromUtf8(isolate, "LOW"), Number::New(isolate, LOW));
  obj->Set(String::NewFromUtf8(isolate, "OUTPUT"), Number::New(isolate, OUTPUT));

  obj->Set(String::NewFromUtf8(isolate, "pin_mode"), FunctionTemplate::New(isolate, Pin_Mode)->GetFunction());
  obj->Set(String::NewFromUtf8(isolate, "digital_write"), FunctionTemplate::New(isolate, Digital_Write)->GetFunction());

  args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module) {
    if( -1 == wiringPiSetup() ) {
        ThrowException( Exception::TypeError( String::New( "Bad argument type" ) ) );
        return;
    }

    NODE_SET_METHOD(module, "exports", CreateObject);
}

NODE_MODULE(addon, Init)

}  // namespace demo