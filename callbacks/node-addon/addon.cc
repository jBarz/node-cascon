#include <node.h>
#include <v8.h>

using namespace v8;

void RunCallback(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  Local<Function> cb = Local<Function>::Cast(args[0]);
  const unsigned argc = 1;
  Local<Value> argv[argc] = { String::NewFromUtf8(isolate, "hello world") };
  cb->Call(isolate->GetCurrentContext()->Global(), argc, argv);
}

void Init(Handle<Object> exports, Handle<Object> module) {
  Isolate* isolate = Isolate::GetCurrent();
  exports->Set(String::NewFromUtf8(isolate, "callback"), 
               FunctionTemplate::New(isolate, RunCallback)->GetFunction());
}

NODE_MODULE(addon, Init)
