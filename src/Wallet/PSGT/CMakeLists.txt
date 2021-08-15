set(TARGET_NAME PSGT)

file(GLOB SOURCE_CODE
        "Psgt.h"
        "Psgt.cpp"
)

add_library(${TARGET_NAME} STATIC ${SOURCE_CODE})
target_compile_definitions(${TARGET_NAME} PRIVATE MW_PSGT)
target_link_libraries(${TARGET_NAME} Core)