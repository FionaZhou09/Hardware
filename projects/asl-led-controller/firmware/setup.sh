#!/usr/bin/env bash
# Run once to pull the HAL and CMake toolchain support.
# Requires: git, cmake, arm-none-eabi-gcc, openocd (all available via brew)

set -e

SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
CMAKE_DIR="$SCRIPT_DIR/cmake"

mkdir -p "$CMAKE_DIR"

# ── 1. stm32-cmake (CMake modules for STM32 bare-metal) ──────────────────
if [ ! -d "$CMAKE_DIR/stm32-cmake" ]; then
    echo "[1/2] Cloning stm32-cmake..."
    git clone --depth 1 https://github.com/ObKo/stm32-cmake.git "$CMAKE_DIR/stm32-cmake"
else
    echo "[1/2] stm32-cmake already present, skipping."
fi

# ── 2. STM32CubeG4 HAL (sparse: Drivers only, ~40 MB instead of ~600 MB) ─
if [ ! -d "$CMAKE_DIR/STM32CubeG4" ]; then
    echo "[2/2] Cloning STM32CubeG4 HAL (sparse checkout, Drivers only)..."
    git clone --depth 1 --filter=blob:none --sparse \
        https://github.com/STMicroelectronics/STM32CubeG4.git \
        "$CMAKE_DIR/STM32CubeG4"
    cd "$CMAKE_DIR/STM32CubeG4"
    git sparse-checkout set Drivers
    cd "$SCRIPT_DIR"
else
    echo "[2/2] STM32CubeG4 already present, skipping."
fi

# ── 3. Configure + build ──────────────────────────────────────────────────
BUILD_DIR="$SCRIPT_DIR/build"
mkdir -p "$BUILD_DIR"

echo ""
echo "Configuring CMake..."
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" \
    -DCMAKE_TOOLCHAIN_FILE="$CMAKE_DIR/stm32-cmake/cmake/stm32_gcc.cmake" \
    -DSTM32_CUBE_G4_PATH="$CMAKE_DIR/STM32CubeG4" \
    -DCMAKE_BUILD_TYPE=Debug

echo ""
echo "Building firmware..."
cmake --build "$BUILD_DIR" -- -j$(sysctl -n hw.logicalcpu)

echo ""
echo "Done. Firmware is at: build/firmware.bin"
echo "To flash: openocd -f openocd.cfg -c 'program build/firmware.elf verify reset exit'"
