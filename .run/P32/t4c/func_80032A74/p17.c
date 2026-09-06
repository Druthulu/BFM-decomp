/* path (b) attempt with a sign-extend chain on a register value: N = r & 0xFF (live), T = N << 24, X = T >>a 24 */
extern u32 G, H, J;
s32 g(u32 r, u32 *p) {
    u32 n; s32 t, x;
    n = r & 0xFF;
    t = n << 24;
    x = t >> 24;
    G = x;
    p[0] = n;
    return n + 1;
}
