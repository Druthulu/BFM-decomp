/* func_8017051C — shared body (overlay slot 0x80128158, h_exact ff0f4659). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_800AE6DC;
extern void func_80171928(void *a0);
void func_8017051C(void *a0) {
    *(s16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = D_800AE6DC;
    func_80171928(a0);
}
