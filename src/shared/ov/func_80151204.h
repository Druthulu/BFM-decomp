/* func_80151204 — shared body (overlay slot 0x80128158, h_exact 48bd34d5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void guess_SpawnSmallObjectType1DAbove(void *a0, s32 a1, s32 a2);
/* $v0 at exit: result of guess_SpawnSmallObjectType1DAbove or entry $v0, unset or addiu $v0, $zero, 0x3E8 at ov_MAIN_012:0x80151214; no caller reads $v0 (census unused); void failed to compile: void value not ignored as it ought to be */
int func_80151204(int a0, int a1)
{
    if (a1 != 0 && a1 != 1000) {
        guess_SpawnSmallObjectType1DAbove(a0, 1, a1 & 0x7FFF);
    }
}
