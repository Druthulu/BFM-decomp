/* func_80166244 — shared body (overlay slot 0x80128158, h_exact eadf51e8). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80146A6C(s32 a0, void *a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6);
void func_80166244(void* arg0) {
    ((void (*)(s32, void*, s16, s16, s16, u32, u32))func_80146A6C)(3, arg0, *(s16*)((u8*)arg0 + 6), *(u16*)((u8*)arg0 + 0xA) - 0x10, *(s16*)((u8*)arg0 + 0xE), 0x8F8FFF8, 0xE000B000);
}
