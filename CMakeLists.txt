cmake_minimum_required (VERSION 3.8)

set(CMAKE_BUILD_TYPE Release)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CCHIP8" VERSION 0.9)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED 14)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES
	${SOURCE_DIR}/main.cpp
	${SOURCE_DIR}/buffer_operations.cpp
	${SOURCE_DIR}/buffer_operations.h
	${SOURCE_DIR}/chip8cpu.cpp
	${SOURCE_DIR}/chip8cpu.h
	${SOURCE_DIR}/DisplayManager.cpp
	${SOURCE_DIR}/DisplayManager.h
	${SOURCE_DIR}/fileManager.cpp
	${SOURCE_DIR}/fileManager.h
	${SOURCE_DIR}/instruction_set.h
	${SOURCE_DIR}/KeyboardManager.cpp
	${SOURCE_DIR}/KeyboardManager.h
	${SOURCE_DIR}/Memory.cpp
	${SOURCE_DIR}/Memory.h
	${SOURCE_DIR}/ProgramManager.cpp
	${SOURCE_DIR}/ProgramManager.h
)

add_executable(CCHIP8-EMULATOR ${SOURCE_FILES})

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Release/resources")

add_custom_command(
    TARGET CCHIP8-EMULATOR POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${LIB_DIR}/SDL2.dll $<TARGET_FILE_DIR:CCHIP8-EMULATOR>
	COMMAND ${CMAKE_COMMAND} -E copy
        ${LIB_DIR}/SDL2_ttf.dll $<TARGET_FILE_DIR:CCHIP8-EMULATOR>
)

target_include_directories(CCHIP8-EMULATOR PRIVATE ${INCLUDE_DIR})
target_link_libraries(CCHIP8-EMULATOR PRIVATE 
	${LIB_DIR}/SDL2.lib
	${LIB_DIR}/SDL2main.lib
	${LIB_DIR}/SDL2_ttf.lib
)
