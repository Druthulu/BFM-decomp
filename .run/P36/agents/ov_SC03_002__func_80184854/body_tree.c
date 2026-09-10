s32 func_80184854(void *a0) {

    extern u8 D_801202A0[];
    u8 *p;
    u8 *end;
    s32 t;
    u16 tag;
    s16 out[3];
    s16 in[3];

    p = D_801202A0;
    end = p + 0x6480;
    if (p != end) {
        do {
            tag = *(u16 *)p;
            if (tag != 0 && tag != 0x61 && func_80184960((s32)p) != 0) {
                t = *(s32 *)(p + 0x20);
                if (t != 0 && *(s32 *)(t + 0x24) != 0 && *(s32 *)(t + 0x4) >= 0) {
                    in[0] = *(u16 *)(p + 0x6);
                    in[1] = *(u16 *)(p + 0xA);
                    in[2] = *(u16 *)(p + 0xE);
                    func_8012F2E8((s32)a0, (s32)in, (s32)out);
                    if (func_8012CB64((s32)out, -0xA0, 0x80, -0xC0, 0x80) != 0) {
                        __asm__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus9)
                        return 1;
                    }
                }
            }
            p += 0x10C;
        } while (p != end);
    }
    return 0;
}
