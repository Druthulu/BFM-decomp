void func_80176734(s32 param_1)
{
    extern u8  D_8011F7A8;      /* st base  ($s3) */
    extern u8  D_80078E78[];    /* cur base ($s4) */
    extern s16 D_801152BA;
    extern u8  D_8011F7B0;      /* == *(u8 *)(st + 8), read absolutely (mixed addressing) */
    extern u8  D_80115214;
    extern u8  D_80193BE8[];
    extern u16 D_80193B3A[];
    extern u16 D_80193B48;
    extern u8  D_80193BDC[];
    extern s32 D_80193BF4[];
    extern u8  D_800D43D4;
    extern u8  D_800D4414;
    extern u8  D_800D45D4;
    extern u8  D_800B9A13;
    extern s16 D_80126CE0;
    extern s16 D_80126D20;
    extern s32 D_80126B58;
    extern void func_800183E0(s32 a0);
    extern s32  func_801619D0(void *a0);
    extern s32  func_80161A00(s32 a0);
    extern s32  func_80161A30(s32 a0);
    extern s32  func_80161A60(s32 a0);
    extern void func_801775E0(s32 param_1, s32 param_2);

    s32 st, cach, flag, cur;
    s16 chg;        /* s16: every `(s32)chg` is a sign extension that combine reduces to a copy ($v1) */
    s16 amp;        /* s16, and reused as block I's change flag (the target keeps both in $s0) */
    u16 tgt;
    s32 pv;                                  /* the param copy that owns $s6 */
    s32 ix;                                  /* block A's index, hoisted out of the block */
    u8  dum[8];                              /* dead frame slot (target .frame vars=8) */
    s32 p;          /* ONE sprite-list pointer for blocks A, B and C: its conflicts leave it $a1 */

    st  = (s32)&D_8011F7A8;
    ix  = ((param_1 << 16) >> 14) + st;
    pv  = param_1;
    cach = st + 0x48;
    flag = st + 0xE0;
    cur  = (s32)&(*(u8 *)D_80078E78);

    /* ---- block A: pulse byte ---- */
    {
        u8 *q;
        p = *(s32 *)(ix + 0x28);
        q = (u8 *)(p + 0x3C);                /* must live in the entry BB */
        if (D_801152BA != 0) {
            u8 b = D_8011F7B0;
            u8 v;
            if (b < 0x80) v = b - 0x80;
            else          v = ~b - 0x80;
            q[4] = v;
            *(u8 *)(p + 4) = v;
            *(u8 *)(st + 8) = *(u8 *)(st + 8) + D_80115214;
        } else {
            *(u8 *)(p + 0x40) = 0x80;
            *(u8 *)(p + 4) = 0x80;
        }
    }

    /* ---- block B: 0x48 animation already running ---- */
    if (*(u8 *)(flag + 0x48) != 0) {
        p = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        *(u8 *)(p + 0xD) = D_80193BE8[*(u8 *)(flag + 0x48)];
        if (*(u8 *)(flag + 0x48) < 4) {
            *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
        } else {
            u8 c = *(u8 *)(cach + 0x48);
            s32 arg;
            p = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
            if (c & 0x80) {
                *(u16 *)(p + 0x20) = D_80193B48;
                arg = (s32)&D_800D45D4;
            } else if (c != 0) {
                *(u16 *)(p + 0x20) = D_80193B3A[c];
                arg = D_80193BF4[*(u8 *)(cach + 0x48)];
            } else {
                goto Lskip;
            }
            func_800183E0(arg);
        Lskip:
            if (*(u8 *)(flag + 0x48) == 5) {
                if (*(u8 *)(cach + 0x48) == 0) *(u8 *)(flag + 0x48) = 0;
                else *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            } else if (*(u8 *)(flag + 0x48) == 10) {
                *(u8 *)(flag + 0x48) = 0;
            } else {
                *(u8 *)(flag + 0x48) = *(u8 *)(flag + 0x48) + 1;
            }
        }
    /* ---- block C: 0x48 changed -> start the animation ---- */
    } else if (*(u8 *)(cach + 0x48) != *(u8 *)(cur + 0x48)) {
        u8 k;                                /* gives the `andi $v1,$v1,0xFF` index mask */
        if (*(u8 *)(cach + 0x48) == 0 && *(u8 *)(cur + 0x48) != 0)
            *(u8 *)(flag + 0x48) = 5;
        else
            *(u8 *)(flag + 0x48) = 0;
        *(u8 *)(cach + 0x48) = *(u8 *)(cur + 0x48);
        p = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        k = *(u8 *)(flag + 0x48);
        *(u8 *)(flag + 0x48) = k + 1;
        *(u8 *)(p + 0xD) = D_80193BE8[k];
    }

    /* ---- block D: field 0x2E (equality-first: the ne-arm must be out of line) ---- */
    if (*(s16 *)(cach + 0x2E) == *(s16 *)(cur + 0x2E)) {
        if (*(s16 *)(flag + 0x2E) == 0) goto L9C0;
        *(s16 *)(flag + 0x2E) = 0;
    } else {
        *(s16 *)(cach + 0x2E) = *(s16 *)(cur + 0x2E);
        *(s16 *)(flag + 0x2E) = 1;
    }
    {
        s32 pp = *(s32 *)(((pv << 16) >> 14) + st + 0x28);
        s32 t = (s32)(*(u16 *)(cach + 0x2E) << 16);
        if (t != 0) *(u8 *)(pp + 0x49) = D_80193BDC[t >> 20];
        else        *(u8 *)(pp + 0x49) = 0xA0;
    }
L9C0:

    /* ---- block E: field 0x1E sign flip ---- */
    {
        s32 fa = *(s16 *)(cach + 0x1E) & 0x8000;
        s32 fb = *(s16 *)(cur + 0x1E) & 0x8000;
        if (fa != fb) {
            s32 arg;
            if (fa != 0) {
                *(s16 *)(cach + 0x1E) = 0;
                arg = (s32)&D_800D43D4;
            } else {
                *(s16 *)(cach + 0x1E) = -0x8000;
                arg = (s32)&D_800D4414;
            }
            func_800183E0(arg);
        }
    }

    /* ---- block F: mode byte -> chg ---- */
    {
        u8 m = D_800B9A13;
        if (m != 3) {                        /* inverted: `chg = 0` belongs out of line */
            chg = (*(u8 *)(st + 7) != m);
            if (chg != 0) *(u8 *)(st + 7) = m;
        } else {
            chg = 0;
        }
    }

    /* ---- block G: switch on cur[0x48] (cases 3/4/5 cross-jump onto one tail) ---- */
    amp = 0;
    switch (*(u8 *)(cur + 0x48)) {
    case 3:
        if (func_801619D0(&D_80126B58) != 0) amp = 0xFF;
        break;
    case 4:
        if (func_80161A00((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 5:
        if (func_80161A30((s32)&D_80126B58) != 0) amp = 0xFF;
        break;
    case 6:
        if (func_80161A60((s32)&D_80126B58) != 0) amp = 0xBA;
        break;
    }

    /* ---- block H: amp != 0 short-circuit ---- */
    {
        if (amp != 0) {
            *(u8 *)(flag + 0x47) = 1;
            *(u8 *)(cach + 0x4B) = *(u8 *)(cur + 0x48) | 0xF0;
            *(u8 *)(cach + 0x47) = ((s32)D_80126D20 << 7) / amp;
            goto Ltail;
        }
    }

    if (*(u8 *)(cach + 0x4B) >= 0xF0) *(u8 *)(cach + 0x4B) = 0;

    /* ---- block I: target level + change flag.  The lhu is unconditional (target loads
       both the signed and the unsigned view of D_80126CE0 up front). ---- */
    tgt = *(u16 *)&D_80126CE0;
    if (D_80126CE0 != 0) {
        u8 v;                                /* u8: a SUBREG copy cse keeps; masked in place at the compare */
        v = tgt;
        *(u8 *)(cach + 0x4B) = v;
        amp = (*(u8 *)(cach + 0x47) != v);
    } else {
        u32 cv = *(u8 *)(cach + 0x47);       /* one load, two compares, no re-mask */
        tgt = *(u8 *)(cur + 0x47);
        amp = 0;
        if (cv != tgt || cv == 0x80) amp = 1;
        if (*(u8 *)(cur + 0x47) != 0 && *(u8 *)(cach + 0x4B) != 0) {
            *(u8 *)(cach + 0x4B) = 0;
            *(u8 *)(cach + 0x47) = *(u8 *)(cur + 0x47);
        }
    }

    /* ---- block J/K: slew cach[0x47] toward tgt when anything changed.  The inner test re-reads
       chg after the flag load (cse cannot see through the label), jump threading sends the outer
       `chg != 0` past it. ---- */
    if (amp != 0 || chg != 0 || *(u8 *)(flag + 0x47) != 0) {
        if (amp != 0 || chg != 0) {
            u32 c = *(u8 *)(cach + 0x47);
            s32 sv = (s16)tgt;
            if ((s32)c < sv) {
                *(u8 *)(cach + 0x47) = tgt;
            } else {
                if (sv != 0) *(u8 *)(cach + 0x47) = c - 3;   /* store in BOTH arms */
                else         *(u8 *)(cach + 0x47) = c - 8;
                c = *(u8 *)(cach + 0x47);        /* stays a real lbu because of the two stores */
                if (c == 0 || c > 0x80) {
                    *(u8 *)(cach + 0x47) = 0;
                    *(u8 *)(cach + 0x4B) = 0;
                } else if ((s32)c < (s16)tgt) {  /* fresh EBB -> the sll/sra is recomputed */
                    *(u8 *)(cach + 0x47) = tgt;
                }
            }
            *(u8 *)(flag + 0x47) = 1;
        } else {
            *(u8 *)(flag + 0x47) = 0;
        }
    }
Ltail:

    /* ---- block L: tail.  m+5 / m+9 are separate temps: `lhu + (m+5)`, not `(lhu + m) + 5`. ---- */
    {
        s32 b = ((pv << 16) >> 14) + st;
        s32 m = (*(u8 *)(st + 7) != 0) << 8;
        s32 m5 = m + 5;
        s32 m9 = m + 9;
        *(u16 *)(*(s32 *)(b + 0x28) + 0x32) = *(u16 *)(st + 0x12) + m5;
        func_801775E0(*(s32 *)(b + 0x28) + 0x64, (s16)(*(u16 *)(st + 0x12) + m9));
    }
}
