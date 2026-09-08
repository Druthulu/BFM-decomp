/* func_8015D57C — shared body (overlay slot 0x80128158, h_exact 5662145b). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80154150(s32 a0, s32 a1);
extern void func_801553A8(s32 *a0);
extern void func_80155440(s32 *a0);
extern void func_80146CA0(void *a0);
extern void func_801746DC(void);
void func_8015D57C(s32 arg0)
{
    s16 *p;
    func_80154150((s32)arg0, 0x19);
    func_801553A8(arg0);
    func_80155440(arg0);
    func_80146CA0(arg0);
    *(s32 *)((s8 *)arg0 + 0x234) = 0;
    p = *(s16 **)((s8 *)arg0 + 0x178);
    if (p != 0) {
        if (*(u16 *)p == 0x1F8) {
            *(s16 *)((s8 *)p + 0xFC) = 1;
            func_801746DC();
        }
    }
}
