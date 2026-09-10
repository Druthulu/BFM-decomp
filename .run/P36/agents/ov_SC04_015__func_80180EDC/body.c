void func_80180EDC(void *a0, s32 a1, s32 a2)
{

    extern u8 D_80078EB1;

    if (D_80078EB1 >= a1 && D_80078EB1 < a2) {
        *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 1;
    } else {
        *(s32 *)(*(s32 *)((s32)a0 + 0xCC) + 0xB0) = 2;
    }
}
