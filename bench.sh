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

best_time() {
        best=""

        "$binary" >/dev/null

        for _ in 1 2 3; do
                current="$(time_once)"
                if [ -z "$best" ]; then
                        best="$current"
                else
                        best="$(awk -v a="$best" -v b="$current" \
                                'BEGIN { if (a < b) printf "%s", a; else printf "%s", b }')"
                fi
        done

        printf "%s" "$best"
}

seconds="$(best_time)"
milliseconds="$(awk -v seconds="$seconds" 'BEGIN { printf "%.3f", seconds * 1000 }')"

printf "Binary: %s\n" "$binary"
printf "Time:   %s s\n" "$seconds"
printf "Time:   %s ms\n" "$milliseconds"
