/* func_80177784 — shared body (overlay slot 0x80128158, h_exact 32ad012d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void *func_80177784(void *a0, s32 a1, s32 a2, s32 a3) {
    *(u32 *)((s32)a0 + 0x0) = (((s32)a0 - 0x14) & 0xFFFFFF) | 0x3000000;
    *(u32 *)((s32)a0 + 0x4) = 0x74808080;
    *(s32 *)((s32)a0 + 0x8) = a1;
    *(s32 *)((s32)a0 + 0xC) = a2;
    return (void *)((s32)a0 + 0x14);
}
