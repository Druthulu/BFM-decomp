/* func_8012A860 — shared body (overlay slot 0x80128158, h_exact 991046b9). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern int func_8012ACE0(void *a0);
extern void func_8012AAAC();
void func_8012A860(void *a0, int a1) {
    int v0;
    register char *p asm("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1)
    *(int *)((char *)a0 + 0x90) = a1;
    v0 = func_8012ACE0(a0);
    p = (char *)a0;
    *(unsigned short *)(p + 0x72) = *(unsigned short *)(p + 0x72) | 0x200;
    *(int *)(p + 0x94) = v0 - 1;
    *(int *)(p + 0x9C) = 0;
    *(short *)(p + 0x9A) = 0;
    func_8012AAAC();
}
