/* func_8013AF20 — shared body (overlay slot 0x80128158, h_exact c7ed6f70). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *func_80010A08(s32);
void func_8013AF20(u32 *param_1, u16 *param_2, u16 *param_3, u8 *param_4)
{
    u32 *puVar3;
    u32 *puVar4;
    u32 *puVar5;
    s32 iVar8;
    s32 j;
    puVar3 = (u32 *)func_80010A08(0x168);
    puVar4 = (u32 *)func_80010A08(0x1e0);
    puVar5 = (u32 *)func_80010A08(0x1e0);
    iVar8 = 0;
    j = 0;
    do {
        *(u8 *)((s32)puVar4 + 3) = 3;
        *(u8 *)((s32)puVar4 + 7) = 0x40;
        *(u8 *)((s32)puVar4 + 4) = 0x3d;
        *(u8 *)((s32)puVar4 + 5) = 0x3d;
        *(u8 *)((s32)puVar4 + 6) = 0x3d;
        *(u16 *)((s32)puVar4 + 8) = param_3[j];
        *(u16 *)((s32)puVar4 + 0xa) = param_3[j + 1];
        iVar8 = iVar8 + 1;
        *(u16 *)((s32)puVar4 + 0xc) = param_3[j + 2];
        *(u16 *)((s32)puVar4 + 0xe) = param_3[j + 3];
        j += 2;
        /* addPrim(param_1, puVar4): setaddr(p, getaddr(ot)), setaddr(ot, p) */
        ((P_TAG *)puVar4)->addr = ((P_TAG *)param_1)->addr;
        ((P_TAG *)param_1)->addr = (u32)puVar4;
        puVar4 = puVar4 + 4;
    } while (iVar8 < 0x1e);
    iVar8 = 0;
    j = 0;
    do {
        iVar8 = iVar8 + 1;
        *(u8 *)((s32)puVar5 + 3) = 3;
        *(u8 *)((s32)puVar5 + 7) = 0x40;
        *(u8 *)((s32)puVar5 + 4) = 0x92;
        *(u8 *)((s32)puVar5 + 5) = 0x92;
        *(u8 *)((s32)puVar5 + 6) = 0x92;
        *(u16 *)((s32)puVar5 + 8) = param_3[j] + (s8)param_4[j];
        *(u16 *)((s32)puVar5 + 0xa) = param_3[j + 1] + (s8)param_4[j + 1];
        *(u16 *)((s32)puVar5 + 0xc) = param_3[j + 2] + (s8)param_4[j + 2];
        *(u16 *)((s32)puVar5 + 0xe) = param_3[j + 3] + (s8)param_4[j + 3];
        j += 2;
        ((P_TAG *)puVar5)->addr = ((P_TAG *)param_1)->addr;
        ((P_TAG *)param_1)->addr = (u32)puVar5;
        puVar5 = puVar5 + 4;
    } while (iVar8 < 0x1e);
    iVar8 = 0;
    j = 0;
    do {
        *(u8 *)((s32)puVar3 + 3) = 5;
        *(u8 *)((s32)puVar3 + 7) = 0x28;
        *(u8 *)((s32)puVar3 + 4) = 0xff;
        *(u8 *)((s32)puVar3 + 5) = 0xff;
        *(u8 *)((s32)puVar3 + 6) = 0xff;
        *(u16 *)((s32)puVar3 + 8) = param_3[j];
        *(u16 *)((s32)puVar3 + 0xa) = param_3[j + 1];
        *(u16 *)((s32)puVar3 + 0xc) = param_2[0];
        *(u16 *)((s32)puVar3 + 0xe) = param_2[1];
        *(u16 *)((s32)puVar3 + 0x10) = param_3[j + 2];
        *(u16 *)((s32)puVar3 + 0x12) = param_3[j + 3];
        iVar8 = iVar8 + 2;
        *(u16 *)((s32)puVar3 + 0x14) = param_3[j + 4];
        *(u16 *)((s32)puVar3 + 0x16) = param_3[j + 5];
        j += 4;
        ((P_TAG *)puVar3)->addr = ((P_TAG *)param_1)->addr;
        ((P_TAG *)param_1)->addr = (u32)puVar3;
        puVar3 = puVar3 + 6;
    } while (iVar8 < 0x1e);
}
