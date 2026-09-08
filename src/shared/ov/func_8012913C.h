/* func_8012913C — shared body (overlay slot 0x80128158, h_exact 7b5905d9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001D074(s32 a, s32 b);
extern u8 *func_801291C0(void);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
u8 * func_8012913C(s32 arg0)
{
    s32 iVar1;
    u8 *puVar2;
    iVar1 = ((s32(*)(s32,s32))func_8001D074)(0x7E, 0x100);
    if (iVar1 == 0) {
        return (u8 *)0;
    }
    puVar2 = func_801291C0();
    if (puVar2 == (u8 *)0) {
        return (u8 *)0;
    }
    *(s16 *)puVar2 = arg0;
    *(s32 *)(puVar2 + 0x20) = iVar1;
    func_8001CC3C(iVar1, 0, 0, 0);
    return puVar2;
}
