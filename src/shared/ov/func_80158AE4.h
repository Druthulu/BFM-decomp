/* func_80158AE4 — shared body (overlay slot 0x80128158, h_exact 97ed2dea). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 D_800AE6AC;
extern s32 D_800AE6B0;
extern s32 D_80078EC8;
extern void func_8016F264(void);
extern void func_80165840(void);
extern void func_801658DC(void);
extern s32 func_80165A20(s32 a0);
extern void func_80165A78(s32);
extern void func_8014BF48(void);
extern void func_8014CBF8(void *a0);
extern void func_8014B160(s32 a0);
extern void func_80149020(s32 *a0);
extern void func_80146CA0(void *a0);
void func_80158AE4(void * a0)
{
    D_800AE6B0 = D_800AE6AC | 0x1000000;
    func_8016F264();
    ((void (*)(s32))func_80165840)(a0);
    ((void (*)(s32))func_801658DC)(a0);
    func_80165A20(a0);
    func_80165A78(a0);
    func_8014BF48();
    func_8014CBF8((void *)a0);
    func_8014B160(a0);
    func_80149020((s32 *)a0);
    *(s16 *)(a0 + 0x12E) = 0;
    *(s16 *)(a0 + 0x74) = 0x1000;
    *(s16 *)(a0 + 0x72) = 0x1000;
    *(s16 *)(a0 + 0x70) = 0x1000;
    *(s16 *)(a0 + 0x6C) = 0x1000;
    *(s16 *)(a0 + 0x6A) = 0x1000;
    *(s16 *)(a0 + 0x68) = 0x1000;
    *(s16 *)(a0 + 0x64) = 0x1000;
    *(s16 *)(a0 + 0x62) = 0x1000;
    *(s16 *)(a0 + 0x60) = 0x1000;
    *(s16 *)(a0 + 0x1BA) = 0x1000;
    *(s16 *)(a0 + 0x1B8) = 0x1000;
    *(s16 *)(a0 + 0xF6) = 0x1000;
    D_80078EC8 = 0;
    *(s16 *)(a0 + 0x1C8) = 0;
    func_80146CA0((void *)a0);
}
