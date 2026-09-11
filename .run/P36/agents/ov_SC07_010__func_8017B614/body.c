s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern s32 D_80126990;
    extern s32 D_80126994;
    extern s16 D_801A7C54;
    extern s16 D_801A94D0;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80185900[];
    extern s16 D_801A7CCC;
    extern s16 D_801A7CCE;
    extern s16 D_801A7CD0;
    extern s16 D_801A7CC4;
    extern s16 D_801A7CC6;
    extern s16 D_801A7CC8;
    extern u8 D_8012694C[];
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_80185900[((u32)param_2) * 0x10];
        a2addr = (s32)&D_80185900[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    *(Blk8_8017B614 *)&D_801A7CCC = *(Blk8_8017B614 *)&buf[0];
    *(Blk8_8017B614 *)&D_801A7CC4 = *(Blk8_8017B614 *)&buf[8];
    func_8012A018((s32)func_8017BE60, 0);
    D_8012694C[0] = 0;
    D_801A94D0 = 1;
    D_801A7C54 = 0x1E;
    D_80126990 = ((SV4_8017B368 *)&D_801A7CCC)->a;
    D_80126994 = D_801A7CCE;
    D_80126998 = D_801A7CD0;
    D_80126984 = ((SV4_8017B368 *)&D_801A7CC4)->a;
    D_80126988 = D_801A7CC6;
    D_8012698C = D_801A7CC8;
    func_80129CF8();
}
