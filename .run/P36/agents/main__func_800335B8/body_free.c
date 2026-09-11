void func_800335B8(s32 a0, s32 a1) {
    u8 *e = (u8 *)D_800A46E8 + a0 * 0x54;
    u8 *p;
    s32 a2;
    s32 v1;
    s32 t0;

    if ((*(u16 *)e & 0x3F) != 1) {
        return;
    }

    /* copy-fence: keeps the `addu $t0,$a1,$zero` param copy alive (cse would
       otherwise propagate $a1 into branch 2's `andi $a1,$t0,0x7F`). */
    t0 = a1;

    if (a1 & 0x1000) {
        v1 = 0;
        a2 = *(u16 *)(e + 0xC);
        a1 = a1 & 0x7F;
        t0 = 1;
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (; v1 < 8; v1++, p += 0x54) {
            u8 *rec;
            if (a2 == 0) {
                return;
            }
            if (*(u8 *)(e + v1 + 0xE) != 0) {
                /* copy-fence: materialises the target's in-loop
                   `addu $v0,$a0,$zero` (reorg then steals it for the
                   beqz delay slot). Walking pointer, NOT p + v1*0x54,
                   so loop strength reduction still owns $a0. */
                rec = p;
                a2--;
                *(u16 *)(rec + 0x48) = a1;
                *(u8 *)(rec + 0x4F) = t0;
            }
        }
    } else if (a1 & 0x2000) {
        a2 = *(u16 *)(e + 0xC);
        v1 = 0;
        a1 = t0 & 0x7F;
        p = (u8 *)D_800A46E8 + 0x2A0;
        for (; v1 < 8; v1++) {
            u8 *rec;
            if (a2 == 0) {
                return;
            }
            if (*(u8 *)(e + v1 + 0xE) != 0) {
                rec = p + v1 * 0x54;
                if (*(u8 *)(rec + 0x35) != 0) {
                    *(u8 *)(rec + 0x53) = a1;
                }
                a2--;
            }
        }
    }
}
