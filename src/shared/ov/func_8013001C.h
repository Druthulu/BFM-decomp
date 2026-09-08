/* func_8013001C — shared body (overlay slot 0x80128158, h_exact 9047781a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BCCC(s32 a0);
extern s32 func_80131AC8(void *a0);
void func_8013001C(void *a0) {
    s32 v0 = func_8012BCCC((s32)a0);
    if (v0 <= 0x8FFF) {
        if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x30)) {
            return;
        }
        ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x31);
    } else {
        if (((s32 (*)(void *, s32))func_80131AC8)(a0, 0x31)) {
            return;
        }
        ((s32 (*)(void *, s32))func_80131AC8)(a0, 0x30);
    }
}
