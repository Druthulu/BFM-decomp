/* func_801653B8 — shared body (overlay slot 0x80128158, h_exact c08b20fc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_801653F4(s32 a0);
    extern void func_80147078(s32 *a0, s16 a1);
    extern void func_80165580(s32 _arg0);
    void func_801653B8(s32 *a0) {
        s32 s = (s32)a0;
        ((void (*)(s32 *))func_801653F4)((s32 *)s);
        ((void (*)(s32, s32))func_80147078)(s, 0x17);
        ((void (*)(void *))func_80165580)((void *)s);
    }
