void func_8017E54C(s32 a0)
{
    s32 dmg;
    s32 flag;

    func_8012E9C0(a0);

    dmg = ((s32)*(s16 *)(a0 + 0x60) * (s32)*(s16 *)(*(s32 *)(a0 + 0x78) + 0x30)) >> 12;
    if (dmg <= 0) {
        dmg = 1;
    }

    *(u16 *)(a0 + 0x76) = *(u16 *)(a0 + 0x76) - dmg;

    if (*(u8 *)(a0 + 0xC8) != 0) {
        func_8002A520((void *)a0);
    }
    if (*(u8 *)(a0 + 0xC9) != 0) {
        func_8002A790((void *)a0);
    }

    if (*(s16 *)(a0 + 0x76) <= 0) {
        /* short / "died" path */
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (*(u16 *)(a0 + 0x62) + 0x800) & 0xFFF;
        func_8012B2CC(a0);
        func_8017EBB8((void *)a0);
    } else {
        /* long / "still alive" path */
        if (D_8019F720 == 0) {
            D_8019F720 = 0xF;
            func_8002D4C8(0xA95, 0);
        }

        if ((*(u16 *)(a0 + 0x2) & 0xFFFF) != 8) {
            D_8019F718 = *(u16 *)(a0 + 0x2);
        }

        func_8017EEFC(a0, 8, 0, (s32)&D_80196974);

        *(u16 *)(a0 + 0x5C) = *(u16 *)(a0 + 0x5C) & 0xFFFE;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) = (*(u16 *)(a0 + 0x62) + 0x800) & 0xFFF;
        func_80143B6C(a0, 0);

        *(u8 *)(a0 + 0xC1) = 1;

        *(s32 *)(a0 + 0x1C) = D_80188A1C;
        flag = *(u8 *)(a0 + 0x5E);

        if (flag != 0 && (flag < 5 || flag == 8)) {
            D_8019F70C += 1;
        } else {
            D_8019F70C += 4;
        }

        if (D_8019F70C >= 4) {
            func_8017F13C((void *)a0);
        }
    }
}
