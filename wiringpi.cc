#include <node.h>
#include <wiringPi.h>

using v8::Exception;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::String;
using v8::Value;

void Get_Num_Pins(const FunctionCallbackInfo<Value>& args) {
    args.GetReturnValue().Set(Number::New(isolate, NUM_PINS));
}

void WiringPi_Setup(const FunctionCallbackInfo<Value>& args){
    Isolate* isolate = args.GetIsolate();
    
    if( -1 == wiringPiSetup() ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Bad argument type")));
        return;
    }
}

void Pin_Mode(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    
    if( args.Length() != 2 ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    if( !args[0]->IsNumber() || !args[1]->IsNumber() ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Bad arguments")));
        return;
    }
    
    if( ( args[0]->NumberValue() < 0 ) || ( args[0]->NumberValue() >= NUM_PINS ) ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Index out of bounds")));
        return;
    }
    
    pinMode( args[0]->NumberValue(), args[1]->NumberValue() );
}


void Digital_Write(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    
    if( args.Length() != 2 ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
        return;
    }
    
    if( !args[0]->IsNumber() || !args[1]->IsNumber() ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Bad argument")));
        return;
    }
    
    if( ( args[0]->NumberValue() < 0 ) || ( args[0]->NumberValue() >= NUM_PINS ) ) {
        isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Index out of bounds")));
        return;
    }
    
    digitalWrite( args[0]->NumberValue(), args[1]->NumberValue() );
}

Local<Object> Mode_Constant(){
    Isolate* isolate = Isolate::GetCurrent();
    Local<Object> obj = Object::New(isolate);
    
    obj->Set(String::NewFromUtf8(isolate, "OUTPUT"), Number::New(isolate, OUTPUT));
    obj->Set(String::NewFromUtf8(isolate, "INPUT"), Number::New(isolate, INPUT));
    
    return obj;
}


Local<Object> Value_Constant(){
    Isolate* isolate = Isolate::GetCurrent();
    Local<Object> obj = Object::New(isolate);
    
    obj->Set(String::NewFromUtf8(isolate, "HIGH"), Number::New(isolate, HIGH));
    obj->Set(String::NewFromUtf8(isolate, "LOW"), Number::New(isolate, LOW));
    
    return obj;
}

void Init(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(exports, "getNumPins", Get_Num_Pins);
    NODE_SET_METHOD(exports, "setup", WiringPi_Setup);
    NODE_SET_METHOD(exports, "pinMode", Pin_Mode);
    NODE_SET_METHOD(exports, "digitalWrite", Digital_Write);
    
    exports->Set(String::NewFromUtf8(isolate, "mode"), Mode_Constant());
    exports->Set(String::NewFromUtf8(isolate, "value"), Value_Constant());
}

NODE_MODULE(wiringpi, Init)
