/* func_8014032C — shared body (overlay slot 0x80128158, h_exact ba377f7b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8014032C(s32 param_1, s32 param_2) {
    extern int (*D_8018065C[])(void);
    extern int (*D_8018064C[])(void);
    extern void * D_80180368[];
    extern void * D_80180398[];
    extern void * D_801803A8[];
    extern void * D_80180380[];
    extern u8 D_80180338[];
    extern void * D_801803C0[];
    extern void * D_801803D8[];
    extern void * D_801803EC[];
    extern u8 D_8018033F[];
    extern u8 * D_8018E7C4;
    extern u8 D_801117EC[];
    extern u8 D_801117B4[];
    extern u8 D_80112BC8[];
    extern u8 D_80112B58[];
    extern u8 D_80112BA8[];
    extern u8 D_80112B90[];


    int cVar1;
    unsigned int uVar3;
    void *result;

    result = D_801117EC;
    switch (((short)param_1)) {
    case 0:
        if (((s32(*)(s32))func_80029178)(D_80180314[((short)param_2)]) & 0xFF) {
            result = D_80180368[((short)param_2)];
        }
        break;
    case 1:
        result = D_80180398[((short)param_2)];
        break;
    case 2:
        switch ((*(s16*)&D_80115128)) {
        case 0:
            if (D_8018065C[((short)param_2)]() == 0) {
                ((short)param_2) = 5;
            } else if (D_8018064C[((short)param_2)]() != 0) {
                ((short)param_2) = 4;
            }
            result = D_801803A8[((short)param_2)];
            break;
        case 1:
            goto case5;
        case 2:
            if (((s32(*)(s32))func_80029178)(D_8018E7C4[((short)param_2)]) & 0xFF) {
                if (((short)param_2) == 5 && (((s32(*)(s32))func_80029178)(0x1C) & 0xFF)) {
                    result = D_801117B4;
                } else {
                    result = D_80180380[((short)param_2)];
                }
            }
            break;
        case 3:
            if (((s32(*)(s32))func_80029178)(D_80180338[((short)param_2)]) & 0xFF) {
                result = D_801803C0[((short)param_2)];
            }
            break;
        case 4:
            result = D_801803D8[((short)param_2)];
            break;
        }
        break;
    case 5:
    case5:
        uVar3 = ((s32(*)(s32))func_800291B4)(D_8018032C[((short)param_2)]) & 0xFF;
        if (uVar3 != 0) {
            result = D_801803EC[uVar3];
        }
        break;
    case 3:
        if (((short)param_2) != 0) {
            cVar1 = ((s32(*)(s32))func_800291B4)(D_8018033F[((short)param_2)]) & 0xFF;
            if (cVar1 == 0) {
                result = D_80112B58;
            } else {
                result = D_80112BA8;
                if (cVar1 == 1) {
                    result = D_80112B90;
                }
            }
        } else {
            result = D_80112BC8;
        }
        break;
    case 6:
    case 7:
    default:
        result = 0;
        break;
    }
    return result;
}
