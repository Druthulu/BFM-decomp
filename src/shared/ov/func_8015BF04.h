/* func_8015BF04 — shared body (overlay slot 0x80128158, h_exact e59dc56c). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801553A8(s32 *a0);
extern void func_80154A74(s32 a0, s32 a1);
void func_8015BF04(s32 *a0)
{
    func_801553A8(a0);
    func_80154A74((s32)a0, 0x11);
    *(s32 *)((u8 *)a0 + 0x44) &= ~2;
}
