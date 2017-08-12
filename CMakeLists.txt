
# CMakeLists.txt, generated gencmake.pl, on 2017/08/10 20:23:31
cmake_minimum_required( VERSION 2.8.8 )

# CMakeScripts or use the ones that come by default with CMake.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules) # ${CMAKE_MODULE_PATH})

project( xyz2wsg84 )

# The version number.
set( xyz2wsg84_MAJOR 3 )
set( xyz2wsg84_MINOR 0 )
set( xyz2wsg84_POINT 0 )


# Allow developer to select is Dynamic or static library built
set( LIB_TYPE STATIC )  # set default static
option( BUILD_SHARED_LIB "Set ON to build shared Library (DLL)" OFF )


if(CMAKE_COMPILER_IS_GNUCXX)
    set( WARNING_FLAGS -Wall )
endif(CMAKE_COMPILER_IS_GNUCXX)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang") 
   set( WARNING_FLAGS "-Wall -Wno-overloaded-virtual" )
endif() 

if(WIN32 AND MSVC)
    # turn off various warnings - none needed in this compile
    set(WARNING_FLAGS "${WARNING_FLAGS} /wd4996")
    # foreach(warning 4244 4251 4267 4275 4290 4786 4305)
    #     set(WARNING_FLAGS "${WARNING_FLAGS} /wd${warning}")
    # endforeach(warning)
    set( MSVC_FLAGS "-DNOMINMAX -D_USE_MATH_DEFINES -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -D__CRT_NONSTDC_NO_WARNINGS" )
    # if (${MSVC_VERSION} EQUAL 1600)
    #    set( MSVC_LD_FLAGS "/FORCE:MULTIPLE" )
    # endif (${MSVC_VERSION} EQUAL 1600)
    #set( NOMINMAX 1 )
    # to distinguish between debug and release libs
    set( CMAKE_DEBUG_POSTFIX "d" )
else()
    # items for unix
    list(APPEND add_LIBS m)
endif()

set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS} ${MSVC_FLAGS} -D_REENTRANT" )
set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${MSVC_LD_FLAGS}" )

find_package( GeographicLib )
if (GeographicLib_FOUND)
    message(STATUS "*** Found GeographicLib inc=${GeographicLib_INCLUDE_DIRS} lib=${GeographicLib_LIBRARIES}")
    list(APPEND add_LIBS ${GeographicLib_LIBRARIES})
    include_directories( ${GeographicLib_INCLUDE_DIRS} )
    add_definitions( -DUSE_GEOGRAPHIC_LIB )
else ()
    message(STATUS "*** NOT found GeographicLib!")
endif ()    
    
# configuration file, if needed
# configure_file( ${CMAKE_SOURCE_DIR}/config.h.cmake ${CMAKE_BINARY_DIR}/config.h )
# add_definitions( -DHAVE_CONFIG_H )
# include_directories( ${CMAKE_BINARY_DIR} )

if(BUILD_SHARED_LIB)
   set(LIB_TYPE SHARED)
   message(STATUS "*** Building DLL library ${LIB_TYPE}")
else()
   message(STATUS "*** Option BUILD_SHARED_LIB is OFF ${LIB_TYPE}")
endif()
# Total libs 1, exes 1
#################################################
##### LIBRARIES 0 #####
#################################################
set(name xyzutils)
set(dir src)
set(${name}_SRCS
    ${dir}/degdms.c
    ${dir}/plh2xyz.c
    ${dir}/xyz2plh.c
    )
set(${name}_HDRS
    ${dir}/libgpsC.h
    ${dir}/linfit.h
    ${dir}/olt.h
    ${dir}/physcon.h
    ${dir}/sidata.h
    )
if (MSVC)
    list(APPEND ${name}_SRCS ${dir}/wingetopt/getopt.c)
    list(APPEND ${name}_HDRS ${dir}/wingetopt/getopt.h)
endif ()    
add_library( ${name} STATIC ${${name}_SRCS} ${${name}_HDRS} )
list(APPEND add_LIBS ${name})

# deal with install, if any...
install( TARGETS ${name}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib )
#install(FILES ${${name}_HDRS} DESTINATION include)
#################################################
##### EXECUTABLE 2 #####
#################################################

# src EXECUTABLE from [src],
# have 4 C/C++ sources, 5 headers
set(name xyz2wsg)
set(dir src)
set(${name}_SRCS
    ${dir}/xyz2llh.c
    )
add_executable( ${name} ${${name}_SRCS} )
if (add_LIBS)
    target_link_libraries( ${name} ${add_LIBS} )
endif ()
if (MSVC)
    set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
endif ()
# deal with install, if any...
install( TARGETS ${name} DESTINATION bin )

if (GeographicLib_FOUND)
    set(name xyz2wsg84)
    set(dir src)
    set(${name}_SRCS
        ${dir}/xyz2wsg.cxx
        )
    add_executable( ${name} ${${name}_SRCS} )
    if (add_LIBS)
        target_link_libraries( ${name} ${add_LIBS} )
    endif ()
    if (MSVC)
        set_target_properties( ${name} PROPERTIES DEBUG_POSTFIX d )
    endif ()
    # deal with install, if any...
    install( TARGETS ${name} DESTINATION bin )
endif ()

# eof
