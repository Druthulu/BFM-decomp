extern u32 G, H;
extern u8 F;
void g(u32 vol) {
    u32 m, a, b;
    G = vol;
    if (F != 0) {
        m = vol;
        a = m << 3;
        b = m << 4;
        m = a - b;
        m >>= 7;
        vol = m;
    }
    H = vol;
    m = H * 3;
    G = m >> 14;
}
