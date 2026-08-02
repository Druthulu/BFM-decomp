/* Declarations copied VERBATIM from src/ov_SC03_014/ov_SC03_014_jr_801848E4.c
 * (func_80029178 @ line 58/3176, func_80029124 @ line 43/3253,
 *  func_80178CBC @ line 2537).  The D_801E3* globals are not declared
 *  anywhere in the TU. */
extern s32 D_801E31D4;
extern s32 D_801E31C0;
extern s32 D_801E31BC;
extern s32 D_801E3254;
extern s32 D_801E31E8;
extern s32 D_801E30B4[];
extern s32 D_801E3138[];
extern s32 func_80029178(s32 arg);
extern void func_80029124(s32 a0, s32 a1);
extern void func_80178CBC(s32 arg0, s32 arg1);

void func_80189C7C(void *a0) {
    s32 *s0;
    s32 *p;
    u16 v0;

    s0 = *(s32 **)((char *)a0 + 0xDC);
    v0 = *(u16 *)((char *)s0 + 0x8);

    if (!(v0 & 0x8000)) {
        v0 = (func_80029178(0x1D)) & 0xFF;

        if (v0 != 0) {
            u16 flags2;
            D_801E31D4 = *(s32 *)((char *)s0 + 0x4);
            flags2 = *(u16 *)((char *)s0 + 0x8);

            if (!(flags2 & 0x4000)) {
                v0 = *(u16 *)((char *)s0 + 0xC);
                D_801E31BC = 0;
                D_801E31C0 = D_801E3138[v0];
            } else {
                D_801E31C0 = 0;
                v0 = *(u16 *)((char *)s0 + 0xC);
                func_80029124(D_801E3138[v0], 1);
                D_801E31BC = 2;
            }
        } else {
            D_801E31D4 = *(s32 *)((char *)s0 + 0x0);
            v0 = *(u16 *)((char *)s0 + 0xC);
            D_801E31BC = 0;
            D_801E31C0 = D_801E30B4[v0];
        }

        func_80178CBC((s32)a0, (s32)&D_801E31E8);
    } else {
        p = &D_801E3254;
        *p = *(s32 *)((char *)s0 + 0x0);
        func_80178CBC((s32)a0, (s32)(p - 7));
    }

    *(u16 *)(a0 + 0x2) = 4;
    *(u16 *)(a0 + 0x70) |= 0x8000;
}
