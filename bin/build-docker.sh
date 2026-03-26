#!/usr/bin/env bash
set -euo pipefail

docker run --rm \
  -v "$(pwd):/workspace" \
  --privileged \
  -v /dev:/dev \
  -w /workspace \
  ghcr.io/qmk/qmk_cli@sha256:2dc05fc9f32efebd6b05c2b8676ee548358bc7e151e9dbf4dac6b6eed4513b07 \
  bash bin/_build-docker.sh
