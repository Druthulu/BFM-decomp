extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801E2FBC[];
extern u8 D_801E3980[];
extern u8 D_801E3760[];

void func_8018A06C(void *a0) {
    s32 ptr;
    unsigned short v1;
    unsigned short v0;

    if (func_8012C354((s32)a0, (s32)D_801E2FBC) == 0) {
        return;
    }

    ptr = *(s32 *)((s32)a0 + 0x64);
    v1 = *(unsigned short *)(ptr + 0x36);
    v0 = *(unsigned short *)((s32)a0 + 0x70);
    *(unsigned short *)((s32)a0 + 0xFC) = v1;

    if (v0 & 0x4000) {
        func_8012A828((s32)a0, D_801E3980);
        *(unsigned short *)((s32)a0 + 0x5C) = 0;
    } else {
        func_8012A828((s32)a0, D_801E3760);
    }

    *(unsigned short *)((s32)a0 + 0x2) = 1;
}
