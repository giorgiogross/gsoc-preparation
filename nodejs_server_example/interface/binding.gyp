{
  "targets": [
    {
      "target_name": "myaddon",
      "sources": [ "bindings/hello.cc"]
    },
    {
      "target_name": "c_wrapper_addon",
      "sources": [ "bindings/c_wrapper.cc" ],
      "libraries": [ "/Users/Giorgio/Documents/GSoC/gsoc-preparation/static_lib/libmytest.a" ]
    }
  ]
}