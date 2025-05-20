set(VVV_SOURCE_FILES
    engine.cc
    main.cc
    script.cc
)

add_executable(vvv ${VVV_SOURCE_FILES})
target_link_libraries(vvv PUBLIC ArduinoCore)

arduino_avr_hex(vvv)

set(ARDUINO_PORT "/dev/ttyACM0" CACHE STRING "The serial port for uploading using avrdude")
arduino_avr_upload(vvv ${ARDUINO_PORT})
