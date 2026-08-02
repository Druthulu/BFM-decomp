extern s32 func_8012C354(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, s32 a1);
extern u8 D_80186448[];
extern u8 D_801A9E84[];
extern u8 D_801A9DA0[];

void func_80180B0C(void *a0) {
    if (func_8012C354((s32)a0, (s32)D_801A9E84) != 0) {
        void *a2 = *(void **)((char *)a0 + 0x20);

        *(s32 *)((char *)a2 + 0x4) |= 0x80000000;
        *(u8 *)((char *)a0 + 0xC0) = 1;

        *(s32 *)((char *)a0 + 0xBC) = (s32)D_801A9DA0;
        *(s32 *)((char *)a0 + 0xC4) |= 0x2;

        func_8012A828((s32)a0, (s32)D_80186448);

        *(u16 *)((char *)a0 + 0x2) = 1;
        *(u8 *)((char *)a0 + 0x75) = 0;
    }
}
