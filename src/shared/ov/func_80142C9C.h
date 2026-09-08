/* func_80142C9C — shared body (overlay slot 0x80128158, h_exact e5f20023). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012CBF4(s32 a0);
void func_80142C9C(s32 * arg0)
{
    u32 uVar1;
    if (*(s16 *)((u8 *)arg0 + 0x102) < 2) {
        uVar1 = ((s32 (*)(void))func_8012CBF4)();
        if (0x180000 < *(s32 *)((u8 *)arg0 + 0x14)) {
            *(s32 *)((u8 *)arg0 + 0x14) = 0x180000;
        }
        if (((uVar1 & 0x6000) != 0) || (0x100 < *(s16 *)((u8 *)arg0 + 0xA))) {
            if (*(s16 *)((u8 *)arg0 + 0x102) == 0) {
                *(s32 *)((u8 *)arg0 + 0x14) = 0xFFF80000;
            }
            *(s16 *)((u8 *)arg0 + 0x102) = *(s16 *)((u8 *)arg0 + 0x102) + 1;
        }
    }
}
