/* func_80178004 — shared body (overlay slot 0x80128158, h_exact e1b70e9f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u32 func_801783D0(s32 a0, s32 a1);
s32 func_80178004(uint *param_1, uint param_2, int param_3)
{
    extern short D_8011F81E;
    register uint *p __asm__("$18");      /* $s2 running ptr */
    register uint p2  __asm__("$17");     /* $s1 param_2 */
    register uint u6  __asm__("$16");     /* $s0 uVar6 */
    register uint mask __asm__("$4");     /* $a0 0xFFFFFF */
    register uint c74 __asm__("$5");      /* $a1 0x74808080 */
    register uint q0  __asm__("$7");      /* $a3 (block 0 const) */
    p  = param_1;
    p2 = param_2;
    u6 = param_3 << 0x10;
    q0 = 0x6d165828;
    mask = 0xffffff;
    c74 = 0x74808080;
    {
        p[0] = ((uint)(p + -5) & mask) | 0x3000000;
        p[1] = c74;
        p[2] = u6 | (p2 & 0xffff);
        p[3] = q0;
        p += 5;
    }
    {
        register uint q __asm__("$6");    /* $a2 */
        q = 0x6d160048;
        p[0] = ((uint)(p + -5) & mask) | 0x3000000;
        p[1] = c74;
        p[2] = u6 | ((p2 + 7) & 0xffff);
        p[3] = q;
        p += 5;
    }
    {
        register uint q __asm__("$6");
        q = 0x6d160818;
        p[0] = ((uint)(p + -5) & mask) | 0x3000000;
        p[1] = c74;
        p[2] = u6 | ((p2 + 0xd) & 0xffff);
        p[3] = q;
        p += 5;
    }
    {
        register uint q __asm__("$6");
        q = 0x6d160028;
        p[0] = ((uint)(p + -5) & mask) | 0x3000000;
        p[1] = c74;
        p[2] = u6 | ((p2 + 0x13) & 0xffff);
        p[3] = q;
        p += 5;
    }
    {
        register uint q __asm__("$6");
        q = 0x6d160020;
        p[0] = ((uint)(p + -5) & mask) | 0x3000000;
        p[1] = c74;
        p[2] = u6 | ((p2 + 0x19) & 0xffff);
        p[3] = q;
        p += 5;
    }
    {
        register uint q __asm__("$6");
        q = 0x6d164058;
        p[0] = ((uint)(p + -5) & mask) | 0x3000000;
        p[1] = c74;
        p[2] = u6 | ((p2 + 0x3a) & 0xffff);
        p[3] = q;
        p += 5;
    }
    {
        register uint  uVar1 __asm__("$8");   /* $t0 */
        register uint *q     __asm__("$4");   /* $a0 running ptr in loop */
        register uint *r     __asm__("$5");   /* $a1 = q + 3 */
        register int   iVar4 __asm__("$7");   /* $a3 */
        register uint  uVar5 __asm__("$9");   /* $t1 */
        register uint  base6 __asm__("$14");  /* $t6 0x6D160000 */
        register uint  m2    __asm__("$10");  /* $t2 0xFFFFFF */
        register uint  c3b   __asm__("$11");  /* $t3 0x3000000 */
        register int   two   __asm__("$13");  /* $t5 */
        register int   ff    __asm__("$12");  /* $t4 */
        int a0arg;
        a0arg = 100 - (D_8011F81E * 0xa198 >> 0x10);
        {
            register uint ret __asm__("$2");
            ret = ((uint (*)(int, int))func_801783D0)(a0arg, 4);
            q = p;
            __asm__ __volatile__("" : "=r"(q) : "0"(q));
            uVar1 = ret;
        }
        p2 = p2 + 0x22;
        base6 = 0x6d160000;
        uVar5 = 0x1000000;
        iVar4 = 0;
        two = 2;
        ff = 0xff;
        m2 = 0xffffff;
        c3b = 0x3000000;
        r = q + 3;
        {
        register int  nx __asm__("$2");  /* $v0 */
        do {
            register uint uVar2 __asm__("$6");  /* $a2 */
            register uint c74v  __asm__("$3");  /* $v1 0x74808080 */
            register uint rval  __asm__("$2");  /* $v0 */
            uint t;
            t = (uVar1 << 16) >> 28;
            uVar2 = t;
            if (t != 0) {
                uVar5 = 0;
            } else if ((short)iVar4 == two) {
                uVar5 = 0;
            } else if ((short)iVar4 == ff) {
                uVar5 = 0;
            }
            c74v = 0x74808080;
            q[0] = ((uint)(q + -5) & m2) | c3b;
            r[-1] = u6 | (p2 & 0xffff) | uVar5;
            __asm__ __volatile__("" : : "r"(uVar2));
            rval = (uVar2 * 8 + 8) | 0x4000;
            rval = base6 | rval;
            r[-2] = c74v;
            r[0] = rval;
            r = r + 5;
            q = q + 5;
            p2 = p2 + 8;
            nx = iVar4 + 1;
            iVar4 = nx;
            __asm__ __volatile__("" : "=r"(nx) : "0"(nx));
            uVar1 = uVar1 << 4;
        } while (nx * 0x10000 >> 0x10 < 3);
        }
        return q;
    }
}
