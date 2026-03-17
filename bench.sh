#!/bin/sh

set -eu

if [ "$#" -ne 1 ]; then
        echo "usage: $0 ./binary" >&2
        exit 1
fi

binary="$1"

if [ ! -x "$binary" ]; then
        echo "binary not found or not executable: $binary" >&2
        exit 1
fi

time_once() {
        start_ns="$(date +%s%N)"
        "$binary" >/dev/null
        end_ns="$(date +%s%N)"
        awk -v start="$start_ns" -v end="$end_ns" \
                'BEGIN { printf "%.3f", (end - start) / 1000000000 }'
}

seconds="$(time_once)"
milliseconds="$(awk -v seconds="$seconds" 'BEGIN { printf "%.3f", seconds * 1000 }')"

printf "Binary: %s\n" "$binary"
printf "Time:   %s s\n" "$seconds"
printf "Time:   %s ms\n" "$milliseconds"
