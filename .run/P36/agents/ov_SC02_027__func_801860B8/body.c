void func_801860B8(s32 arg0_)
{
    s32 arg0;
    s32 a;      /* the level, the ramp target, then the old D_801DA77C ($a1 throughout) */
    s32 cur;    /* D_801DA778, then the entity's +0x20 object ($a0 throughout) */
    s32 diff;   /* the gap to the target, then |v| ($v0 throughout) */
    u16 flags;
    s32 v;
    s32 spd;
    s32 e1;
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

    cur = D_801DA778;
    diff = cur - a;
    if (diff > 0) {
        D_801DA778 -= diff >> 2;
    } else if (diff < 0) {
        D_801DA778 += (-diff) / 4;
    }

    a = D_801DA77C;
    e1 = *(s32 *)(arg0 + 0x20);
    v = D_801DA778 - a + spd;
    D_801DA77C = spd;
    flags = *(u16 *)(e1 + 0x2C);
    D_801DA778 = v;
    *(u16 *)(e1 + 0x2C) = flags | 0x10;

    cur = *(s32 *)(arg0 + 0x20);
    diff = __builtin_abs(v);
    *(s16 *)(cur + 0x1C) = diff;
    *(s16 *)(cur + 0x18) = diff;
    *(s16 *)(*(s32 *)(arg0 + 0x20) + 0x1A) = tail + 0x1000;
}
