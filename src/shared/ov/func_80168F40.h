/* func_80168F40 — shared body (overlay slot 0x80128158, h_exact 75c3bc82). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
void func_80168F40(void *arg0) {
    extern Blk20 D_800AE620;
    extern s32 func_80016A5C();
    struct A a;
    struct B b;
    a.unk00 = *(u16 *)((u8 *)arg0 + 0x10);
    a.unk02 = *(u16 *)((u8 *)arg0 + 0x14);
    a.unk04 = *(u16 *)((u8 *)arg0 + 0x18);
    a.unk08 = *(u16 *)((u8 *)arg0 + 0x6);
    a.unk0A = *(u16 *)((u8 *)arg0 + 0xA);
    a.unk0C = *(u16 *)((u8 *)arg0 + 0xE);
    a.unk10 = 8;
    a.unk14 = 0xC0;
    a.unk12 = 0;
    a.unk11 = 0;
    a.unk16 = 0x80;
    a.unk15 = 0x80;
    *(struct Bv *)&b = *(struct Bv *)&D_800AE620;
    a.unk18 = 0x50000000;
    func_80016A5C(&a, &b);
}
