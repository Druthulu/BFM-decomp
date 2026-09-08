/* func_8016BF50 — shared body (overlay slot 0x80128158, h_exact 1c5bc11f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80149350(s32 arg0);
extern void func_80015954(s32 a0, s32 a1);
s32 func_8016BF50(s32 param)
{
    u16 buf[3];
    s32 arg;
    arg = *(s32 *)(param + 0x34);
    buf[0] = *(u16 *)(param + 0x12);
    buf[1] = *(u16 *)(param + 0x16);
    buf[2] = *(u16 *)(param + 0x1a);
    ((void (*)(s32, void *, void *))func_80149350)(arg, buf, buf);
    ((void (*)(void *, s32))func_80015954)(buf, param + 4);
}
