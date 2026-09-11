void func_801A395C(s32 a0, s32 a1) {
    s32 ret;
    s16 cur;
    s16 t;
    s32 overshot;

    t = (s16)a1;
    cur = *(s16 *)(a0 + 0xA);
    if (cur == t) {
        ret = 1;
    } else {
        if (t < cur) {
            cur -= 2;
            *(s16 *)(a0 + 0xA) = cur;
            overshot = (t < cur);
        } else {
            cur += 2;
            *(s16 *)(a0 + 0xA) = cur;
            overshot = (cur < t);
        }
        if (overshot) {
            ret = 0;
        } else {
            *(s16 *)(a0 + 0xA) = t;
            ret = 1;
        }
    }
}
