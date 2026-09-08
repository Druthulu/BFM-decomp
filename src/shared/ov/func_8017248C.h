/* func_8017248C — shared body (overlay slot 0x80128158, h_exact 9efabaa2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_801724EC(s32 a0);
s32 func_8017248C(s32 arg0, s32 arg1)
{
    if (((s32 (*)(void*, void*))func_801724EC)(arg0, arg1) != 0) {
        *(u16*)((u8*)arg0 + 6) = *(u16*)((u8*)arg1 + 0);
        *(u16*)((u8*)arg0 + 0xA) = *(u16*)((u8*)arg1 + 2);
        *(u16*)((u8*)arg0 + 0xE) = *(u16*)((u8*)arg1 + 4);
        return 1;
    }
    return 0;
}
