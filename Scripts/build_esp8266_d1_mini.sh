#!/bin/bash
SCRIPT_DIR=${0%/*}
SKETCH_NAME=ESP_BLINK
CORE=esp8266
BOARD=d1_mini
CPUF=80

bash ${SCRIPT_DIR}/../ESP_Build_Scripts/build_sketch.sh -s ${SKETCH_NAME} -c ${CORE} -b ${BOARD} -f ${CPUF}   