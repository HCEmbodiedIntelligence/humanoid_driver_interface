cmake_minimum_required(VERSION 3.8)
project(humanoid_driver_interface)

find_package(ament_cmake REQUIRED)
find_package(pluginlib REQUIRED)

install(DIRECTORY include/ DESTINATION include)
install(FILES README.md DESTINATION share/${PROJECT_NAME})

ament_export_include_directories(include)
ament_export_dependencies(pluginlib)

ament_package()
