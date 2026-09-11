void func_801861FC(s32 a0) {
    s32 ent = a0;
    s32 state = *(u16 *)(ent + 0x34);
    s32 sub;
    s32 cnt;

    switch (state) {
    case 0: {
        s32 t = func_8004787C(*(s32 *)(ent + 0x1C) << 6);
        *(s16 *)(*(s32 *)(ent + 0x20) + 0x18) = t * 7;
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = t << 1;
        cnt = *(s32 *)(ent + 0x1C) + 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt < 0x10) {
            break;
        }
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = 0x7000;
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = 0x2000;
        *(s32 *)(ent + 0x1C) = 0x40;
        *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        break;
    }
    case 1:
        if (func_8012BEE8(ent) != 0) {
            *(s32 *)(ent + 0x1C) = 0x10;
            *(u16 *)(ent + 0x34) = *(u16 *)(ent + 0x34) + 1;
        }
        break;
    case 2: {
        s32 t = func_8004787C(*(s32 *)(ent + 0x1C) << 6);
        sub = *(s32 *)(ent + 0x20);
        *(s16 *)(sub + 0x1A) = t << 1;
        cnt = *(s32 *)(ent + 0x1C) - 1;
        *(s32 *)(ent + 0x1C) = cnt;
        if (cnt == 0) {
            func_8012C218((void *)ent);
            return;
        }
        break;
    }
    }

    func_8018632C(ent);
}
