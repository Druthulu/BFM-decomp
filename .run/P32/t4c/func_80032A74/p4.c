extern u32 G, H;
extern u8 F;
void g(u32 vol) {
    u32 m;
    G = vol;
    if (F != 0) {
        m = vol;
        m += 3;
        m >>= 7;
        vol = m;
    }
    H = vol;
    m = H * 3;
    G = m >> 14;
}
