void func_800314DC(Obj *p) {
    Slot *e;
    /* dead local: the target frame is `vars= 8` with no $sp reference. */
    s32 pad[2];
    u16 h;
    u32 t;
    /* $2 pin #1 -- `base` is a LOCAL qty in the D_800A4C28 block. Unpinned,
       local-alloc.c:1825 combine_regs TIES its dest into operand 0 of the
       addu (the dying `t & 0xFF00` temp, which lives in $v1), so base lands
       in $v1; the target keeps it in $v0. A hard-reg dest cannot be tied, so
       the pin materialises base in $v0 exactly where the target has it. */
    register s32 base __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)
    u32 d;
    u32 res;
    /* $2 pin #2 (disjoint lifetime from `base`) -- see the lerp comment. */
    register u32 q __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B tus9)

    if (!(p->unk37 & 1)) {
        return;
    }

    if (p->unk30 != 0) {
        p->unk30--;
        return;
    }

    if (p->unk2C < 0) {
        p->unk24 += p->unk2C;
        if (p->unk24 <= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    } else {
        p->unk24 += p->unk2C;
        if (p->unk24 >= p->unk28) {
            p->unk24 = p->unk28;
            p->unk37 &= 0xFE;
        }
    }

    if (!(p->unk37 & 1) && p->unk38 != 0) {
        if (p->unk24 != p->unk3C) {
            p->unk28 = p->unk3C;
            if (p->unk3C < p->unk24) {
                p->unk2C = -p->unk3A;
            } else {
                p->unk2C = p->unk3A;
            }
        }
        p->unk38 = 0;
        p->unk37 |= 1;
    }

    e = &D_800A4C28[p->unk51];
    e->unk00 = D_80073140[p->unk0A];
    h = D_8006A970[p->unk10][p->unk0C].unk04;
    /* `t` MUST be a separate SImode local: a HImode `h` used both by the
       0x18 store and by SImode arithmetic is what keeps the otherwise
       redundant `andi $v0,$a0,0xFFFF` alive (folding it away costs an insn). */
    t = h;
    /* splitting the -0x3C00 off keeps the sh scheduled AFTER the andi/sll/sra
       chain: as one expression the store's memory dependence on the 0x24 load
       gives it enough sched1 priority to hoist into the load-delay region. */
    base = (t & 0xFF00) + ((s8)t * 2);
    e->unk18 = h;
    base -= 0x3C00;
    /* in-place update: the target reuses $a1 for both the 0x24 load and the
       difference, and global.c has no coalescing (K8) -- cross-block sharing
       has to be ONE pseudo in the source. */
    d = p->unk24;
    d -= base;
    if (d >= 0x5300) {
        res = 0x3FFF;
    } else {
        /* `q` merges the D_8006AB30 load with the first product into one
           $v0-pinned range. That blocks $v0 across insns 4..11 of this block,
           which is what pushes 0x100 -> $v1, the index -> $a0, the D_8006AB32
           load -> $v1, and (via the global pass) the second mflo -> $v1. */
        q = D_8006AB30[d >> 8];
        q = q * (0x100 - (d & 0xFF));
        res = (q + D_8006AB32[d >> 8] * (d & 0xFF)) >> 8;
    }
    e->unk14 = res;
    e->unk40 = p->unk0A;
    if (e->unk44 != 0) {
        e->unk04 |= 0x10;
    } else {
        e->unk44 = 1;
        e->unk04 = 0x10;
    }
}
