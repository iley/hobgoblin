cc_binary(
    name = "emu",
    srcs = ["emu_main.cc"],
    deps = [
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        ":bus",
        ":cpu",
        ":emulator",
        ":mc6850",
        ":memory",
    ],
)

cc_library(
    name = "device",
    hdrs = ["device.h"],
    srcs = ["device.cc"],
)

cc_library(
    name = "null_device",
    hdrs = ["null_device.h"],
    srcs = ["null_device.cc"],
    deps = [":device"],
)

cc_library(
    name = "memory",
    hdrs = ["memory.h"],
    srcs = ["memory.cc"],
    deps = [":device"],
)

cc_test(
    name = "memory_test",
    srcs = ["memory_test.cc"],
    deps = [
        "//third_party:catch",
        ":memory",
    ],
)

cc_library(
    name = "bus",
    hdrs = ["bus.h"],
    srcs = ["bus.cc"],
    deps = [":device"],
)

cc_test(
    name = "bus_test",
    srcs = ["bus_test.cc"],
    deps = [
        "//third_party:catch",
        ":bus",
        ":memory",
    ],
)

cc_library(
    name = "cpu",
    hdrs = ["cpu.h"],
    srcs = ["cpu.cc"],
    deps = [
        ":device",
        "//third_party:z80",
    ],
)

cc_test(
    name = "cpu_test",
    srcs = ["cpu_test.cc"],
    deps = [
        "//third_party:catch",
        ":cpu",
        ":memory",
        ":null_device",
    ],
)

cc_library(
    name = "emulator",
    hdrs = ["emulator.h"],
    srcs = ["emulator.cc"],
    deps = [
        ":cpu",
        ":device",
    ],
)

cc_library(
    name = "mc6850",
    hdrs = ["mc6850.h"],
    srcs = ["mc6850.cc"],
    deps = [
        ":channel",
        ":device",
    ],
)

cc_library(
    name = "channel",
    hdrs = ["channel.h"],
)

cc_test(
    name = "channel_test",
    srcs = ["channel_test.cc"],
    deps = [
        "//third_party:catch",
        ":channel",
    ],
)
