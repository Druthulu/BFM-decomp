/* func_8013BCDC @ 0x8013BCDC — ov_SC01_000 shared engine dispatcher (-O0 cluster 0x8013B568..0x8013C98C).
 * If the global callback pointer D_8017F35C is non-NULL, invoke it. The 0x30 frame carries a
 * 16-byte dead scratch local (byte-gate evidence: frame is 0x30, not 0x20; body is otherwise
 * an exact match). Compiles -O0 per Makefile:578-584 (frame-pointer prologue sig 21F0A003). */
extern void (*D_8017F35C)(void);

void func_8013BCDC(void)
{
    char pad[16];
    if (D_8017F35C != 0) {
        D_8017F35C();
    }
}
