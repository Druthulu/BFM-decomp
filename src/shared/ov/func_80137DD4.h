/* func_80137DD4 — shared body (overlay slot 0x80128158, h_exact 9b03676a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *func_80010A08(s32);
extern void func_80137FD8(s32 a0, s32 a1, s32 a2, s32 a3);
void func_80137DD4(s32 ent, u8 *arg, u8 *work) {
    register s32 t __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    s32 d, c, c1, sub, y;
    u32 b;
    P_TAG_80137DD4 *q, *r;
    {
        register u32 h12 __asm__("$2"), h16 __asm__("$3");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
        h12 = *(u16 *)(ent + 0x12);
        h16 = *(u16 *)(ent + 0x16);
        t = h12 - h16;
    }
    d = t;
    if ((s16)t < 0) {
        register s32 e __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1)
        e = t + 1;
        d = (u32)*(u16 *)(ent + 0x2e) + e;
    }
    b = *(volatile u8 *)(ent + 0x1f);
    c = (s8)b;
    sub = d - (u32)*(u8 *)(ent + 0x21);
    c1 = c + 1;
    y = (u32)*(u16 *)(ent + 0x32) + (s16)(sub + c1) * 0xe;
    q = (P_TAG_80137DD4 *)func_80010A08(0x48);
    *(u8 *)(arg + 3) = 0;
    func_80137FD8(ent, (s32)arg, (s32)q, (s16)y);
    q->addr = ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr;
    ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr = (u32)q;
    q = (P_TAG_80137DD4 *)((u8 *)q + 0x24);
    *(u8 *)(arg + 3) = 1;
    func_80137FD8(ent, (s32)arg, (s32)q, (s16)y);
    q->addr = ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr;
    ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr = (u32)q;
    r = (P_TAG_80137DD4 *)func_80010A08(8);
    r->len = 1;
    *(u32 *)((u8 *)r + 4) = 0xe100000a;
    r->addr = ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr;
    ((P_TAG_80137DD4 *)((u32)*(u16 *)(ent + 0x1a) * 4 + *(s32 *)(work + 4)))->addr = (u32)r;
}
