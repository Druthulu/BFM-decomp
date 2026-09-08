/* func_80147B18 — shared body (overlay slot 0x80128158, h_exact e033e50a). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147D38(s32 a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void func_80147B5C(s32 a0, void *a1);
void func_80147B18(s32 a0)
{
    s32 buf[4];
    s32 b0, b1, b2;
    func_80147D38(a0, b0, b1, b2, &buf[0]);
    func_80147B5C(a0, &buf[0]);
}
