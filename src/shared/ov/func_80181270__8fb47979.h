/* func_80181270 — shared body (overlay slot 0x80128158, h_exact 8fb47979). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_80178970(void);
extern void func_8012A828(s32*, s32);
extern void func_80178D18(void);
void func_80181270(arg0)
void *arg0;
{
    extern s16 D_801E7010;
    extern s16 D_801E7012;
    extern short D_801B9AA8;
    if (func_80178970() != 0) {
        ((void (*)(s32))func_80178D18)((s32)arg0);
        *(u16 *)((char *)arg0 + 0x2) = D_801E7010;
        *(u16 *)((char *)arg0 + 0x34) = D_801E7012;
        ((void (*)(s32 *, s32))func_8012A828)((s32 *)arg0, (s32)&D_801B9AA8);
    }
}
