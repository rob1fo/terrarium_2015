#!/bin/bash

export PATH=$PATH:$PWD/kconfig-nuttx/bin

cd nuttx

APPSDIR=../apps kconfig-nuttx-mconf Kconfig

cd ..

