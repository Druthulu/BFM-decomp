/* func_801407F4 — shared body (overlay slot 0x80128158, h_exact b86e8046). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_801407F4(void)
{
    u8 *puVar1;
    s32 iVar2;
    u16 *puVar3;

    puVar1 = D_801802D0;
    iVar2 = func_80028D58();
    puVar3 = D_801802E4[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    puVar1 = D_801802D4;
    iVar2 = func_80028DE0();
    puVar3 = D_801802E4[iVar2];
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;

    iVar2 = func_80028FBC();
    *(s16 *)(D_801802D8 + 0x18) = *D_801802EC[iVar2];
    iVar2 = func_80029000();
    *(s16 *)(D_801802DC + 0x18) = *D_801802EC[iVar2];

    puVar1 = D_801802E0;
    iVar2 = func_80028D9C();
    puVar3 = D_8018030C[iVar2];
    *(s16 *)(puVar1 + 0x12) = *puVar3++;
    *(s16 *)(puVar1 + 0x14) = *puVar3++;
    *(s16 *)(puVar1 + 0x16) = *puVar3++;
    *(s16 *)(puVar1 + 0x18) = *puVar3++;
    *(s16 *)(puVar1 + 0x1a) = *puVar3++;
    *(s16 *)(puVar1 + 0x1c) = *puVar3++;
}
