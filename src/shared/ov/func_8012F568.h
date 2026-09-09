/* func_8012F568 — shared body (overlay slot 0x80128158, h_exact d302f6ed). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *memcpy(void *, const void *, u32);
extern u8 D_80126C38;
extern u8 D_80126C40;
extern u16 D_80126B94;
extern u16 D_80126B96;
extern s16 D_80126B98;
extern s16 D_80126B9A;
void func_8012F568(s32 param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5, s32 param_6)
{
    memcpy(&D_80126C38, param_5, 8);
    memcpy(&D_80126C40, param_6, 8);
    __asm__ __volatile__("" ::: "memory");  // !FAKE: barrier memory — NEEDED DIFFERS (P36 rung B headers1)
    D_80126B96 = param_2;
    D_80126B9A = param_3;
    D_80126B98 = param_4;
    D_80126B94 = D_80126B94 | param_1;
}
