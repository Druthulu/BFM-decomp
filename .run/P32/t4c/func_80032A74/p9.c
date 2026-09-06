extern u32 G, H, J;
extern u8 F;
extern void ext(u32);
void g(u32 vol) {
    u32 m;
    G = vol;
    ext(vol);
    if (F != 0) {
        m = vol;
        m = (m << 3) - m;
        m <<= 4;
        m >>= 7;
        ext(m);
        vol = m;
    }
    H = vol;
    ext(vol);
    m = H;
    m++;
    G = m;
}
