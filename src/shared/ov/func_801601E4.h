/* func_801601E4 — shared body (overlay slot 0x80128158, h_exact 9d63aa59). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
extern s32 func_80161208();
void func_801601E4(s32 *a0) {
    if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
        func_80154150((s32)a0, 0x22);
        func_80154A74((s32)a0, 0x1A);
        func_80146CA0(a0);
    } else {
        ((s32 (*)(s32 *))func_80161208)(a0);
    }
}
