/* func_80162968 — shared body (overlay slot 0x80128158, h_exact a44c8b39). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 ratan2(s32 a0, s32 a1);
extern s32 func_80047D3C(s32 a0);
extern void func_80013F3C(s32 a0);
extern void func_800126C4(s32 a0, s32 a1);
extern void func_800123F0(s32 a0, s32 a1);
extern void func_80012558(s32 a0, s32 a1);
void func_80162968(s32 param_1)
{
    register int p __asm__("$18");
    register int iVar4 __asm__("$17");
    register int iVar3 __asm__("$16");
    register int iVar5 __asm__("$19");
    short sVar2;
    int iVar6;
    p = param_1;
    iVar4 = *(int *)(p + 4);
    iVar5 = *(int *)(p + 8);
    iVar3 = p + 0xc;
    *(short *)(iVar5 + 0x10) =
        (short)ratan2((int)*(short *)(iVar4 + 0x84), (int)*(short *)(iVar4 + 0x82));
    sVar2 = (short)func_80047D3C((int)*(short *)(iVar4 + 0x84) * (int)*(short *)(iVar4 + 0x84) +
                                 (int)*(short *)(iVar4 + 0x82) * (int)*(short *)(iVar4 + 0x82));
    *(short *)(iVar5 + 0x14) =
        (short)ratan2((int)*(short *)(iVar4 + 0x80), -(int)sVar2);
    func_80013F3C(iVar3);
    func_800126C4(iVar3, (int)*(short *)(iVar5 + 0x10));
    func_800123F0(iVar3, (int)*(short *)(iVar5 + 0x14));
    func_80012558(iVar3, (int)*(short *)(*(int *)(iVar4 + 0x20) + 0x12));
    func_800126C4(iVar3, 0x400);
    iVar6 = ((0x300 - (int)(short)(*(int *)(p + 0x24) - (unsigned int)*(unsigned short *)(iVar4 + 0xa))) * 0x2000) / 0x300;
    sVar2 = (short)iVar6;
    if ((*(unsigned int *)(iVar4 + 0x44) & 0x400) != 0) {
        sVar2 = (short)iVar6 / 3;
    }
    *(short *)(iVar5 + 0x1c) = sVar2;
    *(short *)(iVar5 + 0x1a) = sVar2;
    *(short *)(iVar5 + 0x18) = sVar2;
    return;
}
