/* func_8017D12C — shared body (overlay slot 0x80128158, h_exact 79ff9481). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8002931C(s32 a0);
extern int func_8017D12C(int arg);
/* $v0 at exit: result of func_8002931C; no byte-neutral return: `return 0;` moved `move v0,zero` at +0x14, ov_SC06_018 objdump */
int func_8017D12C(int arg) {
    ((void (*)(int))func_8002931C)(0x1A40000);
}
