CC ?= gcc
CFLAGS := -O3 -Wall -Wextra -std=c11
CPPFLAGS := -DSIZE=1024
BINARIES := cachedemo row_major col_major

.PHONY: all run bench bench-row bench-col clean

all: $(BINARIES)

cachedemo: cachedemo.c
	$(CC) $(CPPFLAGS) $(CFLAGS) cachedemo.c -o cachedemo

row_major: solution/row_major.c
	$(CC) $(CPPFLAGS) $(CFLAGS) solution/row_major.c -o row_major

col_major: solution/col_major.c
	$(CC) $(CPPFLAGS) $(CFLAGS) solution/col_major.c -o col_major

run: cachedemo
	./cachedemo

bench: cachedemo
	sh ./bench.sh ./cachedemo

bench-row: row_major
	sh ./bench.sh ./row_major

bench-col: col_major
	sh ./bench.sh ./col_major

clean:
	rm -f $(BINARIES)
