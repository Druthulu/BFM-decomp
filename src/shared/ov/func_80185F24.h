/* func_80185F24 — shared body (overlay slot 0x80128158, h_exact 8834878f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012E504(s32 a0, s32 a1);
void func_80185F24(void) {
    s32 v1 = func_8012E504(0, 0x29);
    if (v1 != 0) {
        *(s16 *)(v1 + 2) = 0xF;
    }
}
