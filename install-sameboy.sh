#!/bin/bash
set -e

unzip -q assets/sameboy-1.0.2-source.zip -d assets/sameboy
cd assets/sameboy/SameBoy-1.0.2
make tester || true # || true because `rgbgfx` is missing, but we don't need it.
cd ../../..

mkdir -p assets/sameboy
cp assets/sameboy/SameBoy-1.0.2/build/bin/tester/sameboy_tester assets/sameboy/
unzip -j -o assets/sameboy-macos.zip '*_boot.bin' -d assets/sameboy/
