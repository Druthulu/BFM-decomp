/* func_8018C3F0 — shared body (overlay slot 0x80128158, h_exact 52d19dc6). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_8012BD14(s32 a0);
extern s32 func_80178BF8();      /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2539/2541) */
extern void func_80172710(void); /* TU-canonical (ov_SC04_018_jr_8017AE2C.c L2231) */
extern u16 D_80126B5E;
extern u16 D_80126B66;
s32 func_8018C3F0(void *a0)
{
    s32 field;
    s32 *p;
    s32 v0;
    field = *(s32 *)((s32)a0 + 0x64);
    if (*(u16 *)(field + 0x2) != 2) {
        return 0;
    }
    if (func_8012BD14(field) >= 0x6401) {
        return 0;
    }
    if (*(s16 *)&D_80126B5E >= 0x281) {
        return 0;
    }
    if (*(s16 *)&D_80126B66 < -0x380) {
        return 0;
    }
    p = *(s32 **)((s32)a0 + 0x64);
    v0 = *(u16 *)((s32)p + 0x2) + 1;
    *(u16 *)((s32)p + 0x2) = v0;
    func_80178BF8();
    return (s32)func_80172710;
}
