/* func_801407F4 — shared body (overlay slot 0x80128158, h_exact cdfae9b4). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801407F4(void)
{
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_8017FB1C;
    iVar2 = func_80028D58();
    puVar3 = D_8017FB30[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_8017FB20;
    iVar2 = func_80028DE0();
    puVar3 = D_8017FB30[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_8017FB24 + 0x18) = *D_8017FB38[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_8017FB28 + 0x18) = *D_8017FB38[iVar2];

    puVar1 = D_8017FB2C;
    iVar2 = func_80028D9C();
    puVar3 = D_8017FB58[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}
