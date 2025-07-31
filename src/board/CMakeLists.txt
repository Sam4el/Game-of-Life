# src/board/print/CMakeLists.txt

# Create a library named print 
# STATIC mean it's static library (.a file) which gets compiled into final exec 
# Other options are SHARE for (.so dynamic libs) and OBJECT (raw compiled .o file)
add_library(board STATIC
    state.cpp
    io/printer.cpp
    logic/controller.cpp
)

# Tell CMake where to find headers for this library
target_include_directories(board PUBLIC
    ${PROJECT_SOURCE_DIR}/inc/board
    ${PROJECT_SOURCE_DIR}/inc/board/io
    ${PROJECT_SOURCE_DIR}/inc/board/logic
)
