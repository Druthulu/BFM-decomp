void func_8017F0F4(s32 a0)
{
    s16 hi;
    s16 pos;
    s32 sp10[3];
    u16 state;
    s32 ret;

    hi = *(s16 *)(a0 + 0x8A);
    pos = *(s16 *)(a0 + 0xA);

    if (pos >= hi - 8) {
        if (*(s32 *)(a0 + 0x48) >= 0) {
            *(s32 *)(a0 + 0x48) = -0x8000;
            *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
        }
    } else {
        if (hi + 8 >= pos) {
            if (*(s32 *)(a0 + 0x48) <= 0) {
                *(s32 *)(a0 + 0x48) = 0x8000;
                *(s32 *)(a0 + 0x14) = *(s32 *)(a0 + 0x14) >> 1;
            }
        }
    }

    if (*(s32 *)(a0 + 0xDC) < -0x40000) {
        *(s32 *)(a0 + 0xDC) = -0x40000;
    }

    sp10[0] = 0;
    sp10[1] = 0;
    sp10[2] = *(s32 *)(a0 + 0xDC);
    ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
    func_8012CBCC(a0);

    state = *(u16 *)(a0 + 0x34);
    switch (state) {
    case 0: {
        s32 s0v;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        s32 p20;

        s0v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s0v);
        if (ret <= 0x3FFFF) {
            if (func_8017EA54(a0, 0x51) == 0) {
                goto set_state1;
            }
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s0v);
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 8);
        p20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) &= 0xFFF;
        ((void (*)(s32, s32))func_8012B1B4)(a0, (s32)sp10);
        break;
    }
    case 1: {

        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88));
        if (ret > 0x3FFFF) {
            goto rand_tail;
        }
        if (func_8017EA54(a0, 0x51) == 0) {
            goto end_switch;
        }
        goto rand_tail;
    }
    case 2: {
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;
        s32 p20;

        p744 = func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88));
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 0x10);
        p20 = *(s32 *)(a0 + 0x20);
        *(u16 *)(p20 + 0x12) = *(u16 *)(p20 + 0x12) + b608;
        v1p = *(s32 *)(a0 + 0x20);
        *(u16 *)(v1p + 0x12) = *(u16 *)(v1p + 0x12) & 0xFFF;
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) >> 1;
        func_8017EA54(a0, 0x51);
        if (*(s16 *)(a0 + 0x102) == 0) {
            *(u16 *)(a0 + 0x34) = 3;
        } else {
            *(s16 *)(a0 + 0x102) = *(s16 *)(a0 + 0x102) - 1;
        }
        break;
    }
    case 3: {
        s32 s2v;
        s32 p744;
        s32 v1p;
        s16 snd;
        s32 b608;

        s2v = a0 + 0x88;
        ret = ((s32 (*)(s32, u16 *))func_8012BE98)(a0, (u16 *)s2v);
        *(s32 *)(a0 + 0xDC) = *(s32 *)(a0 + 0xDC) << 1;
        if (func_8017EA54(a0, 0x51) != 0) {
            goto rand_tail;
        }
        if (ret <= 0x40000) {
            goto set_state1;
        }
        p744 = func_8012B744((void *)(a0 + 4), (void *)s2v);
        v1p = *(s32 *)(a0 + 0x20);
        snd = *(s16 *)(v1p + 0x12);
        b608 = func_8012B608(snd, p744, 1);
        if ((u32)(b608 + 0xFF) < 0x1FF) {
            goto end_switch;
        }
        goto rand_tail;
    }
    }
    goto end_switch;

rand_tail:
    *(u16 *)(a0 + 0x34) = 2;
    {
        s32 r = rand();
        *(s16 *)(a0 + 0x102) = (r & 7) + 8;
    }
    goto end_switch;

set_state1:
    *(u16 *)(a0 + 0x34) = 1;

end_switch:
    if (*(s16 *)(a0 + 0x100) != 0) {
        *(s16 *)(a0 + 0x100) = *(s16 *)(a0 + 0x100) - 1;
    } else {
        s32 ret3;

        ret3 = ((s32 (*)(s32))func_8012BE54)(a0);
        if (ret3 <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 2;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}
