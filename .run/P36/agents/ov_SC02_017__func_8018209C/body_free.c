void func_8018209C(void *arg0)
{
    SV_8018209C vin;
    SV_8018209C w;
    RES_8018209C res;
    s32 g;
    s32 rv;

    func_8012F214((s32)arg0, (s32)D_8018E56C, (s32)&vin);

    g = (s32)&D_800AF648;
    __asm__ __volatile__(                
        "lw $12, 0(%0)\n" "lw $13, 4(%0)\n"
        "ctc2 $12, $0\n" "ctc2 $13, $1\n"
        "lw $12, 8(%0)\n" "lw $13, 12(%0)\n" "lw $14, 16(%0)\n"
        "ctc2 $12, $2\n" "ctc2 $13, $3\n" "ctc2 $14, $4\n" :  : "r"(g) : "$12", "$13", "$14" );
    __asm__ __volatile__(
        "lw $12, 20(%0)\n" "lw $13, 24(%0)\n"
        "ctc2 $12, $5\n" "lw $14, 28(%0)\n"
        "ctc2 $13, $6\n" "ctc2 $14, $7\n" :  : "r"(g) : "$12", "$13", "$14" );

    gte_ldv0(&vin);
    gte_rtps();
    gte_stsxy(&res.x);
    gte_stflg(&res.flag);

    if ((res.flag & -0x1001) != 0) { rv = 0; goto out; }
    if ((res.x < 0 ? -res.x : res.x) >= 0xAB)
        goto L2;
    if ((res.y < 0 ? -res.y : res.y) >= 0x83)
        goto L2;
    goto tail;

L2:
    w.vx = *(u16 *)((s32)arg0 + 6);
    w.vy = *(u16 *)((s32)arg0 + 0xA);
    w.vz = *(u16 *)((s32)arg0 + 0xE);
    gte_ldv0(&w);
    gte_rtps();
    gte_stsxy(&res.x);
    gte_stflg(&res.flag);

    if ((res.flag & -0x1001) != 0) { rv = 0; goto out; }
    if ((res.x < 0 ? -res.x : res.x) >= 0x105) { rv = 0; goto out; }
    if ((res.y < 0 ? -res.y : res.y) >= 0x8D) { rv = 0; goto out; }
tail:
    if (func_80013478((s32)&D_80126B5C, (s32)&vin) <= 0x41010)
        func_8002D4C8(0xB67, 0);
    rv = 1;
out:
}
