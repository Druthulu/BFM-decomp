void func_801AB54C(void *a0) {
    s32 v;
    s32 c;
    s32 p;
    s32 frame_pad[4];
    register s32 z __asm__("$0");  // !FAKE: pin $0 — NEEDED DIFFERS (P36 rung B tus9)

    func_801A8494(a0);

    if (*(s32 *)((s32)a0 + 0x1C) != 0) {
        *(s32 *)((s32)a0 + 0x1C) -= 1;
        return;
    }

    p = *(s32 *)((s32)a0 + 0x20);
    v = *(s16 *)(p + 0x18);
    c = v + z;
    if (v < 0x600) {
        v = c + 0x100;
        *(s16 *)(p + 0x18) = v;
    }

    p = *(s32 *)((s32)a0 + 0x20);
    v = *(s16 *)(p + 0x1A);
    c = v + z;
    if (v < 0xA00) {
        v = c + 0x140;
        *(s16 *)(p + 0x1A) = v;
    }

    (void)&frame_pad;
}
