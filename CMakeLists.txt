cmake_minimum_required(VERSION 3.27)
set(project_version 8.0)
set(project_name "clr-power-tweaks")
project(clr_power_tweaks VERSION ${project_version} LANGUAGES C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PACKAGE "\"${project_name}\"")
set(PACKAGE_BUGREPORT "\"dev@lists.clearlinux.org\"")
set(PACKAGE_NAME "\"${project_name}\"")
set(PACKAGE_STRING "\"${project_name} ${project_version}\"")
set(PACKAGE_TARNAME "\"${project_name}\"")
set(PACKAGE_URL "\"\"")
set(VERSION "\"${project_version}\"")

# Check for pkg-config (required for the next steps)
find_package(PkgConfig REQUIRED)
# Add GNUInstallDirs to use GNU install directories
include(GNUInstallDirs)

# Check for systemd
pkg_check_modules(SYSTEMD libsystemd)
if(SYSTEMD_FOUND)
    message(STATUS "Systemd found: ${SYSTEMD_LIBRARIES}")
    # target_include_directories(myapp PRIVATE ${SYSTEMD_INCLUDE_DIRS})
    # target_link_libraries(myapp ${SYSTEMD_LIBRARIES})
else()
    message(FATAL_ERROR "Error: systemd NOT found")
    exit(1)
endif()

configure_file(
  "${PROJECT_SOURCE_DIR}/config2.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

# Setting the include directory for the application to find config.h
# include_directories( ${CMAKE_BINARY_DIR} )
# Since we have created a config.h add a global define for it
# add_definitions( "-DHAVE_CONFIG_H" )# Generating the library clr_power
# set(project "clr_power")

# set(${project}, "")
list(APPEND ${PACKAGE}_SOURCES
    ${PROJECT_SOURCE_DIR}/src/cpu.c
    ${PROJECT_SOURCE_DIR}/src/data.h
    ${PROJECT_SOURCE_DIR}/src/ethernet.c
    ${PROJECT_SOURCE_DIR}/src/gfx.c
    ${PROJECT_SOURCE_DIR}/src/lib.c
    ${PROJECT_SOURCE_DIR}/src/main.c
    ${PROJECT_SOURCE_DIR}/src/mm.c
    ${PROJECT_SOURCE_DIR}/src/pci.c
    ${PROJECT_SOURCE_DIR}/src/server.c
    ${PROJECT_SOURCE_DIR}/src/usb.c
    ${PROJECT_SOURCE_DIR}/src/verifytime.c
)
add_executable(clr_power ${${PACKAGE}_SOURCES} )
# target_include_directories(clr_power_tweaks
#     PRIVATE
#         ${PROJECT_SOURCE_DIR}/include
# )
target_include_directories(clr_power PRIVATE include)
target_include_directories(clr_power PRIVATE "${PROJECT_BINARY_DIR}")


install(TARGETS clr_power
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )

# Installation of the man files
install(FILES man/clr_power.1
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man1
        )
install(FILES man/clr-power-tweaks.conf.5
        DESTINATION ${CMAKE_INSTALL_MANDIR}/man5
        )


install(FILES clr-power-rfkill.service DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/system)
install(FILES clr-power.service DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/system)
install(FILES clr-power.timer DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/system)


install(CODE "file(MAKE_DIRECTORY \${CMAKE_INSTALL_PREFIX}/lib/systemd/system/timers.target.wants)")
install(CODE "execute_process(COMMAND ln -sf ${CMAKE_INSTALL_PREFIX}/lib/systemd/system/clr-power.timer ${CMAKE_INSTALL_PREFIX}/lib/systemd/system/timers.target.wants/clr-power.timer)")

install(CODE "file(MAKE_DIRECTORY \${CMAKE_INSTALL_PREFIX}/lib/systemd/system/sysinit.target.wants)")
install(CODE "execute_process(COMMAND ln -sf ${CMAKE_INSTALL_PREFIX}/lib/systemd/system/clr-power-rfkill.service ${CMAKE_INSTALL_PREFIX}/lib/systemd/system/sysinit.target.wants/clr-power-rfkill.service)")
