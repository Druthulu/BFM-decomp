/* func_8013BD74 — shared body (overlay slot 0x80128158, h_exact 85c0b52f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013BD74(void *a0, s32 a1) {
    /* §100 draft-LOCAL types: file-scope typedefs are NOT carried by extract_unit/remap_hseq, so a
       file-scope E_13BD74 banks the exemplar and then fails every sibling with `E_13BD74'
       undeclared (the §94 type-carry class, measured on ov_SC01_000). Block scope travels with the
       body and is byte-neutral (a type emits no code). */
    s32 *q;
    s32 *p;
    s32 i;
    s32 unused0;
    s32 unused1;
    P_13BD74 *e;
    P_13BD74 *end;
    s32 unused2;
    s32 base;
    s32 unused3;

    D_8018F9C0 = -0xA0;
    D_8018F9C2 = -0x78;
    D_8018F9C4 = 0x140;
    D_8018F9C6 = 0xF0;
    ((E_13BD74 *)a0)->f8 = (void *)a1;
    ((E_13BD74 *)a0)->fC = (void *)(a1 + 8);
    base = a1 + 0x4008;
    if (((u8 *)a1)[4] == 0) {
        p = (s32 *)((E_13BD74 *)a0)->fC;
        for (i = 0; i < 0x1000; i++) {
            if (*p != 0) {
                *p += (s32)((E_13BD74 *)a0)->fC;
                q = (s32 *)*p;
                q[0] += (s32)q;
                q[5] += (s32)q;
                e = (P_13BD74 *)q[5];
                q[6] = q[6] * 12 + q[5];
                end = (P_13BD74 *)q[6];
                while (e < end) {
                    switch (e->code) {
                    case 0x24:
                    case 0x2C:
                    case 0x34:
                    case 0x3C:
                        *(s32 *)e = (*(s32 *)e & 0xFFFFFF) + base;
                        break;
                    case 0x26:
                    case 0x2E:
                    case 0x36:
                    case 0x3E:
                        *(s32 *)e = (*(s32 *)e & 0xFFFFFF) + base;
                        break;
                    }
                    e++;
                }
            }
            p++;
        }
        ((u8 *)a1)[4] = 1;
    }
}
