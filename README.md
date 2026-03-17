# Cache Demo

This project shows how loop order changes matrix multiplication performance.

- `cachedemo.c` runs the cache-friendly `i, k, j` version.
- `solution/row_major.c` is the cache-friendly `i, k, j` example.
- `solution/col_major.c` is the cache-unfriendly `j, k, i` example.
- `bench.sh` times any executable you pass to it and prints the runtime in seconds and milliseconds.

## Build

```sh
make all
```

This produces:

- `./cachedemo`
- `./row_major`
- `./col_major`

## Run

Run the default demo:

```sh
make run
```

Or run a binary directly:

```sh
./cachedemo
./row_major
./col_major
```

## Benchmark

Benchmark any built binary:

```sh
./bench.sh ./cachedemo
./bench.sh ./row_major
./bench.sh ./col_major
```

There are also Make targets:

```sh
make bench
make bench-row
make bench-col
```

## Expected Result

`row_major` should usually run much faster than `col_major`.

The important difference is loop order:

- `i, k, j` reuses `a[i][k]` and walks across rows of `b` and `out`, which is cache-friendly in C.
- `j, k, i` walks down columns of `out` and `a`, which causes much worse locality.

`cachedemo` matches the fast `i, k, j` version.

## Notes

- This is intended for a Linux/Ubuntu-style environment such as a Docker container.
- The checksum output is kept so the compiler cannot optimize the work away.
