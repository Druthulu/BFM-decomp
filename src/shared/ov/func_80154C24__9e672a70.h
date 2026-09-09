/* func_80154C24 — shared body (overlay slot 0x80128158, h_exact 9e672a70). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80154C24(s32 param_1, s32 *param_2, s32 *param_3) {
    u16 uVar2;
    s32 iVar3;
    s32 uVar5;
    s32 uVar6;

    if (*(u8 *)(param_1 + 0xd4) == 0) {
        return;
    }
    if (*param_2 == 0) {
        *(u16 *)(param_1 + 0xd4) = (u16)*(u8 *)(param_1 + 0xd4);
        *param_2 = *param_2 + 1;
    }
    uVar2 = *(u16 *)(param_1 + 0xd4) - 1;
    *(u16 *)(param_1 + 0xd4) = uVar2;
    if ((uVar2 & 0xff) != 0) {
        goto LAB_80154e6c;
    }
    switch (*(s32 *)((u32)*(u8 *)(param_1 + 0xd8) * 4 + *(s32 *)(param_1 + 0xd0))) {
    case 0:
        *(u16 *)(param_1 + 0xd4) = 0;
        *param_3 = *param_3 | 0x8000;
        *(u16 *)(param_1 + 0xd6) = 0;
        *(u8 *)(param_1 + 0xd8) = 0;
        *(u8 *)(param_1 + 0xd9) = 0;
        break;
    case 1:
        *(u16 *)(param_1 + 0xd4) = 1;
        *param_3 = *param_3 | 0x8000;
        *(u8 *)(param_1 + 0xd8) = 0;
        *(u8 *)(param_1 + 0xd9) = 0;
        func_80154C24(param_1, param_2, param_3);
        break;
    case 2:
        *(u16 *)(param_1 + 0xd4) = 0;
        *(s8 *)(param_1 + 0xd8) = *(s8 *)(param_1 + 0xd8) + 1;
        goto LAB_80154e9c;
    case 3:
        uVar5 = *(s32 *)((u32)*(u8 *)(param_1 + 0xd8) * 4 + *(s32 *)(param_1 + 0xd0) + 4);
        *(u16 *)(param_1 + 0xd4) = 1;
        *(s8 *)(param_1 + 0xd8) = *(s8 *)(param_1 + 0xd8) + 2;
        *(s16 *)(param_1 + 0xd6) = (s16)uVar5;
        func_80154C24(param_1, param_2, param_3);
        break;
    case 5:
        iVar3 = (u32)*(u8 *)(param_1 + 0xd8) * 4 + *(s32 *)(param_1 + 0xd0);
        uVar5 = *(s32 *)(iVar3 + 4);
        uVar6 = *(s32 *)(iVar3 + 8);
        *(u16 *)(param_1 + 0xd4) = 1;
        *(s8 *)(param_1 + 0xd8) = (s8)uVar6;
        *(s32 *)(param_1 + 0xd0) = uVar5;
        func_80154C24(param_1, param_2, param_3);
        break;
    case 6:
        uVar6 = *(s32 *)((u32)*(u8 *)(param_1 + 0xd8) * 4 + *(s32 *)(param_1 + 0xd0) + 4);
        *(u16 *)(param_1 + 0xd4) = 1;
        *(s8 *)(param_1 + 0xd8) = (s8)uVar6;
        func_80154C24(param_1, param_2, param_3);
        break;
    case 7:
        *(u16 *)(param_1 + 0xd4) = *(u16 *)(param_1 + 0xd6);
        *param_3 = *param_3 | 0x4000;
        *(s8 *)(param_1 + 0xd8) = *(s8 *)(param_1 + 0xd8) + 1;
        *(s8 *)(param_1 + 0xd9) = *(s8 *)(param_1 + 0xd9) + 1;
        func_80154C24(param_1, param_2, param_3);
        break;
    case 8:
        *(u16 *)(param_1 + 0xd4) = *(u16 *)(param_1 + 0xd6);
        *param_3 = *param_3 | 0x2000;
        *(s8 *)(param_1 + 0xd8) = *(s8 *)(param_1 + 0xd8) + 1;
        *(s8 *)(param_1 + 0xd9) = *(s8 *)(param_1 + 0xd9) + 1;
        func_80154C24(param_1, param_2, param_3);
        break;
    default:
        func_80154ED8(param_1, *(s32 *)((u32)*(u8 *)(param_1 + 0xd8) * 4 + *(s32 *)(param_1 + 0xd0)));
        *(u16 *)(param_1 + 0xd4) = *(u16 *)(param_1 + 0xd6);
        *(s8 *)(param_1 + 0xd8) = *(s8 *)(param_1 + 0xd8) + 1;
        break;
    }
    goto LAB_80154eac;

LAB_80154e6c:
    if (uVar2 != 1) {
        goto LAB_80154eac;
    }
    if (*(s32 *)((u32)*(u8 *)(param_1 + 0xd8) * 4 + *(s32 *)(param_1 + 0xd0)) != 0) {
        goto LAB_80154eac;
    }
LAB_80154e9c:
    *param_3 = *param_3 | 0x8000;
LAB_80154eac:
    *(u16 *)(param_1 + 0xd4) = *(u16 *)(param_1 + 0xd4) | *param_3;
    return;
}
