set(TARGET_NAME HardwareWallet)

file(GLOB SOURCE_CODE
        "Comm.h"
        "Error.cpp"
        "Error.h"
        "HidDevice.cpp"
        "HidDevice.h"
        "Ledger.cpp"
        "Ledger.h"
        "Transport.cpp"
        "Transport.h"
        "Utils.cpp"
        "Utils.h"
        "LedgerKeyKeeper.cpp"
        "LedgerKeyKeeper.h"
        "KeyKeeper.h"
)

add_library(${TARGET_NAME} STATIC ${SOURCE_CODE})
target_compile_definitions(${TARGET_NAME} PRIVATE MW_HardwareWallet)
target_link_libraries(${TARGET_NAME} Core)