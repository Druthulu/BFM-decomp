s32 func_80181E98_impl(void *arg)
{
    extern void func_8012F214(s32 a0, s32 a1, s32 a2);
    extern s32 func_80013478(s32 a0, s32 a1);
    extern void func_8002D4C8(s32 a0, s32 a1);
    extern s32 D_8018E564;
    extern u8 D_800AF648;
    extern u8 D_80126B5C;

    struct {
        s16 in0[4];
        s16 in1[4];
        s16 sxy[2];
        s32 flag;
    } w;
    s32 t;
    s32 r;
    s32 k;

    func_8012F214((s32)arg, (s32)&D_8018E564, (s32)w.in0);
    gte_SetRotMatrix(&D_800AF648);
    gte_SetTransMatrix(&D_800AF648);
    gte_ldv0(w.in0);
    gte_rtps();
    gte_stsxy(w.sxy);
    gte_stflg(&w.flag);
    if (w.flag & 0xFFFFEFFF) {
        goto ret0;
    }
    t = w.sxy[0];
    if (t < 0) {
        t = -t;
    }
    if (t < 0xAB) {
        if (w.sxy[1] >= 0) {
            if (w.sxy[1] >= 0x83) {
                goto second;
            }
            goto pass;
        } else {
            if (-w.sxy[1] < 0x83) {
                goto pass;
            }
        }
    }
second:
    w.in1[0] = *(s16 *)((s32)arg + 6);
    w.in1[1] = *(s16 *)((s32)arg + 10);
    w.in1[2] = *(s16 *)((s32)arg + 14);
    gte_ldv0(w.in1);
    gte_rtps();
    gte_stsxy(w.sxy);
    gte_stflg(&w.flag);
    if (w.flag & 0xFFFFEFFF) {
        goto ret0;
    }
    t = w.sxy[0];
    if (t < 0) {
        t = -t;
    }
    if (t >= 0x105) {
        goto ret0;
    }
    if (w.sxy[1] >= 0) {
        if (w.sxy[1] >= 0x8D) {
            goto ret0;
        }
        /* zero-byte cross_jump fence (jump.c find_cross_jump): without an insn
           here the two |sxy[1]| arms share the suffix `slti 0x8D; beq ret0`
           and cross_jump merges them into a single conditional-negate (-5 ins). */
        __asm__ __volatile__("");  // !FAKE: barrier — NEEDED DIFFERS (P36 rung B tus8)
        goto pass;
    } else {
        if (-w.sxy[1] >= 0x8D) {
            goto ret0;
        }
    }
pass:
    r = func_80013478((s32)&D_80126B5C, (s32)w.in0);
    k = 0x5A0;
    if (r <= 0x41010) {
        k = 0x59F;
    }
    func_8002D4C8(k, 0);
    return 1;
ret0:
    return 0;
}
