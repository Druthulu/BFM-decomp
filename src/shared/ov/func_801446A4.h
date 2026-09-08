/* func_801446A4 — shared body (overlay slot 0x80128158, h_exact 107c1000). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C194(void);
extern void func_8012CAE4(void *a0);
extern s32 func_8001CC3C(s32 a0, s32 a1, s32 a2, s32 a3);
extern void func_80128EA8(s32 a0, s32 a1, s32 a2);
extern u8 D_800D3888[];
extern u8 D_800D387C[];
void func_801446A4(int param_1)
{
    register int s1 __asm__("$17");
    register int iVar1 __asm__("$16");
    s1 = param_1;
    iVar1 = ((int (*)(void))func_8012C194)();
    if (iVar1 == 0) {
        ((void (*)(int))func_8012CAE4)(s1);
    } else {
        *(int *)(s1 + 0xcc) = iVar1;
        ((void (*)(int, int, int, int))func_8001CC3C)(iVar1, 0, 0, 0);
        *(int *)(iVar1 + 0x20) = (int)&D_800D387C;
        *(unsigned char *)(iVar1 + 0x27) = 0x9c;
        *(short *)(iVar1 + 0x1a) = 0x3000;
        *(short *)(iVar1 + 0x18) = 0x3000;
        *(unsigned int *)(iVar1 + 4) = *(unsigned int *)(iVar1 + 4) | 0x50000000;
        func_80128EA8(iVar1, s1 + 0xd0, (int)&D_800D3888);
        *(short *)(iVar1 + 8) = *(unsigned short *)(s1 + 6);
        *(short *)(iVar1 + 0xa) = *(unsigned short *)(s1 + 0xa);
        *(short *)(iVar1 + 0xc) = *(unsigned short *)(s1 + 0xe);
        *(short *)(s1 + 2) = *(short *)(s1 + 2) + 1;
    }
}
