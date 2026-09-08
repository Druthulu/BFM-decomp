/* func_80175624 — shared body (overlay slot 0x80128158, h_exact 6fa48c7e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_800B9A02;
extern void func_801757A0(s32);
void func_80175624(void *a0) {
    func_801757A0(D_800B9A02);
    *((u8 *)a0 + 1) = *((u8 *)a0 + 1) + 1;
}
