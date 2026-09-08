/* func_80139634 — shared body (overlay slot 0x80128158, h_exact 20545451). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80059888(void *a0, s32 a1, s32 a2, s32 a3);
void func_80139634(void *a0) {
    s16 sp[4];
    sp[0] = *(u16 *)((u8 *)a0 + 0x38);
    sp[1] = *(u16 *)((u8 *)a0 + 0x3A);
    sp[2] = 0x38;
    sp[3] = 0x30;
    func_80059888(&sp[0], 0, 0, 0);
}
