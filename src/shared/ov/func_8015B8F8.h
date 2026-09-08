/* func_8015B8F8 — shared body (overlay slot 0x80128158, h_exact 94eda480). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801542DC(s32 *a0, s32 a1);
extern void func_80154150(s32 a0, s32 a1);
extern s32 D_800D4A9C;
extern s32 D_800D4B48;
void func_8015B8F8(s32 *a0) {
    s32 v = *(s32 *)((s32)a0 + 0x23C);
    if (v == (s32)&D_800D4A9C || v == (s32)&D_800D4B48) {
        ((void (*)(s32 *, s32, s32))func_801542DC)(a0, v, *(u8 *)((s32)a0 + 0x244));
    } else {
        func_80154150((s32)a0, 0xF);
    }
}
