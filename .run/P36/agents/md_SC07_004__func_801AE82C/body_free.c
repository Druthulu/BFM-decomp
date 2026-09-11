void func_801AE82C(s32 a0) {
    s32 cnt;
    s32 v1;
    s32 t;
    s32 w;
    s32 frame_pad[1];

    (void)&frame_pad;

    cnt = *(s32 *)((s32)a0 + 0x1C);
    v1 = *(s32 *)((s32)a0 + 0x34);
    if (cnt != 0) {
        *(s32 *)((s32)a0 + 0x1C) = cnt - 1;
    } else {
        t = *(s16 *)(v1 + 0xC);
        w = t + 0;
        if (t < 0x1000) {
            t = w + 0x400;
            *(s16 *)(v1 + 0xC) = t;
            *(s16 *)(v1 + 0x10) = t;
        } else {
            *(u16 *)((s32)a0 + 2) += 1;
            *(s32 *)((s32)a0 + 0x1C) = 0x48;
        }
    }
    if (*(s32 *)((s32)a0 + 0x1C) & 1) {
        func_801ADA10(a0);
    }
}
