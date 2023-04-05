add_rules("mode.debug", "mode.release")
add_requires("gtest")

target("base_test")
    set_kind("binary")
    add_includedirs("include")
    add_files("test/base_test.cpp")
    add_files("src/base.c")
    add_packages("gtest")
