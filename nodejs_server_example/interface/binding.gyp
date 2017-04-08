{
  "targets": [
    {
      "target_name": "myaddon",
      "sources": [ "bindings/hello.cc"]
    },
    {
      "target_name": "c_wrapper_addon",
      "cflags": ["-Wall", "-std=c++11"],
      "sources": [ "bindings/c_wrapper.cc", "lib/exchange.cc", "lib/libtest.c" ],
      "include_dirs" : [
        "lib", "<!(node -e \"require('./server/node_modules/nan')\")"
      ],
      "conditions": [
        [ "OS=='mac'", {
          "xcode_settings": {
            "OTHER_CPLUSPLUSFLAGS" : ["-std=c++11","-stdlib=libc++"],
            "OTHER_LDFLAGS": ["-stdlib=libc++"],
            "MACOSX_DEPLOYMENT_TARGET": "10.7" }
        }
        ]
      ]
    }
  ]
}