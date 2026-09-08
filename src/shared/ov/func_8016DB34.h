/* func_8016DB34 — shared body (overlay slot 0x80128158, h_exact 5e5b0146). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80128ED8(s32 param_1, s32 *param_2);
extern void func_80146C3C();
void func_8016DB34(s32 param_1)
{
    s32 iVar2;
    iVar2 = *(s32 *)(param_1 + 0x20);
    if (((s32 (*)(s32, s32))func_80128ED8)(iVar2, param_1 + 0x24) != 0) {
        ((void (*)(s32))func_80146C3C)(param_1);
    } else {
        *(s8 *)(iVar2 + 0x27) = *(u8 *)(param_1 + 0x28) - 0x70;
        *(s32 *)(param_1 + 0x10) = *(s32 *)(param_1 + 0x10) - 0x60000;
        *(s32 *)(param_1 + 0x14) = *(s32 *)(param_1 + 0x14) + *(s32 *)(param_1 + 0x10);
        *(s32 *)(param_1 + 0x8) = *(s32 *)(param_1 + 0x8) + *(s32 *)(param_1 + 0x14);
        *(s16 *)(iVar2 + 0x18) = *(s16 *)(iVar2 + 0x18) - 0x500;
        *(s16 *)(iVar2 + 0x1a) = *(s16 *)(iVar2 + 0x1a) - 0x300;
    }
}
