s32 func_8017B238(s32 param_1, s32 param_2)
{

    extern s16 D_801F5FF4;
    extern s16 D_801F62F8;
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_8018DD4C[];
    extern s16 D_801F606C;
    extern s16 D_801F6064;
    extern u8 D_8012694C;

    u8 buf[16];
    u8 *src;

    if (((u32)param_2) >= 0xB) {
        src = (u8 *)((u32)param_2);
        *(Blk8_8017B238 *)&buf[0] = *(Blk8_8017B238 *)src;
        *(Blk8_8017B238 *)&buf[8] = *(Blk8_8017B238 *)(src + 8);
    } else {
        s32 a2addr;

        src = &D_8018DD4C[((u32)param_2) * 0x10];
        a2addr = (s32)&D_8018DD4C[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, (s32)src, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_801F606C;
        s16 *p78C = &D_801F6064;
        *(Blk8_8017B238 *)p794 = *(Blk8_8017B238 *)&buf[0];
        *(Blk8_8017B238 *)p78C = *(Blk8_8017B238 *)&buf[8];
        func_8012A018((s32)func_8017BE60, 0);
        D_8012694C = 0;
        D_801F62F8 = 1;
        D_801F5FF4 = 0;
    }
}
