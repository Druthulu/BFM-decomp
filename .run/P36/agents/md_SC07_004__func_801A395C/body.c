s32 func_801A395C(s32 a0, s32 a1) {
    s16 cur;
    s32 overshot;
    s16 t;

    t = a1;
    cur = *(s16 *)(a0 + 0xA);
    if (cur == t) {
        return 1;
    }
    if (t < cur) {
        cur -= 2;
        *(s16 *)(a0 + 0xA) = cur;
        overshot = t < cur;
    } else {
        cur += 2;
        *(s16 *)(a0 + 0xA) = cur;
        overshot = cur < t;
    }
    if (overshot) {
        return 0;
    }
    *(s16 *)(a0 + 0xA) = t;
    return 1;
}
