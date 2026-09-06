extern u32 G, H, J;
extern u8 F;
void g(u32 vol) {
    u32 m;
    G = vol;
    if (F != 0) {
        m = vol;
        m = (m << 3) - m;
        m <<= 4;
        m >>= 7;
        J = m & 0x7F;
        vol = m;
    }
    H = vol;
    m = H;
    m++;
    G = m;
}
