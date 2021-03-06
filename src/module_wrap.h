#ifndef SRC_MODULE_WRAP_H_
#define SRC_MODULE_WRAP_H_

#if defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#include <unordered_map>
#include <string>
#include <vector>
#include "node_url.h"
#include "base_object-inl.h"
#include "node_external_refs.h"

namespace node {
namespace loader {

v8::Maybe<url::URL> Resolve(Environment* env,
                            const std::string& specifier,
                            const url::URL& base,
                            bool read_pkg_json = false);

class ModuleWrap : public BaseObject {
 public:
  static const std::string EXTENSIONS[];
  static void Initialize(v8::Local<v8::Object> target,
                         v8::Local<v8::Value> unused,
                         v8::Local<v8::Context> context);
  static void RegisterExternalReferences(ExternalReferenceRegister* reg);

 private:
  ModuleWrap(Environment* env,
             v8::Local<v8::Object> object,
             v8::Local<v8::Module> module,
             v8::Local<v8::String> url);
  ~ModuleWrap();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Link(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Instantiate(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Evaluate(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void Namespace(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void GetUrl(v8::Local<v8::String> property,
                     const v8::PropertyCallbackInfo<v8::Value>& info);
  static void Resolve(const v8::FunctionCallbackInfo<v8::Value>& args);
  static v8::MaybeLocal<v8::Module> ResolveCallback(
      v8::Local<v8::Context> context,
      v8::Local<v8::String> specifier,
      v8::Local<v8::Module> referrer);

  v8::Persistent<v8::Module> module_;
  v8::Persistent<v8::String> url_;
  bool linked_ = false;
  std::unordered_map<std::string, v8::Persistent<v8::Promise>> resolve_cache_;
};

}  // namespace loader
}  // namespace node

#endif  // defined(NODE_WANT_INTERNALS) && NODE_WANT_INTERNALS

#endif  // SRC_MODULE_WRAP_H_
