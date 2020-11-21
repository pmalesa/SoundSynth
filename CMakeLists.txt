cmake_minimum_required(VERSION 3.18.3)

project(soundSynth)
set(CMAKE_CXX_STANDARD 14)

# Platform specific variables
if(WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(TARGET_SYSTEM "win64")
    endif()
elseif(UNIX)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(TARGET_SYSTEM "linux64")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
        set(TARGET_SYSTEM "linux32")
    endif()
endif()

message(STATUS "Target system: ${TARGET_SYSTEM}")

# RtAudio library
if (UNIX)
    set(RTAUDIO_LIBRARIES "${PROJECT_SOURCE_DIR}/dll/rtaudio/librtaudio.so")
endif()

# Create sources variables
set(SOUNDSYNTH_MAIN_FILE "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp")
set(SOUNDSYNTH_SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/src/main.cpp"

    # (...)
)

# Create main target
add_executable(soundSynth "")
target_sources(soundSynth
    PRIVATE
        ${SOUNDSYNTH_MAIN_FILE}
        ${SOUNDSYNTH_SOURCES}
)

target_include_directories(soundSynth PUBLIC "src/" "include/rtaudio/")
target_link_libraries(soundSynth ${RTAUDIO_LIBRARIES})