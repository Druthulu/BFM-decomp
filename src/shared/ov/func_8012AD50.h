/* func_8012AD50 — shared body (overlay slot 0x80128158, h_exact 545fa3d7). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
/* $v0 at exit: addiu $v0, $v0, 0x1 at ov_MAIN_012:0x8012AD58; no byte-neutral return: `return 0;` moved `sh v0,2(a0)` at +0xC, ov_MAIN_012 objdump */
s32 func_8012AD50(void * arg0)
{
    M2C_FIELD(arg0, s16 *, 0x34) = 0;
    M2C_FIELD(arg0, u16 *, 2) = (u16) (M2C_FIELD(arg0, u16 *, 2) + 1);
}
