/* func_80161774 — shared body (overlay slot 0x80128158, h_exact 3576d059). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014C010(s32 a0, s32 a1);
extern void func_80161D20();
extern void func_801599A4(void *a0);
extern void func_8015BF48(s32 *a0);
extern s32 func_8014A6C4(s32 a0);
extern void func_8015F2F0(s32 *a0);
extern s16 D_801152B0;
extern s16 D_801152B4;
s32 func_80161774(int a0, u32 a1)
{
    s32 v1;
    s16 v2;
    if ((a1 & 1) != 0) {
        func_8014C010((s32)a0, 1);
        v1 = *(u16 *)((s32)a0 + 0x16E);
        func_80161D20((s32)a0, v1);
        return 1;
    }
    if ((a1 & 0x4000) != 0) {
        func_801599A4(a0);
        func_8015BF48((s32 *)a0);
        func_8014C010((s32)a0, 1);
        v1 = *(u16 *)((s32)a0 + 0x16E);
        func_80161D20((s32)a0, v1);
        return 2;
    }
    if ((a1 & 0x2000) != 0) {
        func_8014C010((s32)a0, 1);
        v1 = *(u16 *)((s32)a0 + 0x16E);
        func_80161D20((s32)a0, v1);
        return 4;
    }
    if ((a1 & 0x8000) != 0) {
        v1 = *(u16 *)((s32)a0 + 0x16C);
        if (v1 != 0x15) {
            return 0;
        }
        v1 = func_8014A6C4((s32)a0);
        if (v1 == 0) {
            return 0;
        }
        func_801599A4(a0);
        func_8015F2F0((s32 *)a0);
        v2 = ratan2(D_801152B0, D_801152B4);
        *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = v2;
        return 8;
    }
    return 0;
}
