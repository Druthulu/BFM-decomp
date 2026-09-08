/* func_80186764 — shared body (overlay slot 0x80128158, h_exact d67a6376). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C810(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8012A828(s32 a0, void *a1);
extern u8 D_801DCED0;
extern s32 D_8018F304;
extern s32 D_801E8270;
extern u8 D_801E827C;
extern u8 D_801E827D;
extern u8 D_801E827E;
extern u8 D_801E828C;
extern u8 D_801E828E;
extern u8 D_801E829E;
extern u8 D_801E82AC;
extern u8 D_801DD528;
extern M2C_UNK D_8018AF28;
extern s32 D_801270C8;
void func_80186764(s32 param_1)
{
    s32 v0;
    s32 s0;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001C810)(v0, &D_801DCED0);
    *(s32 *)(param_1 + 0x58) = (s32)&D_8018F304;
    *(u16 *)(param_1 + 0x5C) = 0x800;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 4) |= 0x40000000;
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0xDC, 0x98);
    *(u16 *)(*(s32 *)(param_1 + 0x20) + 0x2C) |= 0x20;
    *(s32 *)(*(s32 *)(param_1 + 0x20) + 0x80) = (s32)&(*(u8 *)&D_801E8270);
    D_801E827D = 0xFF;
    D_801E829E = 0xFF;
    D_801E82AC = 0xFF;
    D_801E827D = 0xFF;
    D_801E828E = 0xFF;
    D_801E828C = 0xFF;
    D_801E827D = 0xFF;
    D_801E827E = 0xFF;
    D_801E827C = 0xFF;
    s0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0xCC) = s0;
    ((void (*)(s32, void *))func_8001C214)(s0, &D_801DD528);
    *(s32 *)(s0 + 0x20) = (*(s32 *)&D_8018AF28);
    func_8001D0E8(s0, 0xDC, 0x98);
    ((void (*)(s32, void *))func_8012A828)(param_1, &(*(s32 *)&D_8018AF28));
    *(s16 *)(param_1 + 2) = 1;
    *(u16 *)(param_1 + 0xFC) = 0x10;
    *(s32 *)(param_1 + 0xDC) = D_801270C8;
}
