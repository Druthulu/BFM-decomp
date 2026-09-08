/* func_801463A0 — shared body (overlay slot 0x80128158, h_exact f5c34dee). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014C6F4();
extern void func_80155150(s32 a0);
extern void func_801470C0(s32 a0);
extern void func_80147478(s32 a0);
extern void func_80147118(s32 a0);
extern void func_8014BDE8(s32 a0);
extern short func_801508F8(s32 a0);
extern void func_8014B5B0(s32 *a0);
extern void func_80161D88();
void func_801463A0(void)
{
    extern s32 D_80126B58;
    extern s32 *D_80126B78;
    extern u16 D_80126B5E;
    extern u16 D_80126B62;
    extern u16 D_80126B66;
    extern u16 D_80126C90;
    extern u16 D_80126C92;
    extern u16 D_80126C94;
    extern s32 D_80126B9C;
    extern s32 D_80126BA0;
    extern u8 D_80126BE0[];     /* identical to the decl DEFINE_func_80146128() already emits in this TU */
    extern u8 D_80126BE8[];
    extern u16 D_80126BE0_hw __asm__("D_80126BE0");   /* halfword view of BE0 — see NEW IDIOM above */
    extern u16 D_80126BE2;
    extern u16 D_80126BE4;
    extern s16 D_80126C9E;
    s32 obj;
    short v;
    obj = (s32)D_80126B78;
    func_8014C6F4((s32)&D_80126B58);
    func_80155150((s32)&D_80126B58);
    func_801470C0((s32)&D_80126B58);
    func_80147478((s32)&D_80126B58);
    func_80147118((s32)&D_80126B58);
    if (obj != 0) {
        v = D_80126B5E + D_80126C90;
        *(short *)(obj + 8) = v;
        *(s32 *)(obj + 0x48) = (s32)v;
        v = D_80126B62 + D_80126C92;
        *(short *)(obj + 0xA) = v;
        *(s32 *)(obj + 0x4C) = (s32)v;
        v = D_80126B66 + D_80126C94;
        *(short *)(obj + 0xC) = v;
        *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x11;
        *(s32 *)(obj + 0x50) = (s32)v;
    }
    func_8014BDE8((s32)&D_80126B58);
    *(Blk8_801463A0 *)&D_80126BE8 = *(Blk8_801463A0 *)&D_80126BE0;
    D_80126BE0_hw = D_80126B5E;
    D_80126BE2 = D_80126B62;
    D_80126BE4 = D_80126B66;
    D_80126BA0 = D_80126B9C;
    D_80126B9C = D_80126B9C & 0x3FFFFFFF;
    func_801508F8((s32)&D_80126B58);
    D_80126C9E = 0;
    func_8014B5B0(&D_80126B58);
    func_80161D88((s32)&D_80126B58);
}
