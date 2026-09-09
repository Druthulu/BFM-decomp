/* func_8017B614 — shared body (overlay slot 0x80128158, h_exact 2d7795bc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8017B614(s32 param_1, s32 param_2)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern void func_80129CF8(void);
    extern s32 func_8017BE60(void *a0);
    extern u8 D_80182BB8[];
    extern s16 D_8018F98C;
    extern s16 D_8018F98E;
    extern s16 D_8018F990;
    extern s16 D_8018F984;
    extern s16 D_8018F986;
    extern s16 D_8018F988;
    extern u8 D_8012694C;
    extern s32 D_80126998;
    extern s32 D_80126984;
    extern s32 D_80126988;
    extern s32 D_8012698C;

    u8 buf[16];

    if (((u32)param_2) >= 0xB) {
        register u8 *src __asm__("$16");
        __asm__ __volatile__("" : "=r"(src) : "0"((u8 *)((u32)param_2)));
        *(Blk8_8017B614 *)&buf[0] = *(Blk8_8017B614 *)src;
        *(Blk8_8017B614 *)&buf[8] = *(Blk8_8017B614 *)(src + 8);
    } else {
        s32 a1addr = (s32)&D_80182BB8[((u32)param_2) * 0x10];
        s32 a2addr = (s32)&D_80182BB8[((u32)param_2) * 0x10 + 8];
        func_8012F214(param_1, a1addr, (s32)&buf[0]);
        func_8012F214(param_1, a2addr, (s32)&buf[8]);
    }
    {
        s16 *p794 = &D_8018F98C;
        s16 *p78C = &D_8018F984;
        *(Blk8_8017B614 *)p794 = *(Blk8_8017B614 *)&buf[0];
        *(Blk8_8017B614 *)p78C = *(Blk8_8017B614 *)&buf[8];
        ((void(*)(s32, s32))func_8012A018)((s32)func_8017BE60, 0);
        {
            s32 v794, v796, v798, v78C, v78E, v790;
            D_8012694C = 0;
            v794 = *p794;
            v796 = D_8018F98E;
            v798 = D_8018F990;
            v78C = *p78C;
            v78E = D_8018F986;
            v790 = D_8018F988;
            __asm__ __volatile__("");
            D_8018FAB0 = 1;
            D_8018F914 = 0x1E;
            D_80126990 = v794;
            D_80126994 = v796;
            D_80126998 = v798;
            D_80126984 = v78C;
            D_80126988 = v78E;
            D_8012698C = v790;
        }
        func_80129CF8();
    }
}
