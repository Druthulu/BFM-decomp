void func_80183DA0(s32 a0) {
    SVec_80183DA0 pos;
    SVec_80183DA0 out;
    s32 val;
    s32 lvl;
    s32 sv;
    s32 n;
    s32 t;
    s32 r;

    val = 0x7F;
    pos.vx = *(s16 *)(a0 + 0x6);
    pos.vy = *(s16 *)(a0 + 0xA);
    pos.vz = *(s16 *)(a0 + 0xE);
    ((void (*)(void *, void *))func_8012EFB8)(&pos, &out);
    lvl = 7;

    if (out.vx >= 0) {
        if (out.vx >= 0x140) {
            val = 0;
            goto tail;
        }
    } else {
        if (-out.vx >= 0x140) {
            goto zero;
        }
    }

    sv = (s16)val;
    if (out.vx >= 0) {
        val = sv - out.vx * 0x7F / 0x140;
    } else {
        val = sv - -out.vx * 0x7F / 0x140;
    }
    goto tail;

zero:
    val = 0;

tail:
    t = out.vx;
    n = lvl + t / 0x14;
    lvl = n;
    if ((s16)n < 0) {
        lvl = 0;
    } else if ((s16)n >= 0x10) {
        lvl = 0xF;
    }
    r = (lvl << 8) | 0x3000;
    func_8002D4C8(0x730, (val | r) & 0xFFFF);
}
