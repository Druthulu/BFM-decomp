/* func_80172958 — shared body (overlay slot 0x80128158, h_exact bcb1fe7d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80171D1C(void *a0, void *a1, s32 a2);
extern void func_80171A1C(u8 *a0);
extern s32 func_80174650(s32);
extern s16 D_80126B36;
extern s16 D_80126B30;
void func_80172958(u8 * a0)
{
    if (func_80171D1C(a0, &D_80126B30, *(u8 *)&D_80126B36)) {
        func_80171A1C(a0);
        func_80174650((s32)a0);
    }
}
