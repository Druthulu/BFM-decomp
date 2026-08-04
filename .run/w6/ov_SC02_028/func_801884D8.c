extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012CAE4(void *a0);
extern void func_80143970(void *a0);
extern void func_8012A828(s32 a0, s32 a1);
extern void func_8012B23C(void *a0);
extern void func_8012B2CC(s32 a0);
extern s32 func_8012C658(s32 arg0, s32 arg1, s32 arg2);
extern s32 rand(void);

void func_801884D8(void *a0) {

    extern u8 D_801AF494[];
    extern u8 D_801BBE74[];
    extern u8 D_801BB73C[];
    extern char D_801BCDEC[];
    extern u8 D_801BCC6C[];
    extern s32 D_801AF5CC;
    extern s32 D_801AF66C;
    extern s32 D_801AF6B4;

    s16 state = *(s16 *)((s32)a0 + 0x70);

    if (func_8012C354((s32)a0, (s32)(D_801AF494 + state * 0x34)) == 0) {
        func_8012CAE4((void *)a0);
    } else {
        s16 state2;
        u16 saved;

        *(u8 *)((s32)a0 + 0xC0) = 1;
        *(s32 *)((s32)a0 + 0xB4) = -0x401;
        func_80143970((void *)a0);

        state2 = *(s16 *)((s32)a0 + 0x70);
        switch (state2) {
            case 0:
                func_8012A828((s32)a0, (s32)D_801BBE74);
                *(s16 *)((s32)a0 + 0x2) = 1;
                func_8012B23C((void *)a0);
                saved = *(u16 *)((s32)a0 + 0xFC);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801AF5CC;
                *(s16 *)((s32)a0 + 0xFC) = 0;
                *(u16 *)((s32)a0 + 0x100) = saved;
                break;
            case 2:
                func_8012A828((s32)a0, (s32)D_801BB73C);
                saved = *(u16 *)((s32)a0 + 0xFC);
                *(s16 *)((s32)a0 + 0x2) = 9;
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801AF66C;
                *(u16 *)((s32)a0 + 0x100) = saved;
                break;
            case 1:
            case 3:
                func_8012A828((s32)a0, (s32)&D_801BCDEC);
                *(s16 *)((s32)a0 + 0x2) = 6;
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801AF6B4;
                break;
            case 4:
                func_8012A828((s32)a0, (s32)D_801BBE74);
                *(s16 *)((s32)a0 + 0x2) = 0xD;
                func_8012B23C((void *)a0);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801AF5CC;
                *(s16 *)((s32)a0 + 0xFC) = 0x1E;
                break;
            case 5:
                if (*(s16 *)((s32)a0 + 0xFC) != 0) {
                    func_8012A828((s32)a0, (s32)D_801BCC6C);
                    *(s16 *)((s32)a0 + 0x2) = 0xE;
                    *(u16 *)(*(s32 *)((s32)a0 + 0x20) + 0x12) = rand() & 0xFFF;
                } else {
                    func_8012A828((s32)a0, (s32)D_801BBE74);
                    *(s16 *)((s32)a0 + 0x2) = 1;
                }
                func_8012B23C((void *)a0);
                *(s32 *)((s32)a0 + 0xBC) = (s32)&D_801AF5CC;
                *(s16 *)((s32)a0 + 0xFE) = 1;
                do {
                    func_8012C658(0x12F, 5, (s32)a0);
                    *(s16 *)((s32)a0 + 0xFE) = *(u16 *)((s32)a0 + 0xFE) + 1;
                } while (*(s16 *)((s32)a0 + 0xFE) < 6);
                *(s16 *)((s32)a0 + 0xFE) = 0;
                break;
            }
        func_8012B2CC((s32)a0);
    }
}
