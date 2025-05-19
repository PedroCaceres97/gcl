# Módulo: core
add_subdirectory(core/${GCL_PLATFORM})

# Módulo: string
target_sources(gcl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/string/allocation.c
    ${CMAKE_CURRENT_SOURCE_DIR}/string/replacement.c
)

# wrappers
target_sources(gcl PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/wrappers.c
)