/* func_80151204 — shared body (overlay slot 0x80128158, h_exact 48bd34d5). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8014ACE8(void *a0, s32 a1, s32 a2);
int func_80151204(int a0, int a1)
{
    if (a1 != 0 && a1 != 1000) {
        func_8014ACE8(a0, 1, a1 & 0x7FFF);
    }
}
