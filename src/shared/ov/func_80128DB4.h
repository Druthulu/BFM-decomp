/* func_80128DB4 — shared body (overlay slot 0x80128158, h_exact ea0b6163). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80018450(s32 a0, s32 a1);
extern void func_800183E0(s32 a0);
s32 func_80128DB4(s32 a0, s32 *a1) {
    s32 base = a1[0];
    s16 cnt = *(s16 *)((u8 *)a1 + 6);
    if (cnt == 0) {
        return 1;
    }
    cnt = cnt - 1;
    *(s16 *)((u8 *)a1 + 6) = cnt;
    if (cnt > 0) {
        return 0;
    }
    {
        s16 idx = *(s16 *)((u8 *)a1 + 4);
        u32 flags = *(u32 *)(base + idx * 8 + 4);
        if ((flags & 0xC0) == 0xC0) {
            *(s16 *)((u8 *)a1 + 6) = 0;
            return 1;
        }
        if ((flags & 0x80) != 0) {
            *(s16 *)((u8 *)a1 + 4) = 0;
        } else {
            *(s16 *)((u8 *)a1 + 4) = idx + 1;
        }
        *(s16 *)((u8 *)a1 + 6) =
            *(u32 *)(base + *(s16 *)((u8 *)a1 + 4) * 8 + 4) & 0x3F;
        if (a0 != 0) {
            func_80018450(a0, *(s32 *)(base + *(s16 *)((u8 *)a1 + 4) * 8));
        } else {
            func_800183E0(*(s32 *)(base + *(s16 *)((u8 *)a1 + 4) * 8));
        }
        return 0;
    }
}
