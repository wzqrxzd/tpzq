cmake_minimum_required(VERSION 3.12)

project(tpzq)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_executable(tpzq
  main.cxx
  config_manager.cxx
  hyprland_controller.cxx
  waybar_controller.cxx
  wallpaper_controller.cxx
  wofi_controller.cxx
)

target_link_libraries(tpzq
    PRIVATE
    spdlog
    fmt
)
