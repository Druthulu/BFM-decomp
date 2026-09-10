void func_80180EDC(void *a0, s32 a1, s32 a2)
{

    extern u8 D_80078EB1;
    s32 v0;
    s32 v1;

    v0 = D_80078EB1;
    if (!(v0 < a1)) {
        if (v0 < a2) {
            v0 = 1;
            v1 = *(s32 *)((s32)a0 + 0xCC);
        } else {
            v1 = *(s32 *)((s32)a0 + 0xCC);
            v0 = 2;
        }
    } else {
        v1 = *(s32 *)((s32)a0 + 0xCC);
        v0 = 2;
    }
    *(s32 *)(v1 + 0xB0) = v0;
}
