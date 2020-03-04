#!/bin/bash
name="MIDIBRK_gerbers"
mkdir -p build/
rm -rf "build/${name}"
rsync -var --update --exclude=".keep" "midi_io/gerbers/" "build/${name}"
rm -f "build/${name}.zip"
cd build && zip -vrT "${name}.zip" "${name}" && rm -rf "${name}"
