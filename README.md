# Cache Demo

This project shows how memory access order affects runtime.

- `cachedemo.c` is the main demo program.
- `solution/row_major.c` walks the matrix in row-major order.
- `solution/col_major.c` walks the matrix in column-major order.
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

`row_major` should usually run faster than `col_major` because C stores 2D array data in row-major order, so row-wise traversal has better cache locality.

`cachedemo` matches the row-major version.

## Notes

- This is intended for a Linux/Ubuntu-style environment such as a Docker container.
- The checksum output is kept so the compiler cannot optimize the work away.
