void func_801860B8(s32 arg0_)
{
    s32 arg0;
    s32 prev;
    u16 flags;
    s32 a;
    s32 diff;
    s32 v;
    s32 d;
    s32 spd;
    s32 e1;
    s32 e2;
    s32 boost;
    s32 tail;

    arg0 = arg0_;
    *(s16 *)(arg0 + 0x5C) = 0;
    boost = (*(u16 *)(arg0 + 0x70) & 1) * 819;
    tail = boost * 2;
    a = D_80126CE0;
    if (a == 0) {
        D_801DA778 = (s16)(boost * 2) + 0x1000;
        D_801DA77C = (s16)(boost * 2) + 0x1000;
    }
    spd = (s16)(boost * 2) + 0x1000;
    a = (spd * (0x90 - a)) / 0x90;

    diff = D_801DA778 - a;
    if (diff > 0) {
        D_801DA778 -= diff >> 2;
    } else if (diff < 0) {
        D_801DA778 += (-diff) / 4;
    }

    prev = D_801DA77C;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801DA778 - prev + spd;
    D_801DA77C = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801DA778 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    e2 = *(s32 *)(arg0 + 0x20);
    d = __builtin_abs(v);
    *(s16 *)(e2 + 0x1C) = d;
    *(s16 *)(e2 + 0x18) = d;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = tail + 0x1000;
}
