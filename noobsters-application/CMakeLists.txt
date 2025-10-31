project(noobsters-application VERSION 1.0.0 LANGUAGES CXX)

include(cmake/Files.cmake)
include(cmake/Variables.cmake)
include(cmake/FetchDependencies.cmake)


#Debug
add_definitions(-DENABLE_ASSERTS=1 -DNOOBSTERS_ENABLE_LOG=1)

option(WANDER_ENGINE_INSTALL "Generate installation target" OFF)

################################################################################################
add_library(noobsters-application STATIC ${NOOBSTERS_APPLICATION_HEADERS} ${NOOBSTERS_APPLICATION_SOURCES})

target_compile_options(noobsters-application PRIVATE
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

target_include_directories(noobsters-application PUBLIC
        $<BUILD_INTERFACE: ${HDR_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(noobsters-application PUBLIC
        spdlog
)

if (NOOBSTERS_APPLICARTION_INSTALL)
    # cmake install dirs
    include(GNUInstallDirs)

    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/noobstersApplicationConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/noobstersApplicationConfig.cmake")
    set(targets_export_name "noobstersEngineTargets")
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
            INSTALL_DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/noobsters)

    # Targets:
    install(
            TARGETS noobsters-application
            EXPORT "${targets_export_name}"
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

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
