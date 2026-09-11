void func_8018209C(void *arg0)
{
    SV_8018209C vin;
    SV_8018209C w;
    RES_8018209C res;
    s32 t;
    s32 rv;

    func_8012F214((s32)arg0, (s32)D_8018E56C, (s32)&vin);
    gte_SetRotMatrix(&D_800AF648);
    gte_SetTransMatrix(&D_800AF648);
    gte_ldv0(&vin);
    gte_rtps();
    gte_stsxy(&res.x);
    gte_stflg(&res.flag);
    if (res.flag & 0xFFFFEFFF) {
        rv = 0;
        goto out;
    }
    t = res.x;
    if (t < 0) {
        t = -t;
    }
    if (t >= 0xAB || (res.y >= 0 ? res.y >= 0x83 : -res.y >= 0x83)) {
        w.vx = *(u16 *)((s32)arg0 + 6);
        w.vy = *(u16 *)((s32)arg0 + 0xA);
        w.vz = *(u16 *)((s32)arg0 + 0xE);
        gte_ldv0(&w);
        gte_rtps();
        gte_stsxy(&res.x);
        gte_stflg(&res.flag);
        if (res.flag & 0xFFFFEFFF) {
            rv = 0;
            goto out;
        }
        t = res.x;
        if (t < 0) {
            t = -t;
        }
        if (t >= 0x105 || (res.y >= 0 ? res.y >= 0x8D : -res.y >= 0x8D)) {
            rv = 0;
            goto out;
        }
    }
    if (func_80013478((s32)&D_80126B5C, (s32)&vin) <= 0x41010) {
        func_8002D4C8(0xB67, 0);
    }
    rv = 1;
out:
    __asm__ __volatile__("" : : "r"(rv));  // !FAKE: keepalive — the s32 return value under the TU's void prototype (P36 S104 e9 minimum-lever)
}
