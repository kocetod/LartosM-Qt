project(TransLib)

set(${PROJECT_NAME}_SOURCES
    PointCoo.cpp
    PointCoo.h
    TrUnivw.cpp
    TrUnivw.h
    TransHelper.cpp
    TransHelper.h
    albers.cpp
    albers.h
    azeq.cpp
    azeq.h
    bng.cpp
    bng.h
    bonne.cpp
    bonne.h
    cassini.cpp
    cassini.h
    cyleqa.cpp
    cyleqa.h
    eckert4.cpp
    eckert4.h
    eckert6.cpp
    eckert6.h
    eqdcyl.cpp
    eqdcyl.h
    geocent.cpp
    geocent.h
    geodw.cpp
    geodw.h
    geoid.cpp
    geoid.h
    georef.cpp
    georef.h
    gnomonic.cpp
    gnomonic.h
    grinten.cpp
    grinten.h
    lambert.cpp
    lambert.h
    loccart.cpp
    loccart.h
    mercator.cpp
    mercator.h
    mgrs.cpp
    mgrs.h
    miller.cpp
    miller.h
    mollweid.cpp
    mollweid.h
    neys.cpp
    neys.h
    nzmg.cpp
    nzmg.h
    omerc.cpp
    omerc.h
    orthogr.cpp
    orthogr.h
    polarst.cpp
    polarst.h
    polycon.cpp
    polycon.h
    projection.cpp
    projection.h
    secret.cpp
    secret.h
    sinusoid.cpp
    sinusoid.h
    stereogr.cpp
    stereogr.h
    tranmerc.cpp
    tranmerc.h
    transform.cpp
    transform.h
    trcyleqa.cpp
    trcyleqa.h
    ups.cpp
    ups.h
    utm.cpp
    utm.h
)


add_library(${PROJECT_NAME} OBJECT ${${PROJECT_NAME}_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON
)

get_filename_component(TRANSLIB_PARENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(${PROJECT_NAME}
    PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    PUBLIC
    "$<BUILD_INTERFACE:${TRANSLIB_PARENT_SOURCE_DIR}>"
    "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>"
)
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    General
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
    _LIB=1
    _EXCLUDE_BSTR=1
    $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:${PROJECT_NAME}_STATIC_DEFINE>
    ${DEFAULT_COMPILE_DEFINITIONS}
)

message(STATUS "Created target ${PROJECT_NAME} for export ${PROJECT_NAME}.")
