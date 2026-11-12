/* func_801463A0 — shared body (overlay slot 0x80128158, h_exact f5c34dee). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014C6F4(u8 *a);
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
    extern s32 guess_g_PlayerActor; // Names ledger: config/names.tsv guess_g_PlayerActor
    extern s32 *guess_g_PlayerModelPtr; // Names ledger: config/names.tsv guess_g_PlayerModelPtr
    extern u16 guess_g_PlayerPosX; // Names ledger: config/names.tsv guess_g_PlayerPosX
    extern u16 guess_g_PlayerPosY; // Names ledger: config/names.tsv guess_g_PlayerPosY
    extern u16 guess_g_PlayerPosZ; // Names ledger: config/names.tsv guess_g_PlayerPosZ
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
    obj = (s32)guess_g_PlayerModelPtr;
    func_8014C6F4((s32)&guess_g_PlayerActor);
    func_80155150((s32)&guess_g_PlayerActor);
    func_801470C0((s32)&guess_g_PlayerActor);
    func_80147478((s32)&guess_g_PlayerActor);
    func_80147118((s32)&guess_g_PlayerActor);
    if (obj != 0) {
        v = guess_g_PlayerPosX + D_80126C90;
        *(short *)(obj + 8) = v;
        *(s32 *)(obj + 0x48) = (s32)v;
        v = guess_g_PlayerPosY + D_80126C92;
        *(short *)(obj + 0xA) = v;
        *(s32 *)(obj + 0x4C) = (s32)v;
        v = guess_g_PlayerPosZ + D_80126C94;
        *(short *)(obj + 0xC) = v;
        *(u16 *)(obj + 0x2C) = *(u16 *)(obj + 0x2C) | 0x11;
        *(s32 *)(obj + 0x50) = (s32)v;
    }
    func_8014BDE8((s32)&guess_g_PlayerActor);
    *(Blk8_801463A0 *)&D_80126BE8 = *(Blk8_801463A0 *)&D_80126BE0;
    D_80126BE0_hw = guess_g_PlayerPosX;
    D_80126BE2 = guess_g_PlayerPosY;
    D_80126BE4 = guess_g_PlayerPosZ;
    D_80126BA0 = D_80126B9C;
    D_80126B9C = D_80126B9C & 0x3FFFFFFF;
    func_801508F8((s32)&guess_g_PlayerActor);
    D_80126C9E = 0;
    func_8014B5B0(&guess_g_PlayerActor);
    func_80161D88((s32)&guess_g_PlayerActor);
}
