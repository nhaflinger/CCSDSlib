project(CCSDS)

add_library(CCSDS SHARED CCSDSlib.cpp)

target_sources(CCSDS PUBLIC "${CMAKE_SOURCE_DIR}/CCSDSlib/CCSDSlib.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/PacketField.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/PacketDecode.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/PacketFixedLength.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/PacketEncode.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/Frame.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/FrameDecode.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/PacketEncode.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/CommandEncode.cpp" "${CMAKE_SOURCE_DIR}/CCSDSlib/source/CRCchecksum.cpp")
include_directories("${CMAKE_SOURCE_DIR}/CCSDSlib" "${CMAKE_SOURCE_DIR}/CCSDSlib/include")
target_sources(CCSDS PUBLIC "${CMAKE_SOURCE_DIR}/CCSDSlib/include/CCSDS.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/CCSDSlib.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/PacketField.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/PacketDecode.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/PacketFixedLength.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/PacketEncode.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/Frame.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/FrameDecode.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/PacketEncode.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/CommandEncode.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/CRCchecksum.h" "${CMAKE_SOURCE_DIR}/CCSDSlib/include/Endian.h")

target_compile_options(CCSDS PRIVATE -fPIC -shared)

if (WIN32)
	set_target_properties(CCSDS PROPERTIES CXX_STANDARD 17 WINDOWS_EXPORT_ALL_SYMBOLS TRUE RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/CCSDSlib/Debug" RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/CCSDSlib/Release")
else()
	set_target_properties(CCSDS PROPERTIES CXX_STANDARD 17 RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/CCSDSlib/Debug" RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/CCSDSlib/Release")
endif()

#add_definitions(-DVERBOSE)
