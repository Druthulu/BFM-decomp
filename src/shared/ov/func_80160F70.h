/* func_80160F70 — shared body (overlay slot 0x80128158, h_exact e2425cb2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146E98(s32 a0);
extern void func_800D0F4C(s32 a0);
extern void func_8014BB24(s32 a0, s32 a1, s32 a2);
extern void func_8014BD24(s32 a0, s32 a1);
extern s32 func_8013767C(s32 a0);
extern void func_80146CA0(void *a0);
extern u8 D_80110EC0;
void func_80160F70(s32 a0) {
    if (func_80146E98(a0) != 0) {
        func_800D0F4C(0xA);
        func_8014BB24(a0, 0x96, 0);
        func_8014BD24(a0, 0x96);
        *(s32 *)(a0 + 0x198) = func_8013767C(&D_80110EC0);
        func_80146CA0((void *)a0);
    }
}
