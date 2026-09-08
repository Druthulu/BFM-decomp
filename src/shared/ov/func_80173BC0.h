/* func_80173BC0 — shared body (overlay slot 0x80128158, h_exact a2c3e966). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s16 D_80126B3A;
extern struct S80126B38 D_80126B38;
extern s16 D_8011F9C8;
extern s32 func_800D0EC4(void);
extern void func_8013E588(void*);
extern s32 func_80174650(s32);
extern void func_80171A34(s32 *a0, s8 a1);
extern void func_80171A1C(u8 *a0);
void func_80173BC0(u8* a0)
{
    s32 v = D_80126B3A;
    if (v != 0 && v < 0x6F && func_800D0EC4() == 0) {
        if ((*(s16 *)&D_80126B38) & 0x8000) {
            ((void (*)(void))func_8013E588)();
        } else {
            func_80174650((s32)a0);
            D_8011F9C8 = 2;
            func_80171A34(a0, 7);
            return;
        }
    }
    func_80171A1C((u8 *)a0);
}
