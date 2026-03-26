#!/usr/bin/env bash
set -euo pipefail

KEYBOARD="keyball44"
KEYMAP="iusztin"

QMK_FIRMWARE_VERSION="0.22.14"
QMK_HOME="$(pwd)/__qmk__"

# git config --global --add safe.directory '*'

echo "==> Cloning qmk_firmware @ ${QMK_FIRMWARE_VERSION}"
if [ ! -d "__qmk__" ]; then
  git clone https://github.com/qmk/qmk_firmware.git \
    --depth 1 \
    --recurse-submodules \
    --shallow-submodules \
    -b "${QMK_FIRMWARE_VERSION}" \
    __qmk__
else
  echo "    __qmk__ already exists, skipping clone"
fi

echo "==> Setting up QMK home"
qmk setup --home "${QMK_HOME}" --yes

echo "==> Installing symlink for keyball keyboards"
ln -sf "$(pwd)/qmk_firmware/keyboards/keyball" "${QMK_HOME}/keyboards/keyball"

echo "==> Installing Python dependencies"
/usr/bin/python3 -m pip install -r "${QMK_HOME}/requirements.txt"

echo "==> Compiling keyball/${KEYBOARD}:${KEYMAP}"
QMK_HOME="${QMK_HOME}" qmk compile -j 4 -kb "keyball/${KEYBOARD}" -km "${KEYMAP}"

qmk flash -j 4 -kb "keyball/${KEYBOARD}" -km "${KEYMAP}"

echo "==> Copying firmware to ./firmware/"
mkdir -p firmware
cp "${QMK_HOME}"/*.hex firmware/

echo "==> Done. Firmware files:"
ls firmware/
