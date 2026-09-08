/* func_801691B8 — shared body (overlay slot 0x80128158, h_exact 298645a7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80169228(void);
extern void func_800D22E4(s32 a0);
extern void func_80146C3C();
void func_801691B8(void *a0) {
    if (*(s32 *)((s32)a0 + 0x1C) < 10) {
        func_80169228();
        func_800D22E4((s32)a0);
        *(s32 *)((s32)a0 + 0x14) += 0x10000;
        *(s32 *)((s32)a0 + 0x1C) += 1;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)a0);
    }
}
