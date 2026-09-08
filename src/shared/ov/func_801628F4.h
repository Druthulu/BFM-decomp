/* func_801628F4 — shared body (overlay slot 0x80128158, h_exact 470d0388). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80162968(s32 a0);
void func_801628F4(s32 *a0) {
    s16 *a2 = (s16 *)a0[0x4 / 4];
    s32 *a1 = (s32 *)a0[0x8 / 4];
    if (*(s16 *)((u8 *)a2 + 0x7E) != 0) {
        a1[0x4 / 4] |= 0x80000000;
    } else {
        a1[0x4 / 4] &= 0x7FFFFFFF;
    }
    a0[0x20 / 4] = *(s16 *)((u8 *)a2 + 0x78);
    a0[0x24 / 4] = *(s16 *)((u8 *)a2 + 0x7A);
    a0[0x28 / 4] = *(s16 *)((u8 *)a2 + 0x7C);
    func_80162968((s32)a0);
}
