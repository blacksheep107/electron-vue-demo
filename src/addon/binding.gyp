{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "hello.cpp",
        "base64.cpp",
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")",
        "<(module_root_dir)/openssl-OpenSSL_1_1_1s/include",
        "base64.h",
      ],
      "dependencies": [
        "<!(node -p \"require('node-addon-api').gyp\")"
      ],
    'libraries': [
        "<(module_root_dir)/openssl-OpenSSL_1_1_1s/libssl.lib",
        "<(module_root_dir)/openssl-OpenSSL_1_1_1s/libcrypto.lib",
        "ws2_32.lib",
        "Crypt32.lib",
    ],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"],
      "defines": ["NAPI_CPP_EXCEPTIONS"],
      "xcode_settings": {
        "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
      }
    }
  ]
}
