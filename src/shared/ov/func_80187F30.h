/* func_80187F30 — shared body (overlay slot 0x80128158, h_exact 1d8b6160). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012AD80(s32 a0);
extern s32 func_8012CEB0(s32 a0, s32 a1, s32 a2);
s32 func_80187F30(void *a0, s32 a1) {
    s16 arr1[3];
    s16 arr2[3];
    s32 res_val;
    arr1[0] = *(u16 *)((s32)a0 + 0x3A);
    arr1[1] = *(u16 *)((s32)a0 + 0x3E) + 0x10;
    arr1[2] = *(u16 *)((s32)a0 + 0x42);
    func_8012AD80((s32)a0);
    arr2[0] = *(u16 *)((s32)a0 + 0x6);
    arr2[1] = *(u16 *)((s32)a0 + 0xA) + 0x10;
    arr2[2] = *(u16 *)((s32)a0 + 0xE);
    res_val = func_8012CEB0((s32)arr1, (s32)arr2, a1);
    *(u16 *)((s32)a0 + 0x6) = arr2[0];
    *(u16 *)((s32)a0 + 0xA) = arr2[1] - 0x10;
    *(u16 *)((s32)a0 + 0xE) = arr2[2];
    if ((res_val & 0x6000) != 0) {
        *(s32 *)((s32)a0 + 0x14) = 0;
    }
    return res_val;
}
