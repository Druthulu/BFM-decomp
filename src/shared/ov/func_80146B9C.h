/* func_80146B9C — shared body (overlay slot 0x80128158, h_exact 8ac9e1b1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern u16 D_8011DA28;
s32 func_80146B9C(void * arg0)
{
    u8 *p;
    u8 *end;
    p = (u8 *)&D_8011DA28;
    end = p - 0x9F8;
    if ((u32)p >= (u32)end) {
        do {
            if (*(u16 *)p == 0) {
                *(s32 *)(p + 52) = *(s32 *)((u8 *)arg0 + 0x8);
                *(s16 *)p = *(u16 *)((u8 *)arg0 + 0x0);
                *(s16 *)(p + 6) = *(u16 *)((u8 *)arg0 + 0x2);
                *(s16 *)(p + 10) = *(u16 *)((u8 *)arg0 + 0x4);
                *(s16 *)(p + 14) = *(u16 *)((u8 *)arg0 + 0x6);
                *(s32 *)(p + 44) = *(s32 *)((u8 *)arg0 + 0xC);
                *(s32 *)(p + 48) = *(s32 *)((u8 *)arg0 + 0x10);
                return (s32)p;
            }
            p -= 0x58;
        } while ((u32)p >= (u32)end);
    }
    return 0;
}
