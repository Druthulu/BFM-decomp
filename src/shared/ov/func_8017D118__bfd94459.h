/* func_8017D118 — shared body (overlay slot 0x80128158, h_exact bfd94459). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 rand(void);
extern void func_80146E90(s32 *a0, s32 a1);
void func_8017D118(s32 param_1)
{
    s32 pad[2];
    s32 r;
    r = rand();
    *(u16 *)(param_1 + 0x10) = 0x200;
    *(u16 *)(param_1 + 0x12) = 0x200;
    *(u16 *)(param_1 + 0x24) = (r & 0x1FF) + (*(u8 *)(param_1 + 0x30) << 9);
    *(u32 *)(param_1 + 0x18) = 0;
    *(u32 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x30) = *(u32 *)(param_1 + 0x30) >> 8;
    func_80146E90((s32 *)param_1, rand() & 7);
    *(u16 *)(param_1 + 0x2) = *(u16 *)(param_1 + 0x2) + 1;
}
