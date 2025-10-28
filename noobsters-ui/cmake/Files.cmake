include(cmake/Variables.cmake)

file(GLOB SOURCE ${SRC_DIR}/*.cpp)
file(GLOB HEADER ${HDR_DIR}/*.h)
file(GLOB INLINE ${HDR_DIR}/*.hpp)

set(NOOBSTERS_LINUX_UI_HEADERS
        ${HEADER}
        ${INLINE}
)

set(NOOBSTERS_LINUX_UI_SOURCES
        ${SOURCE}
)
