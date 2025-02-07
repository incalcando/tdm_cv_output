
# Consider dependencies only in project.
set(CMAKE_DEPENDS_IN_PROJECT_ONLY OFF)

# The set of languages for which implicit dependencies are needed:
set(CMAKE_DEPENDS_LANGUAGES
  "ASM"
  )
# The set of files for implicit dependencies of each language:
set(CMAKE_DEPENDS_CHECK_ASM
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_irq/irq_handler_chain.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_irq/irq_handler_chain.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_bit_ops/bit_ops_aeabi.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_crt0/crt0.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_crt0/crt0.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_double/double_aeabi_dcp.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_double/double_aeabi_dcp.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_double/double_conv_m33.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_double/double_conv_m33.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_double/double_fma_dcp.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_double/double_fma_dcp.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_double/double_sci_m33.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_double/double_sci_m33.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_float/float_conv_m33.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_float/float_conv_m33.S.o"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_float/float_sci_m33_vfp.S" "/home/sebastian/Instruo/tdm_output_example/build/CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_float/float_sci_m33_vfp.S.o"
  )
set(CMAKE_ASM_COMPILER_ID "GNU")

# Preprocessor definitions for this target.
set(CMAKE_TARGET_DEFINITIONS_ASM
  "LIB_BOOT_STAGE2_HEADERS=1"
  "LIB_PICO_ATOMIC=1"
  "LIB_PICO_BIT_OPS=1"
  "LIB_PICO_BIT_OPS_PICO=1"
  "LIB_PICO_CLIB_INTERFACE=1"
  "LIB_PICO_CRT0=1"
  "LIB_PICO_CXX_OPTIONS=1"
  "LIB_PICO_DIVIDER=1"
  "LIB_PICO_DIVIDER_COMPILER=1"
  "LIB_PICO_DOUBLE=1"
  "LIB_PICO_DOUBLE_PICO=1"
  "LIB_PICO_FLASH=1"
  "LIB_PICO_FLOAT=1"
  "LIB_PICO_FLOAT_PICO=1"
  "LIB_PICO_FLOAT_PICO_VFP=1"
  "LIB_PICO_INT64_OPS=1"
  "LIB_PICO_INT64_OPS_COMPILER=1"
  "LIB_PICO_MALLOC=1"
  "LIB_PICO_MEM_OPS=1"
  "LIB_PICO_MEM_OPS_COMPILER=1"
  "LIB_PICO_NEWLIB_INTERFACE=1"
  "LIB_PICO_PLATFORM=1"
  "LIB_PICO_PLATFORM_COMPILER=1"
  "LIB_PICO_PLATFORM_PANIC=1"
  "LIB_PICO_PLATFORM_SECTIONS=1"
  "LIB_PICO_PRINTF=1"
  "LIB_PICO_PRINTF_PICO=1"
  "LIB_PICO_RUNTIME=1"
  "LIB_PICO_RUNTIME_INIT=1"
  "LIB_PICO_STANDARD_BINARY_INFO=1"
  "LIB_PICO_STANDARD_LINK=1"
  "LIB_PICO_STDIO=1"
  "LIB_PICO_STDLIB=1"
  "LIB_PICO_SYNC=1"
  "LIB_PICO_SYNC_CRITICAL_SECTION=1"
  "LIB_PICO_SYNC_MUTEX=1"
  "LIB_PICO_SYNC_SEM=1"
  "LIB_PICO_TIME=1"
  "LIB_PICO_TIME_ADAPTER=1"
  "LIB_PICO_UTIL=1"
  "LOG_LEVEL=DEBUG_LEVEL"
  "PICO_32BIT=1"
  "PICO_BOARD=\"solderparty_rp2350_stamp_xl\""
  "PICO_BUILD=1"
  "PICO_CMAKE_BUILD_TYPE=\"Release\""
  "PICO_COPY_TO_RAM=0"
  "PICO_CXX_ENABLE_EXCEPTIONS=0"
  "PICO_NO_FLASH=0"
  "PICO_NO_HARDWARE=0"
  "PICO_ON_DEVICE=1"
  "PICO_PROGRAM_NAME=\"template\""
  "PICO_PROGRAM_VERSION_STRING=\"0.1\""
  "PICO_RP2350=1"
  "PICO_TARGET_NAME=\"RP2350_TDM_example\""
  "PICO_USE_BLOCKED_RAM=0"
  )

# The include file search paths:
set(CMAKE_ASM_TARGET_INCLUDE_PATH
  "."
  "../"
  "../inc"
  "../.."
  "../pico-sdk/src/rp2_common/pico_atomic/include"
  "../pico-sdk/src/common/pico_stdlib_headers/include"
  "../pico-sdk/src/rp2_common/hardware_gpio/include"
  "../pico-sdk/src/common/pico_base_headers/include"
  "generated/pico_base"
  "../pico-sdk/src/boards/include"
  "../pico-sdk/src/rp2350/pico_platform/include"
  "../pico-sdk/src/rp2350/hardware_regs/include"
  "../pico-sdk/src/rp2_common/hardware_base/include"
  "../pico-sdk/src/rp2_common/pico_platform_compiler/include"
  "../pico-sdk/src/rp2_common/pico_platform_panic/include"
  "../pico-sdk/src/rp2_common/pico_platform_sections/include"
  "../pico-sdk/src/rp2_common/hardware_dcp/include"
  "../pico-sdk/src/rp2350/hardware_structs/include"
  "../pico-sdk/src/rp2_common/hardware_rcp/include"
  "../pico-sdk/src/common/hardware_claim/include"
  "../pico-sdk/src/rp2_common/hardware_sync/include"
  "../pico-sdk/src/rp2_common/hardware_sync_spin_lock/include"
  "../pico-sdk/src/rp2_common/hardware_irq/include"
  "../pico-sdk/src/rp2_common/hardware_uart/include"
  "../pico-sdk/src/rp2_common/hardware_resets/include"
  "../pico-sdk/src/rp2_common/hardware_clocks/include"
  "../pico-sdk/src/rp2_common/hardware_pll/include"
  "../pico-sdk/src/rp2_common/hardware_vreg/include"
  "../pico-sdk/src/rp2_common/hardware_watchdog/include"
  "../pico-sdk/src/rp2_common/hardware_ticks/include"
  "../pico-sdk/src/rp2_common/pico_bootrom/include"
  "../pico-sdk/src/common/boot_picoboot_headers/include"
  "../pico-sdk/src/rp2_common/boot_bootrom_headers/include"
  "../pico-sdk/src/rp2_common/hardware_boot_lock/include"
  "../pico-sdk/src/rp2_common/pico_flash/include"
  "../pico-sdk/src/common/pico_time/include"
  "../pico-sdk/src/rp2_common/hardware_timer/include"
  "../pico-sdk/src/common/pico_sync/include"
  "../pico-sdk/src/common/pico_util/include"
  "../pico-sdk/src/rp2_common/pico_time_adapter/include"
  "../pico-sdk/src/rp2_common/hardware_xosc/include"
  "../pico-sdk/src/rp2_common/hardware_divider/include"
  "../pico-sdk/src/rp2_common/pico_runtime/include"
  "../pico-sdk/src/rp2_common/pico_runtime_init/include"
  "../pico-sdk/src/common/pico_bit_ops_headers/include"
  "../pico-sdk/src/common/pico_divider_headers/include"
  "../pico-sdk/src/rp2_common/pico_double/include"
  "../pico-sdk/src/rp2_common/pico_float/include"
  "../pico-sdk/src/rp2_common/pico_malloc/include"
  "../pico-sdk/src/common/pico_binary_info/include"
  "../pico-sdk/src/rp2_common/pico_printf/include"
  "../pico-sdk/src/rp2_common/pico_stdio/include"
  "../pico-sdk/src/rp2_common/pico_multicore/include"
  "../pico-sdk/src/common/boot_picobin_headers/include"
  "../pico-sdk/src/rp2350/boot_stage2/include"
  "../pico-sdk/src/rp2_common/hardware_i2c/include"
  "../pico-sdk/src/rp2_common/hardware_dma/include"
  "../pico-sdk/src/rp2_common/hardware_pio/include"
  "../pico-sdk/src/rp2_common/hardware_adc/include"
  )

# The set of dependency files which are needed:
set(CMAKE_DEPENDS_DEPENDENCY_FILES
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/hardware_claim/claim.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/hardware_claim/claim.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/hardware_claim/claim.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_sync/critical_section.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/critical_section.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/critical_section.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_sync/lock_core.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/lock_core.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/lock_core.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_sync/mutex.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/mutex.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/mutex.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_sync/sem.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/sem.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_sync/sem.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_time/time.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_time/time.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_time/time.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_time/timeout_helper.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_time/timeout_helper.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_time/timeout_helper.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_util/datetime.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_util/datetime.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_util/datetime.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_util/pheap.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_util/pheap.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_util/pheap.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/common/pico_util/queue.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_util/queue.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/common/pico_util/queue.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2350/pico_platform/platform.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2350/pico_platform/platform.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2350/pico_platform/platform.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_adc/adc.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_adc/adc.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_adc/adc.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_boot_lock/boot_lock.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_boot_lock/boot_lock.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_boot_lock/boot_lock.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_clocks/clocks.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_clocks/clocks.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_clocks/clocks.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_divider/divider.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_divider/divider.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_divider/divider.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_dma/dma.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_dma/dma.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_dma/dma.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_gpio/gpio.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_gpio/gpio.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_gpio/gpio.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_i2c/i2c.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_i2c/i2c.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_i2c/i2c.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_irq/irq.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_irq/irq.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_irq/irq.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_pio/pio.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_pio/pio.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_pio/pio.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_pll/pll.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_pll/pll.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_pll/pll.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_sync/sync.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_sync/sync.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_sync/sync.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_sync_spin_lock/sync_spin_lock.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_sync_spin_lock/sync_spin_lock.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_sync_spin_lock/sync_spin_lock.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_ticks/ticks.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_ticks/ticks.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_ticks/ticks.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_timer/timer.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_timer/timer.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_timer/timer.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_uart/uart.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_uart/uart.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_uart/uart.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_vreg/vreg.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_vreg/vreg.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_vreg/vreg.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_watchdog/watchdog.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/hardware_xosc/xosc.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_xosc/xosc.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/hardware_xosc/xosc.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_atomic/atomic.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_atomic/atomic.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_atomic/atomic.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_bootrom/bootrom.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_bootrom/bootrom_lock.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_bootrom/bootrom_lock.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_bootrom/bootrom_lock.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_clib_interface/newlib_interface.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_clib_interface/newlib_interface.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_clib_interface/newlib_interface.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_divider/divider_compiler.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_divider/divider_compiler.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_divider/divider_compiler.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_double/double_math.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_double/double_math.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_double/double_math.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_flash/flash.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_flash/flash.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_flash/flash.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_float/float_math.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_float/float_math.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_float/float_math.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_malloc/malloc.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_malloc/malloc.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_malloc/malloc.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_platform_panic/panic.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_platform_panic/panic.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_platform_panic/panic.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_printf/printf.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_printf/printf.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_printf/printf.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_runtime/runtime.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime/runtime.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime/runtime.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init_clocks.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init_clocks.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init_clocks.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init_stack_guard.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init_stack_guard.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_runtime_init/runtime_init_stack_guard.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_standard_binary_info/standard_binary_info.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_standard_binary_info/standard_binary_info.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_standard_binary_info/standard_binary_info.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_stdio/stdio.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_stdio/stdio.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_stdio/stdio.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_stdlib/stdlib.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/src/PCM1681.c" "CMakeFiles/RP2350_TDM_example.dir/src/PCM1681.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/src/PCM1681.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/src/TDM_output.c" "CMakeFiles/RP2350_TDM_example.dir/src/TDM_output.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/src/TDM_output.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/src/main.c" "CMakeFiles/RP2350_TDM_example.dir/src/main.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/src/main.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/src/rp2350_adc.c" "CMakeFiles/RP2350_TDM_example.dir/src/rp2350_adc.c.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/src/rp2350_adc.c.o.d"
  "/home/sebastian/Instruo/tdm_output_example/pico-sdk/src/rp2_common/pico_cxx_options/new_delete.cpp" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_cxx_options/new_delete.cpp.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/pico-sdk/src/rp2_common/pico_cxx_options/new_delete.cpp.o.d"
  "/home/sebastian/Instruo/tdm_output_example/src/blinker.cpp" "CMakeFiles/RP2350_TDM_example.dir/src/blinker.cpp.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/src/blinker.cpp.o.d"
  "/home/sebastian/Instruo/tdm_output_example/src/wrapper.cpp" "CMakeFiles/RP2350_TDM_example.dir/src/wrapper.cpp.o" "gcc" "CMakeFiles/RP2350_TDM_example.dir/src/wrapper.cpp.o.d"
  )

# Targets to which this target links.
set(CMAKE_TARGET_LINKED_INFO_FILES
  )

# Fortran module output directory.
set(CMAKE_Fortran_TARGET_MODULE_DIR "")
