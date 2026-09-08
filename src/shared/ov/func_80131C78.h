/* func_80131C78 — shared body (overlay slot 0x80128158, h_exact ac0a5d19). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80131CA8(s32 a0, s32 a1);
void func_80131C78(s32 a0) {
    s32 v0 = *(s32*)(a0 + 0x20);
    *(s8*)(a0 + 0xC1) = 0;
    *(s16*)(v0 + 0x10) = 0;
    *(s16*)(a0 + 0x5E) = 0;
    func_80131CA8(a0, 0xE);
}
