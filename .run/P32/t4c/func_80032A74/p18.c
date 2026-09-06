/* path (b) attempt: N = r + 4 (live), T = N * 3, X = T - 12 (== r*3 : one mult) */
extern u32 G, H, J;
u32 g(u32 r, u32 *p) {
    u32 n, t, x;
    n = r + 4;
    t = n * 3;
    x = t - 12;
    G = x;
    p[0] = n;
    return n + 1;
}
