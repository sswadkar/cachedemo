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

median_time() {
        run1="$(time_once)"
        run2="$(time_once)"
        run3="$(time_once)"

        printf "%s\n%s\n%s\n" "$run1" "$run2" "$run3" | sort -n | sed -n '2p'
}

seconds="$(median_time)"
milliseconds="$(awk -v seconds="$seconds" 'BEGIN { printf "%.3f", seconds * 1000 }')"

printf "Binary: %s\n" "$binary"
printf "Median: %s s\n" "$seconds"
printf "Median: %s ms\n" "$milliseconds"
