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
        return 0;
    }
    t = w.sxy[0];
    if (t < 0) {
        t = -t;
    }
    if (t >= 0xAB || (w.sxy[1] >= 0 ? w.sxy[1] >= 0x83 : -w.sxy[1] >= 0x83)) {
        w.in1[0] = *(s16 *)((s32)arg + 6);
        w.in1[1] = *(s16 *)((s32)arg + 10);
        w.in1[2] = *(s16 *)((s32)arg + 14);
        gte_ldv0(w.in1);
        gte_rtps();
        gte_stsxy(w.sxy);
        gte_stflg(&w.flag);
        if (w.flag & 0xFFFFEFFF) {
            return 0;
        }
        t = w.sxy[0];
        if (t < 0) {
            t = -t;
        }
        if (t >= 0x105 || (w.sxy[1] >= 0 ? w.sxy[1] >= 0x8D : -w.sxy[1] >= 0x8D)) {
            return 0;
        }
    }
    r = func_80013478((s32)&D_80126B5C, (s32)w.in0);
    k = 0x5A0;
    if (r <= 0x41010) {
        k = 0x59F;
    }
    func_8002D4C8(k, 0);
    return 1;
}
