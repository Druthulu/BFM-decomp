/* func_8016F4C4 — shared body (overlay slot 0x80128158, h_exact 3b02d0dc). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8016F0E4(u8 *);
extern void func_80165770(void);
/* $v0 at exit: result of func_80165770; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x1C, ov_MAIN_012 objdump */
s32 func_8016F4C4(s32 param_1)
{
    KR_AS(void, func_8016F0E4)();
    ((void (*)(s32))func_80165770)(param_1);
}
