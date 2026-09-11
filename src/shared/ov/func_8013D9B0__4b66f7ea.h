/* func_8013D9B0 — shared body (overlay slot 0x80128158, h_exact 4b66f7ea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_8013D9B0(int param_1)
{
    extern s16 *D_8018E774;
    extern s32 D_8018E78C;
    s16 rect[4];    /* LoadImage rect: x, y, w, h */
    u32 gte[6];     /* [0] fog colour (RGB), [1] source pixel (IRGB), [2] DPCL result (ORGB); [3..5] unused (frame 0x48) */
    Cmd_8013D53C *p;
    u32 *fc;
    u16 cmd;
    s32 flag;
    s32 any;
    s32 n;
    s32 i;
    u16 *src;
    u16 *img;
    u16 *dst;
    s32 r, g, b;
    s32 tr, tg, tb;
    u32 pix;
    u32 out;
    u32 result;

    p = (Cmd_8013D53C *)D_8018E774;
    if (p != 0) {
        cmd = p->cmd;
        gte[0] = (*(u32 **)&D_8018E76C)[param_1];
        D_8018E78C = -1;
        any = 0;
        if (cmd != 0xff) {
            fc = gte;
            do {
                if (cmd == 9) {
                    i = 0;
                    rect[0] = p->pad4;
                    rect[1] = p->pad6;
                    rect[2] = p->w;
                    rect[3] = p->h;
                    n = p->w * p->h;
                    flag = 0;
                    src = p->data;
                    img = src + n;
                    dst = img;
                    if (n > 0) {
                        do {
                            gte[1] = *src;
                            pix = *dst;
                            r = pix & 0x1f;
                            g = pix & 0x3e0;
                            b = pix & 0x7c00;
                            __asm__ __volatile__("mtc2 $0, $8\n\tlwc2 $6, 0(%0)\n\tlwc2 $28, 0(%1)" :: "r"(fc), "r"(&gte[1]) : "memory");  // !FAKE: asm gte_ldIR0z+gte_ldrgb+gte_ldIRGB — the header spells these as three volatile asms (sched.c:1957 barriers), so the IRGB address lands after lwc2 $6, and a pointer set before mtc2 has life 4 and is hoisted (loop.c:1631); one asm keeps its addiu adjacent (life 1) and before mtc2 (P36 S103 c47 minimum-lever)
                            gte_dpcl();
                            __asm__ __volatile__("move $12, %0\n\tswc2 $29, 0($12)" :: "r"(&gte[2]) : "$12", "memory");  // !FAKE: asm gte_stORGB — the header macro does not write $12 itself; the target's move t4,v0 needs it (S103 c17; the header respelling is Drew's T5 call) (P36 S103 c47 minimum-lever)
                            out = gte[2];
                            tr = out & 0x1f;
                            tg = out & 0x3e0;
                            tb = out & 0x7c00;
                            if (r != tr) {
                                if (r < tr) { flag = 1; r += 1; } else flag = 1;
                                if (tr < r) r -= 1;
                            }
                            if (g != tg) {
                                if (g < tg) { flag = 1; g += 0x20; } else flag = 1;
                                if (tg < g) g -= 0x20;
                            }
                            if (b != tb) {
                                if (b < tb) { flag = 1; b += 0x400; } else flag = 1;
                                if (tb < b) b -= 0x400;
                            }
                            result = r | g | b | (gte[1] & 0x8000);
                            if (result == 0 && gte[1] != 0) {
                                result = 0x8000;
                            }
                            *dst = result;
                            dst++;
                            i++;
                            src++;
                        } while (i < n);
                    }
                    if (flag != 0) {
                        ((void (*)(s16 *, u16 *))func_800599B8)(rect, img);
                    }
                    any |= flag;
                }
                p++;
                cmd = p->cmd;
            } while (cmd != 0xff);
        }
        D_8018E784 = any;
    }
}
