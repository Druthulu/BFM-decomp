/* func_8015F380 — shared body (overlay slot 0x80128158, h_exact 9e46a0ac). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154150(s32 a0, s32 a1);
extern void func_80146E90(s32 *a0, s32 a1);
extern void func_80148534(s32 a0, s32 a1);
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
extern void func_80147324(s32 arg0);
extern s32 func_801725B8(u8 *a0);
extern void func_80146CA0(void *a0);
void func_8015F380(void* arg0) {
    s64 sp20;
    s64 sp28;
    ((void (*)(void*, s32))func_80154150)(arg0, 0x18);
    *(s8*)((u8*)arg0 + 0x244) = 0;
    *(s8*)((u8*)arg0 + 0x245) = 0;
    ((void (*)(void*, s32))func_80146E90)(arg0, 0);
    ((void (*)(s64*, s64*))func_80148534)(&sp20, &sp28);
    ((void (*)(s32, void*, s16, s16, s16, s32, s32))func_80146A6C)(0x25, arg0, *(s16*)((u8*)arg0 + 0x6), (s16)(*(u16*)((u8*)arg0 + 0xA) - 0x14), *(s16*)((u8*)arg0 + 0xE), 0, 0);
    ((void (*)(s32, void*, s16, s16, s16, s32, s32))func_80146A6C)(0x25, arg0, *(s16*)((u8*)arg0 + 0x6), (s16)(*(u16*)((u8*)arg0 + 0xA) - 0x14), *(s16*)((u8*)arg0 + 0xE), 1, 0);
    func_80147324(0x56D);
    ((void (*)(void*))func_801725B8)(arg0);
    func_80146CA0(arg0);
}
