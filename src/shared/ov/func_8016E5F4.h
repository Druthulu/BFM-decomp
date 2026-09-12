/* func_8016E5F4 — shared body (overlay slot 0x80128158, h_exact 6dfa7d50). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern s32 func_8012EFB8(void *param_1, void *param_2);
extern void func_80146C3C();
extern void func_80015954(s32 a0, s32 a1);
void func_8016E5F4(s32 arg0) {
    s32 sp10;
    func_80015978(arg0 + 4, &sp10);
    if ((((s32 (*)(s32, s32))func_8012EFB8)((s32)&sp10, (s32)&sp10) & 0xFFFFEFFF) != 0) {
        ((void (*)(s32))func_80146C3C)(arg0);
    } else {
        func_80015954((s32)&sp10, arg0 + 4);
        *(s16 *)((u8 *)arg0 + 0x10) = 0x100;
        *(s16 *)((u8 *)arg0 + 0x12) = 0;
        *(s16 *)((u8 *)arg0 + 0x14) = 0;
        *(s16 *)((u8 *)arg0 + 0x16) = 0x80;
        *(s16 *)((u8 *)arg0 + 2) = *(u16 *)((u8 *)arg0 + 2) + 1;
    }
}
