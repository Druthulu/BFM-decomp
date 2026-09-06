extern u32 G, H, J, Q;
extern u8 F;
void g(u32 vol) {
    u32 m;
    G = vol;
    if (F != 0) {
        m = vol;
        J = m;
        m >>= 7;
        Q = m;
        vol = m;
    }
    H = vol;
}
