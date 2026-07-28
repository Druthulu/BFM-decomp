extern void func_8012F038();
extern void func_8012F14C();
extern s32 func_80135888(s32, s32, s32, s32);
extern u16 D_80126B5E;
extern u16 D_80126B62;
extern u16 D_80126B66;
/* derived from the asm (%hi/%lo of D_80126BE0 taken as an address arg); matches the
   `extern u8 D_80126BE0[];` decl already used across the sibling overlays. */
extern u8 D_80126BE0[];

void func_80132F40(s32 arg0)
{
    typedef struct { u16 vx, vy, vz, pad; } Svec_80132F40;

    Svec_80132F40 src;
    Svec_80132F40 dst;
    s16 *p;
    void *ps1;
    void *ps2;
    s32 w;
    s32 h;
    s32 m;

    src.vx = D_80126B5E;
    src.vy = D_80126B62;
    src.vz = D_80126B66;
    dst = src;

    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58),
                      (s32)D_80126BE0, (s32)&dst) != 0) {
        p = (s16 *)((*(s32 *)(arg0 + 0x58) & 0x0FFFFFFF) | 0x80000000);
        w = p[4];
        h = p[5];
        m = w;
        if (h < w) {
            m = h;
        }
        ps1 = &src; __asm__ __volatile__("" : "=r"(ps1) : "0"(ps1));
        func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34, ps1, &dst);
        dst.vy = m;
        ps2 = &src; __asm__ __volatile__("" : "=r"(ps2) : "0"(ps2));
        func_8012F14C(*(s32 *)(arg0 + 0x20) + 0x34, &dst, ps2);
        D_80126B5E = src.vx;
        D_80126B62 = src.vy;
        D_80126B66 = src.vz;
    }
}
