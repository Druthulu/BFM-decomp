void func_80183884(s32 a0) {

    extern u8 D_801A71A4[];

    /* No pin (P36 S104 d30): case 3's two call results share ONE local
     * `ret` — flow counts 4 refs over a live length of 5 (the B608 piece's
     * copy from $v0 is folded into its compare by combine only afterwards),
     * so allocno_compare (global.c:595-607) ranks it at 16000, above the a0
     * copy's 13503. `ret` is allocated first and takes $s0; the a0 copy
     * conflicts with it and takes $s1; `tbl` does not conflict with `ret`
     * and takes $s0 in find_reg pass 0 (global.c:945-953) — exactly the
     * target's assignment. One `d` plus one `r` (refs 2, pri 4000) lose to
     * the a0 copy and give the 2-register permutation the old $16 pin hid. */
    s32 tbl;
    s32 ns;

    tbl = (s32)D_801A71A4;
    func_8012B1B4(a0, tbl);
    func_8012CBCC(a0);

    switch (*(u16 *)(a0 + 0x34)) {
    case 0:
        if (func_80182F4C(a0, 0x48) != 0 ||
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) >
                0x3FFFF) {
            s32 r = func_8012B608(
                *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 8);
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
                *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
            func_8012B1B4(a0, tbl);
        } else {
            goto set1;
        }
        break;

    case 1:
        if (func_80182F4C(a0, 0x48) == 0 &&
            ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)(a0 + 0x88)) <=
                0x3FFFF) {
            break;
        }
        goto st2;

    case 2: {
        s32 r = func_8012B608(
            *(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
            func_8012B744((void *)(a0 + 4), (void *)(a0 + 0x88)), 0x10);
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) + r;
        *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) =
            *(u16 *)(*(s32 *)(a0 + 0x20) + 0x12) & 0xFFF;
    }
        func_80182F4C(a0, 0x48);
        {
            s16 c = *(s16 *)(a0 + 0x102);
            if (c == 0) {
                ns = 3;
                goto setstate;
            }
            *(s16 *)(a0 + 0x102) = c - 1;
        }
        break;

    case 3: {
        void *p88 = (void *)(a0 + 0x88);
        s32 ret = ((s32(*)(s32, u16 *))func_8012BE98)(a0, (u16 *)p88);
        if (func_80182F4C(a0, 0x48) == 0) {
            if (ret > 0x40000) {
                ret = func_8012B608(*(s16 *)(*(s32 *)(a0 + 0x20) + 0x12),
                                      func_8012B744((void *)(a0 + 4), p88), 1);
                if (ret >= -0xFF && ret <= 0xFF) {
                    break;
                }
            } else {
                goto set1;
            }
        }
    }
        /* fall through into st2 */
    st2:
        *(u16 *)(a0 + 0x34) = 2;
        *(u16 *)(a0 + 0x102) = (rand() & 7) + 8;
        break;

    set1:
        ns = 1;
    setstate:
        *(u16 *)(a0 + 0x34) = ns;
        break;
    }

    {
        s16 t = *(s16 *)(a0 + 0x100);
        if (t != 0) {
            *(s16 *)(a0 + 0x100) = t - 1;
        } else if (((s32(*)(s32))func_8012BE54)(a0) <= 0x24000) {
            *(s16 *)(a0 + 0x2) = 5;
            *(s16 *)(a0 + 0x100) = 0x3C;
        }
    }
}
