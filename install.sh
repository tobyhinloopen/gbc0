#!/bin/bash

if [[ "$OSTYPE" == "darwin"* ]]; then
  tar -xf assets/gbdk-macos-arm64.tar
  unzip -q assets/sameboy.zip -d assets/
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
  tar -xzf assets/gbdk-linux64.tar.gz
  unzip -q assets/bgb.zip -d assets/
else
  echo "Unsupported operating system: $OSTYPE"
  exit 1
fi

cd gbdk/examples/gb
make
