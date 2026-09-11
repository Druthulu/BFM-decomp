s32 func_800D128C(s32 arg0, s32 arg1) {
    s16 ret = 3;
    s32 flag = 1;
    s32 id = 0;
    s32 obj = (s32)&D_80126B58;
    s32 val;

    switch ((u8)arg0) {
    case 9:
        func_8014BD24(obj, 5);
        val = 0;
        ret = 1;
        break;
    case 106:
        func_8014BB24(obj, 0x12C, 1);
        val = 0x12C;
        break;
    case 1:
        val = 0x96;
        func_8014BB24(obj, 0x96, 1);
        break;
    case 2:
        func_8014BCC0(obj, 5);
        ret = 4;
        /* fallthrough */
    case 13:
    lab1334:
        val = 0x19;
        break;
    case 3:
        func_8014BCC0(obj, 0x19);
        ret = 5;
        goto lab1334;                        /* §162: the backward j is a source goto */
    case 17:
        func_8014BCC0(obj, 5);
        ret = 4;
        val = 0xA;
        break;
    case 18:
        func_8014BCC0(obj, 0xA);
        ret = 5;
        val = 0xA;
        break;
    case 12:
        func_8014BCC0(obj, 5);
        ret = 5;
        val = 2;
        break;
    case 11:
        func_8014BB24(obj, 0x1E, 1);
        val = 0xA;
        break;
    case 8:
        func_8014B944(obj, 0x500000, 1);
        val = 5;
        ret = 2;
        break;
    case 109:
        func_8014B944(obj, 0x900000, 1);
        val = 5;
        ret = 2;
        break;
    case 4:
        ret = 7;
        /* fallthrough */
    case 15:
        val = 0x50;
        break;
    case 5:
        ret = 7;
        /* fallthrough */
    case 16:
        val = 0x96;
        break;
    case 107:
        if ((s16)arg1 >= 0x13) {
            val = 0x14;
        } else {
            val = (s16)arg1 + 2;
        }
        val = val * 25;
        func_8014BD24(obj, val);
        ret = 7;
        break;
    case 6:
        func_8014BD24(obj, 5);
        ret = 7;
        val = 0xFA;
        break;
    case 7:
        func_8014BD24(obj, 5);
        ret = 7;
        val = 0x3E7;
        break;
    case 83:
        func_8014BB24(obj, 0xA, 1);
        val = 0xA;
        break;
    case 84:
        func_8014BCC0(obj, 5);
        ret = 5;
        val = 5;
        break;
    case 85:
        func_8014BB24(obj, 0x32, 1);
        val = 0x32;
        break;
    case 112:
        func_8014BC0C(obj, 0x19);
        ret = 7;
        val = 0x3E7;
        break;
    case 76:
    case 113:
        ret = 7;
        val = 5;
        break;
    case 114:
        func_8014BB24(obj, 0x64, 1);
        /* fallthrough */
    case 14:
        val = 0x32;
        break;
    case 115:
        func_8014BB24(obj, 0x96, 1);
        /* fallthrough */
    case 105:
        val = 0x64;
        break;
    case 116:
        func_8014BB24(obj, 0x96, 1);
        val = 0xC8;
        break;
    case 117:
        func_8014BB24(obj, 0xC8, 1);
        val = 0x96;
        break;
    case 118:
        func_8014BB24(obj, 0xFA, 1);
        /* fallthrough */
    case 104:
        val = 0x12C;
        break;
    case 119:
        func_8014BB24(obj, 0x1F4, 1);
        val = 0x1F4;
        break;
    case 87:
        val = 0xA;
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }

    switch (ret) {
    case 0:
        id = 0x45F;
        flag = 0;
        break;
    case 1:
        id = 0x464;
        func_8014B2A8();
        func_8014BB24(obj, val, 1);
        break;
    case 2:
        func_8014BD24(obj, val);
        id = 0x464;
        break;
    case 3:
        func_8014BD24(obj, val);
        id = 0x45C;
        break;
    case 4:
        func_8014BD24(obj, val);
        id = 0x463;
        break;
    case 5:
        func_8014BD24(obj, val);
        id = 0x465;
        break;
    case 7:
        func_8014BB24(obj, val, 1);
        id = 0x45C;
        break;
    case 8:
        func_8014BCC0(obj, val);
        id = 0x45C;
        break;
    default:
        flag = 0;
        break;
    }

    if ((u16)id != 0) {
        func_8002D4C8((u16)id, 0);
    }
    return flag;
}
