/* path (b) attempt: head N live later, middle T single-use, composition folds to one insn */
extern u32 G, H, J;
u32 g(u32 r, u32 *p) {
    u32 n, t, x;
    n = r & 0xFF;          /* I1: N = r & 0xFF, live later */
    t = n << 24;           /* I2: T = N << 24 */
    x = t >> 24;           /* I3: X = T >> 24  == r & 0xFF == n?  (combine: (lshiftrt (ashift (and r 0xFF) 24) 24) -> (and r 0xFF)) */
    G = x;
    p[0] = n;
    return n + 1;
}
