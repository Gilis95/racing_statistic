project(noobsters-linux-application VERSION 1.0.0 LANGUAGES CXX)

include(cmake/Files.cmake)
include(cmake/Variables.cmake)

set(PROJECT_WORKING_DIR "${CMAKE_CURRENT_BINARY_DIR}")
set(PROJECT_ID "org.noobsters")
SET(OUTPUT_NAME "noobsters-linux-application")


find_package(PkgConfig REQUIRED)

pkg_check_modules(gtk REQUIRED IMPORTED_TARGET gtk4)
pkg_check_modules(libadwaita REQUIRED IMPORTED_TARGET libadwaita-1)
#pkg_check_modules(libxml REQUIRED IMPORTED_TARGET libxml++-5.0)

configure_file(
        ${HDR_DIR}/config.h.in
        ${HDR_DIR}/config.h
)

################################################################################################
add_executable(${OUTPUT_NAME} ${NOOBSTERS_LINUX_APPLICATION_HEADERS} ${NOOBSTERS_LINUX_APPLICATION_SOURCES})

target_compile_options(${OUTPUT_NAME} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wconversion          # Warn on implicit type conversions (int to float, etc.)
        -Wsign-conversion     # Warn on signed/unsigned mismatches
        -Wshadow              # Warn when a variable declaration shadows another
        -Wnon-virtual-dtor    # Warn if a class with virtual functions has a non-virtual destructor
        -Wold-style-cast      # Warn on C-style casts (encourage C++-style casts)
        -Woverloaded-virtual  # Warn if a virtual function is hiding a base class overload
        -Wduplicated-cond     # Warn on repeated conditions in `if` or loops
        -Wduplicated-branches # Warn if branches of conditionals are identical
        -Wnull-dereference    # Warn on possible null pointer dereferencing
        -Wdouble-promotion    # Warn when `float` is implicitly promoted to `double`
        -Wmissing-declarations # Warn if non-`static` functions lack a declaration
        #        -fsanitize=address    # Detect memory errors (buffer overflows, use-after-free, etc.)
        #        -fsanitize=undefined  # Detect undefined behavior (signed overflows, etc.)
)

target_include_directories(${OUTPUT_NAME} PRIVATE
        $<BUILD_INTERFACE: ${HDR_DIR}>
        $<INSTALL_INTERFACE:include>
        ${noobsters-application_INCLUDES}
)

target_link_libraries(${OUTPUT_NAME} PRIVATE
        PkgConfig::gtk
        PkgConfig::libadwaita
        #        PkgConfig::libxml
        noobsters-application
)


find_program(GLIB_COMPULE_RESOURCES_EXECUTABLE glib-compile-resources)
if (GLIB_COMPULE_RESOURCES_EXECUTABLE)
    add_custom_command(TARGET ${OUTPUT_NAME} PRE_BUILD COMMAND "${GLIB_COMPULE_RESOURCES_EXECUTABLE}"
            --sourcedir "${CMAKE_CURRENT_SOURCE_DIR}/resources" "${CMAKE_CURRENT_SOURCE_DIR}/resources/${PROJECT_ID}.gresource.xml"
            --target="${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_ID}.gresource")
else ()
    message(WARNING "glib-compile-resources not found, resources will not be compiled")
endif ()

if (NOOBSTERS_LINUX_APP_INSTALL)
    # cmake install dirs
    include(GNUInstallDirs)

    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/noostersLinuxApplicationConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/noostersLinuxApplicationConfig.cmake")
    set(targets_export_name "noostersLinuxApplicationTargets")
    set(namespace "noobsters::")

    # Include module with function 'write_basic_package_version_file'
    include(CMakePackageConfigHelpers)

    # Configure 'gladConfigVersion.cmake'
    # PROJECT_VERSION is used as a VERSION
    write_basic_package_version_file("${version_config}" COMPATIBILITY SameMajorVersion)

    # Configure 'tracyConfig.cmake'
    # Uses targets_export_name variable.
    configure_package_config_file(
            "Config.cmake.in"
            "${project_config}"
            INSTALL_DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/wunder)

    # Targets:
    install(
            TARGETS ${OUTPUT_NAME}
            EXPORT "${targets_export_name}"
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    #    install(FILES ${WINDOW_GLFW_HEADER} ${WINDOW_GLFW_INLINE}
    #            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/window)

    # Install wunderConfig.cmake, wunderConfigVersion.cmake
    install(
            FILES "${project_config}" "${version_config}"
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/noobsters)

    # Create and install wunderTargets.cmake
    install(
            EXPORT "${targets_export_name}"
            NAMESPACE "${namespace}"
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/noobsters)
endif ()
