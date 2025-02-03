cmake_minimum_required(VERSION 3.12)

project(tpzq)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

find_package(Qt5 REQUIRED COMPONENTS Widgets WaylandClient)
set(CMAKE_AUTOMOC ON)

add_executable(tpzq
  main.cxx
  config_manager.cxx
  hyprland_controller.cxx
  waybar_controller.cxx
  wallpaper_controller.cxx
  wofi_controller.cxx
  cava_controller.cxx
  theme_switcher.cxx
)

target_link_libraries(tpzq
    PRIVATE
    spdlog
    fmt
    Qt5::Widgets
    Qt5::WaylandClient
)
