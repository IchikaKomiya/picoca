set(ProName "pico-test")
add_executable(${ProName}
        ${ProName}.c
        )

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(${ProName} pico_stdlib hardware_pwm hardware_timer)

# enable usb output
pico_enable_stdio_usb(${ProName} 1)
pico_enable_stdio_uart(${ProName} 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(${ProName})
