/* func_8017D804 — shared body (overlay slot 0x80128158, h_exact ef7c957e). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8004787C(s32 a0);
extern s32 func_80146E98(s32 a0);
void func_8017D804(s32 param) {
    s32 a0;
    s32 v0;
    s32 v1;
    s32 *s1;
    a0 = *(s32 *)(param + 0x1C) & 0x3F;
    s1 = (s32 *)(*(s32 *)(param + 0x20));
    v0 = func_8004787C(a0 << 6);
    v1 = *(s32 *)(param + 0x10);
    if (v0 < 0) {
        v0 += 0x7F;
    }
    v0 = v0 >> 7;
    v1 = v1 + v0;
    v0 = v1;
    *(s16 *)((u8 *)s1 + 0x1A) = v0;
    *(s16 *)((u8 *)s1 + 0x18) = v0;
    v0 = *(s32 *)(param + 0x10);
    *(s32 *)(param + 0x10) = v0 + 0x20;
    if (func_80146E98(param) != 0) {
        v0 = *(u16 *)(param + 0x2);
        *(s16 *)(param + 0x2) = v0 + 1;
    }
}
