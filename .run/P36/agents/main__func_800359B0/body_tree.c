void func_800359B0(s32 arg0) {
    u8 result[8];
    s32 sync;

    switch (*(u8 *)(arg0 + 3)) {
    case 1:
    case 2:
        func_800434BC();
        *(u8 *)(arg0 + 2) = 0;
        break;
    case 4:
        func_800434BC();
        *(u8 *)(arg0 + 2) = 1;
        *(u8 *)(arg0 + 3) = 0x10;
        break;
    case 6:
    case 7:
        func_8003EDE8(0, (u32)((D_8006AEEC * D_800A4EFA) >> 7 & 0xFF) * 3 >> 2,
                      (u32)((D_8006AEEC * D_800A4EFA) >> 7 & 0xFF) * 3 >> 2);
        *(u8 *)(arg0 + 2) = 1;
        D_8007620C = 0;
        *(u8 *)(arg0 + 3) = 0xB;
        break;
    case 5:
        func_800434BC();
        *(u8 *)(arg0 + 3) = 8;
        /* fall through */
    case 8:
        func_8003EDE8(0, 0, 0);
        if (func_800435CC(9, 0, 0) == 0) {
            *(u8 *)(arg0 + 2) = 1;
            *(u8 *)(arg0 + 3) = 0x10;
            D_80076104 = 0;
            return;
        }
        D_8007620C = 0;
        D_80076104 = 0;
        *(u8 *)(arg0 + 3) = 9;
        /* fall through */
    case 9:
        sync = func_8004355C(1, result);
        if (sync == 0) {
            D_80076104 = D_80076104 + 1;
            if ((s16)D_80076104 >= 0x12D) {
                func_800434BC();
            do_flag:
                D_80076214 = 1;
                *(u8 *)(arg0 + 2) = 0;
                return;
            }
            *(u8 *)(arg0 + 2) = 1;
            return;
        }
        if (sync == 5 && (result[0] & 0x10)) {
            D_80076214 = 1;
        }
        *(u8 *)(arg0 + 2) = 0;
        break;
    case 11:
        func_8003EDE8(0, D_8006AEEC >> 1, D_8006AEEC >> 1);
        *(u8 *)(arg0 + 3) = 0xC;
        break;
    case 12:
        func_8003EDE8(0, D_8006AEEC >> 2, D_8006AEEC >> 2);
        *(u8 *)(arg0 + 3) = 0xD;
        break;
    case 13:
        func_8003EDE8(0, 0, 0);
        if (func_800435CC(9, 0, 0) != 0) {
            *(u8 *)(arg0 + 3) = 9;
            return;
        }
        *(u8 *)(arg0 + 3) = 0x10;
        D_80076104 = 0;
        break;
    case 16:
        if (func_800435CC(9, 0, 0) == 0) {
            D_80076104 = D_80076104 + 1;
            if ((s16)D_80076104 >= 0x12D) {
                func_800434BC();
                __asm__ __volatile__("");   /* §336 cross-jump fence, zero bytes */  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                goto do_flag;
            }
            break;
        }
        *(u8 *)(arg0 + 3) = 9;
        break;
    case 0:
    case 3:
    case 10:
    case 14:
    case 15:
    case 17:
    case 18:
    default:
        *(u8 *)(arg0 + 2) = 0;
        break;
    }
}
