/* func_80155D70 — shared body (overlay slot 0x80128158, h_exact fafec753). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 func_801487F4(s32 *a0);
extern void func_801599A4(void *a0);
extern void func_8015E880(s32 *a0);
extern void func_80159B3C(void *a0);
extern void func_8014CC28(s32 a0);
extern s32 func_8014F3E8(s32 a0);
extern void func_8015BDD0(s32 *a0);
void func_80155D70(s32 param_1)
{
    s32 iVar2;
    s32 iVar3;
    char buf[64];
    *(u32 *)(param_1 + 0x44) |= 2;
    if (*(u16 *)(param_1 + 0xB8) == 0x8000) {
        if ((((s32 (*)(void))func_801487F4)() & 0x80) != 0) {
            ((void (*)(s32))func_801599A4)(param_1);
            ((void (*)(s32))func_8015E880)(param_1);
        } else {
            ((void (*)(s32))func_801599A4)(param_1);
            ((void (*)(s32))func_80159B3C)(param_1);
        }
    } else {
        iVar2 = ((s32 (*)(s32))func_8014CC28)(param_1);
        iVar3 = ((s32 (*)(s32))func_8014F3E8)(param_1);
        if (iVar3 == 0 && iVar2 == 0) {
            ((void (*)(s32))func_801599A4)(param_1);
            ((void (*)(s32))func_8015BDD0)(param_1);
        }
    }
    (void)buf;
}
