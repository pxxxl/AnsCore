add_rules("mode.debug", "mode.release")
add_requires("gtest")
add_requires("fmt")


target("base_test")
    set_kind("binary")
    add_files("test/base_test.cpp")
    add_files("src/base/base.c")
    add_packages("gtest")

target("processor_API_test")
    set_kind("binary")
    add_includedirs("include")
    add_files("test/processor_API_test.cpp")
    add_files("src/processor/processor.c")
    add_files("src/base/base.c")
    add_files("src/object/object.c")
    add_files("src/units/obstacles.c")
    add_files("src/units/bullets.c")
    add_files("src/units/player_object.c")
    add_packages("gtest")

target("graphic_demo")
    add_rules("qt.widgetapp")
    add_files("test/qt_graphic_test.cpp")
    add_files("src/IO/qt_draw.cpp")
    add_files("src/IO/qt_draw.h")

target("player_test")
    add_rules("qt.widgetapp")


    add_files("src/processor/processor.c")
    add_files("src/base/base.c")
    add_files("src/object/object.c")
    add_files("src/custom/units/*.c")
    add_files("src/custom/skills/*.c")

    add_files("test/qt_player_object_test.cpp")
    add_files("src/IO/qt_draw.cpp")
    add_files("src/IO/qt_draw.h")
    add_files("src/IO/random.cpp")
    add_packages("fmt")
