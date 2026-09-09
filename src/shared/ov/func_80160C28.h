/* func_80160C28 — shared body (overlay slot 0x80128158, h_exact c58d9ce0). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80161208();
extern void func_80146CA0(void *a0);
void func_80160C28(void *arg0)
{
    s32 p;
    s32 q;
    register void *a __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    if (func_80161208() == 0) {
        *(s32 *)((u8 *)arg0 + 0x238) += 0x1c000;
        p = *(s32 *)((u8 *)arg0 + 0x20);
        *(u16 *)((u8 *)p + 0x10) =
            (*(u16 *)((u8 *)p + 0x10) - *(u16 *)((u8 *)arg0 + 0x23a)) & 0xfff;
        q = *(s32 *)((u8 *)arg0 + 0x20);
        if (*(s16 *)((u8 *)q + 0x10) < 0xc00) {
            a = arg0;
            __asm__ __volatile__("" : : "r"(a));  // !FAKE: keepalive — NEEDED DIFFERS (P36 rung B headers1)
            *(u16 *)((u8 *)q + 0x10) = 0xc00;
            *(u16 *)((u8 *)a + 0xb8) = 1;
            func_80146CA0(a);
        }
    }
}
