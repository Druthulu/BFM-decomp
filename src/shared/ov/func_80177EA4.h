/* func_80177EA4 — shared body (overlay slot 0x80128158, h_exact cae296e7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
uint *func_80177EA4(uint *param_1, int param_2, uint param_3, int param_4)
{
    uint uVar1;
    int iVar2;
    uint *p1;
    register uint *puVar3 __asm__("$8");  // !FAKE: pin $8 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
    int iVar4;
    uint uVar5;
    uint mask;
    register int nx __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
    int p4s;
    int cont;
    p1 = param_1; uVar5 = 0x1000000; iVar4 = 0; mask = 0xffffff;
    p4s = param_4 << 0x10;
    puVar3 = p1 + 3;
    do {
        register uint c74 __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
        register uint c3 __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
        register uint m __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
        c74 = 0x74808080;
        m = (uint)(p1 + -5) & mask;
        c3 = 0x3000000;
        *p1 = m | c3;
        puVar3[-2] = c74;
        if ((short)iVar4 != 0) {
            register int six __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
            six = 6;
            if ((short)iVar4 == six) { iVar2 = 1; uVar5 = 0; }
            else {
                int t;
                t = param_2 >> 0x10 & 0xf;
                iVar2 = t + 1;
                param_2 = param_2 << 4;
            }
            {
                int iv2c;
                register int one __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
                iv2c = iVar2;
                __asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B headers1) wall:cse-copy-merge
                one = 1;
                if (iv2c != one) uVar5 = 0;
            }
            uVar1 = p4s | (param_3 & 0xffff) | uVar5;
        } else { iVar2 = 0; uVar1 = p4s | (param_3 & 0xffff); }
        do { puVar3[-1] = uVar1; } while (0);  // !FAKE: do-while
        {
            register uint c6b __asm__("$3");  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
            uint r;
            c6b = 0x6b564000;
            r = (uint)(iVar2 << 3) | c6b;
            *puVar3 = r;
        }
        puVar3 = puVar3 + 5; p1 = p1 + 5; param_3 = param_3 + 8;
        {
            register int sx __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:loop-const-hoist
            nx = iVar4 + 1;
            iVar4 = nx;
            sx = nx << 0x10;
            cont = (sx >> 0x10) < 7;
        }
    } while (cont);
    return p1;
}
