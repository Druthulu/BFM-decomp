/* func_801615C4 — shared body (overlay slot 0x80128158, h_exact b4822f79). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014ED28();
extern void func_80146D90(s32 a0);
extern void func_8014CC28(s32 a0);
extern void func_8014FA04(s32 a0);
s32 func_801615C4(void * arg0, s32 arg1)
{
    u32 acc;
    acc = 0;
    if (((arg1 & 1) == 0) && (((s32 (*)(void))func_8014ED28)() != 0)) {
        func_80146D90(arg0);
    }
    if (*(s32 *)((u8 *)arg0 + 0x34) > 0) {
        acc |= ((s32 (*)(s32))func_8014CC28)(arg0);
    }
    return acc | ((s32 (*)(s32))func_8014FA04)(arg0);
}
