/* func_80160CB4 — shared body (overlay slot 0x80128158, h_exact eb74e19d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80161208();
extern void func_80154150(s32 a0, s32 a1);
extern void func_80154A74(s32 a0, s32 a1);
extern void func_80146CA0(void *a0);
void func_80160CB4(s32 *a0) {
    if (func_80161208() == 0) {
        if (*(u16 *)((u8 *)a0 + 0xB8) == 0x8000) {
            func_80154150((s32)a0, 0x27);
            func_80154A74((s32)a0, 0x1F);
            func_80146CA0(a0);
        }
    }
}
