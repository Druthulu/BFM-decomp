void func_80183DA0(s32 a0) {
    SVec_80183DA0 pos;
    SVec_80183DA0 out;
    s32 val;
    s32 sv;
    s16 lvl;

    val = 0x7F;
    lvl = 7;
    pos.vx = *(s16 *)(a0 + 0x6);
    pos.vy = *(s16 *)(a0 + 0xA);
    pos.vz = *(s16 *)(a0 + 0xE);
    ((void (*)(void *, void *))func_8012EFB8)(&pos, &out);

    if (out.vx >= 0 ? out.vx < 0x140 : -out.vx < 0x140) {
        sv = (s16)val;
        if (out.vx >= 0) {
            val = sv - out.vx * 0x7F / 0x140;
        } else {
            val = sv - -out.vx * 0x7F / 0x140;
        }
    } else {
        val = 0;
    }

    lvl += out.vx / 0x14;
    if (lvl < 0) {
        lvl = 0;
    } else if (lvl >= 0x10) {
        lvl = 0xF;
    }
    func_8002D4C8(0x730, (u16)(val | ((lvl << 8) | 0x3000)));
}
