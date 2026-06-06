cmake_minimum_required(VERSION 3.20)

# Toolchain and HAL paths are passed in from setup.sh (or the cmake command line)
# CMAKE_TOOLCHAIN_FILE  → cmake/stm32-cmake/cmake/stm32_gcc.cmake
# STM32_CUBE_G4_PATH    → cmake/STM32CubeG4

project(asl-led-controller C ASM)
set(CMAKE_C_STANDARD 11)

# ── Find HAL and CMSIS for the G474RE ─────────────────────────────────────
find_package(CMSIS  COMPONENTS STM32G474RE        REQUIRED)
find_package(HAL    COMPONENTS STM32G4 RCC GPIO UART CORTEX PWR REQUIRED)

# ── Firmware target ───────────────────────────────────────────────────────
add_executable(firmware
    Core/Src/main.c
    Core/Src/stm32g4xx_hal_msp.c
    Core/Src/stm32g4xx_it.c
    # pwr_ex is not a named stm32-cmake component — add source directly
    ${STM32_CUBE_G4_PATH}/Drivers/STM32G4xx_HAL_Driver/Src/stm32g4xx_hal_pwr_ex.c
)

target_include_directories(firmware PRIVATE Core/Inc)

target_link_libraries(firmware
    HAL::STM32::G4::RCC
    HAL::STM32::G4::GPIO
    HAL::STM32::G4::UART
    HAL::STM32::G4::CORTEX
    HAL::STM32::G4::PWR
    CMSIS::STM32::G474RE
    STM32::NoSys
)

# ── Generate .bin alongside .elf for flashing ─────────────────────────────
stm32_generate_binary_file(firmware)
