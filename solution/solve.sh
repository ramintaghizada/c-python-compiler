#!/usr/bin/env bash
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
mkdir -p /app/ccomp
cp "$HERE"/ccomp/*.py /app/ccomp/
