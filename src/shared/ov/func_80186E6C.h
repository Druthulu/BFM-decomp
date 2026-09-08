/* func_80186E6C — shared body (overlay slot 0x80128158, h_exact 621bba09). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012C1B8(void);
extern void func_8012CAE4(void *a0);
extern void func_8001C214(s32 a0, s32 a1);
extern void func_8001D0E8(s32 a0, s32 a1, s32 a2);
extern void func_8012A828(s32 a0, void *a1);
extern void func_8012B200(u8 *a0);
extern u8 D_801E071C;
extern u8 D_801E2164;
extern M2C_UNK D_8018AF28;
extern s32 D_8018F3B4;
void func_80186E6C(s32 param_1)
{
    s32 v0;
    s32 addr;
    u8 v2;
    v0 = ((s32 (*)(void))func_8012C1B8)();
    *(s32 *)(param_1 + 0x20) = v0;
    if (v0 == 0) {
        ((void (*)(s32))func_8012CAE4)(param_1);
        return;
    }
    ((void (*)(s32, void *))func_8001C214)(
        v0, (*(s16 *)(param_1 + 0x70) != 0) ? &D_801E2164 : &D_801E071C);
    func_8001D0E8(*(s32 *)(param_1 + 0x20), 0x140, 0xF0);
    addr = (s32)&D_8018F3B4;
    *(s32 *)(param_1 + 0x58) = addr | 0x40000000;
    *(u16 *)(param_1 + 0x5C) |= 0xC00;
    func_8012A828(param_1, &(*(u8 *)&D_8018AF28));
    v2 = 4;
    if (*(s16 *)(param_1 + 0x70) != 0) {
        v2 = 1;
    }
    *(u8 *)(param_1 + 0x75) = v2;
    func_8012B200((u8 *)param_1);
    *(u16 *)(param_1 + 2) = *(u16 *)(param_1 + 2) + 1;
}
