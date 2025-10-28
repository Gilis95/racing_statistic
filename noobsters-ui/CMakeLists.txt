project(noobsters-linux-ui VERSION 1.0.0 LANGUAGES CXX)

include(cmake/Files.cmake)
include(cmake/Variables.cmake)

#add_definitions(-DWANDER_ENABLE_LOG -D_CRT_SECURE_NO_WARNINGS -DWANDER_ENGINE_DEBUG -DTRACY_ENABLE -DGLFW_INCLUDE_NONE)


#Debug
#add_definitions(-DENABLE_ASSERTS=1 -DWUNDER_ENABLE_LOG=1)

option(WANDER_ENGINE_INSTALL "Generate installation target" OFF)

find_package(PkgConfig REQUIRED)

pkg_check_modules(
        GTK REQUIRED
        IMPORTED_TARGET
        gtk4
        libadwaita-1
        gmodule-export-2.0
)

################################################################################################
add_executable(noobsters-linux-ui ${NOOBSTERS_LINUX_UI_HEADERS} ${NOOBSTERS_LINUX_UI_SOURCES})

target_compile_options(noobsters-linux-ui PRIVATE
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

target_include_directories(noobsters-linux-ui PUBLIC
        $<BUILD_INTERFACE: ${HDR_DIR}>
        $<INSTALL_INTERFACE:include>
        ${GTK_INCLUDE_DIRS}
)

target_link_libraries(noobsters-linux-ui PRIVATE
    PkgConfig::GTK
)

if (WANDER_ENGINE_INSTALL)
    # cmake install dirs
    include(GNUInstallDirs)

    set(version_config "${CMAKE_CURRENT_BINARY_DIR}/wunderEngineConfigVersion.cmake")
    set(project_config "${CMAKE_CURRENT_BINARY_DIR}/wunderEngineConfig.cmake")
    set(targets_export_name "wunderEngineTargets")
    set(namespace "wunder::")

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
            TARGETS wunder-renderer
            EXPORT "${targets_export_name}"
            LIBRARY DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}
            RUNTIME DESTINATION ${CMAKE_INSTALL_FULL_BINDIR})

    install(FILES ${APPLICATION_HEADER} ${APPLICATION_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/application)

    install(FILES ${CAMERA_HEADER} ${CAMERA_HEADER}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/camera)

    install(FILES ${CORE_HEADER} ${CORE_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/core)

    install(FILES ${ECS_HEADER} ${ECS_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/ecs)

    install(FILES ${EVENT_HEADER} ${EVENT_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/event)

    install(FILES ${GLA_HEADER} ${GLA_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/gla)

    install(FILES ${GLA_OPENGL_HEADER} ${GLA_OPENGL_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/gla/platform/opengl)

    install(FILES ${ROOT_HEADER} ${ROOT_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/)

    install(FILES ${RENDERER_HEADER} ${RENDERER_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/renderer)

    install(FILES ${SCENE_HEADER} ${SCENE_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/scene)

    install(FILES ${WINDOW_HEADER} ${WINDOW_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/window)

    install(FILES ${WINDOW_GLFW_HEADER} ${WINDOW_GLFW_INLINE}
            DESTINATION ${CMAKE_INSTALL_FULL_INCLUDEDIR}/wunder/window)

    # Install wunderConfig.cmake, wunderConfigVersion.cmake
    install(
            FILES "${project_config}" "${version_config}"
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/wunder)

    # Create and install wunderTargets.cmake
    install(
            EXPORT "${targets_export_name}"
            NAMESPACE "${namespace}"
            DESTINATION ${CMAKE_INSTALL_FULL_LIBDIR}/cmake/wunder)
endif ()
