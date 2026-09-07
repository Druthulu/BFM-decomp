/* tests/fixture.c — the test fixture's source. NOT game code: two small functions written for the test, compiled with
 * the toolchain xsig was built for (gcc-2.7.2-psx cc1 -O2 -G0 -mips1 -mcpu=3000 -mgas -msoft-float -fgnu-linker →
 * maspsx --aspsx-version=2.56 --expand-div → mipsel-linux-gnu-as) and linked TWICE at different addresses with
 * --emit-relocs (see make_fixtures.sh). `fixture` exercises every field xsig masks — a jal (26-bit target), a %hi/%lo
 * pair for a global (HI16/LO16) — and one it keeps (a PC-relative branch); `other` is the discrimination control. */
extern int table[8];
extern int helper(int);

int fixture(int n) {
    int i, acc = 0;
    for (i = 0; i < n; i++) {
        acc += table[i & 7];
        if (acc > 100) acc = helper(acc);
    }
    return acc;
}

int other(int a, int b) {
    return (a * 3) ^ (b >> 2);
}
