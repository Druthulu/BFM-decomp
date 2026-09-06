extern u32 G, H, J, Q;
extern u8 F;
void g(u32 vol) {
    u32 m, k;
    G = vol;
    if (F != 0) {
        m = vol;
        J = m;
        m >>= 7;
        k = m & 0x7F;
        vol = m;
        Q = k;
    }
    H = vol;
    m = H;
    m++;
    G = m;
}
