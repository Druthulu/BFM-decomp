/* func_801399A8 — shared body (overlay slot 0x80128158, h_exact 6a9c3d32). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_801269F0;
extern s32 D_80126A3C;
s32 func_801399A8(void) {
    s32 iVar2; s32 puVar3; s32 iVar1;
    for (iVar2 = 1, puVar3 = (s32)&D_80126A3C, iVar1 = 0x4C; iVar2 < 3; puVar3 += 0x4C, iVar2++, iVar1 += 0x4C) {
        if (*(s32 *)((s32)&D_801269F0 + iVar1) == 0) return puVar3;
    }
    return 0;
}
