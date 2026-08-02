extern void func_8012B1B4(s32 a0, s32 a1);
extern s32 func_8012CBA4(s32 a0);
extern s32 func_80133784(s32 a0, void *a1, void *a2);
extern s32 D_801AF66C;

void func_801848B0(s32 *s0) {
    typedef struct {
        u16 a, b, c, d;
    } Data_t;

    Data_t buf_src, buf_dst;
    s32 v0;

    func_8012B1B4((s32)s0, (s32)&D_801AF66C);

    v0 = func_8012CBA4((s32)s0);
    if (v0 & 0x6000) {
        return;
    }

    // Load halfwords from s0
    buf_src.a = *(u16 *)((u8 *)s0 + 0x3A);
    buf_src.b = *(u16 *)((u8 *)s0 + 0x3E);
    buf_src.c = *(u16 *)((u8 *)s0 + 0x42);

    // Struct assignment generates lwl/lwr + swl/swr
    buf_dst = buf_src;

    // Modify the b field of buf_dst (at offset 2)
    buf_dst.b += 8;

    v0 = func_80133784((s32)s0, &buf_src, &buf_dst);
    if (v0 == 0) {
        return;
    }

    // Copy three words
    *(s32 *)((u8 *)s0 + 0x04) = *(s32 *)((u8 *)s0 + 0x38);
    *(s32 *)((u8 *)s0 + 0x08) = *(s32 *)((u8 *)s0 + 0x3C);
    *(s32 *)((u8 *)s0 + 0x0C) = *(s32 *)((u8 *)s0 + 0x40);
}
