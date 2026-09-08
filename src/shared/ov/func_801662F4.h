/* func_801662F4 — shared body (overlay slot 0x80128158, h_exact da887e0c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_801662F4(void *a0) {
    func_80146A6C(3, a0, *(s16 *)((s32)a0 + 6),
                  (s16)(*(u16 *)((s32)a0 + 0xA) - 0x10),
                  *(s16 *)((s32)a0 + 0xE), 0x8FEFFF4, 0xE000C000);
}
