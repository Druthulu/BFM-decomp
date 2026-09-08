/* func_8017D6B0 — shared body (overlay slot 0x80128158, h_exact 03c35bc3). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void (*D_80190D1C[])(void);
void func_8017D6B0(s32 *param_1)
{
    D_80190D1C[*(u16 *)((char *)param_1 + 0x2)]();
}
