extern u32 G, H, Q;
extern u8 F;
void g(u32 vol) {
    u32 m, k;
    G = vol;
    if (F != 0) {
        m = vol;
        k = m & 3;
        m >>= 7;
        Q = k + m;
        vol = m;
    }
    H = vol;
    m = 0;
}
