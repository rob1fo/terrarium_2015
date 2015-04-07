#!/bin/bash

lsusb

openocd -f "./resources/openocd/atmel_sam4s_xplained.cfg" -c "program ./nuttx/nuttx.bin verify reset"
