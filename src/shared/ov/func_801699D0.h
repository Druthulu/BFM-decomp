/* func_801699D0 — shared body (overlay slot 0x80128158, h_exact 03cde581). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80169A4C(s32 a0, s32 a1);
extern void func_800D22E4(s32 a0);
extern void func_80146C3C();
void func_801699D0(void *arg0) {
    s32 temp_v1;
    temp_v1 = *(s32 *)((u8 *)arg0 + 0x1C);
    if (temp_v1 < 0xF) {
        *(s32 *)((u8 *)arg0 + 0x30) = 0xC0 - temp_v1 * 8;
        func_80169A4C((s32)arg0, (s32)arg0 + 0x38);
        func_800D22E4((s32)arg0);
        *(s32 *)((u8 *)arg0 + 0x14) = *(s32 *)((u8 *)arg0 + 0x14) + 0x10000;
        *(s32 *)((u8 *)arg0 + 0x1C) = *(s32 *)((u8 *)arg0 + 0x1C) + 1;
    } else {
        ((void (*)(s32))func_80146C3C)((s32)arg0);
    }
}
