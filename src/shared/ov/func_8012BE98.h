/* func_8012BE98 — shared body (overlay slot 0x80128158, h_exact 63eedc41). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_800132BC(s32 a0, s32 a1);
void func_8012BE98(s32 arg0, u16 * arg1)
{
    s16 a[3];
    s16 b[3];
    a[0] = *(u16 *)((u8 *)arg0 + 0x6);
    a[1] = 0;
    a[2] = *(u16 *)((u8 *)arg0 + 0xE);
    b[0] = *(u16 *)((u8 *)arg1 + 0x0);
    b[1] = 0;
    b[2] = *(u16 *)((u8 *)arg1 + 0x4);
    func_800132BC((s32)a, (s32)b);
}
