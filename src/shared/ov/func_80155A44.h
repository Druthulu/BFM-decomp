/* func_80155A44 — shared body (overlay slot 0x80128158, h_exact fe3ef0c1). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80029178(s32 arg);
extern u8 func_8014BEF8(void);
extern u16 func_80148800(s32 *a0);
extern void func_80149CB4(void);
int func_80155A44(int param_1)
{
    int x = *(unsigned char *)(param_1 + 0x1AA);
    switch (x) {
    case 0:
    case 1:
        if ((((unsigned char (*)(int))func_80029178)(0x85) & 0xFF) &&
            ((int (*)(int))func_8014BEF8)(param_1) &&
            *(unsigned char *)(param_1 + 0x1C0) &&
            (((int (*)(int))func_80148800)(param_1) & 0x10)) {
            ((void (*)(int, int))func_80149CB4)(param_1, 2);
            return 1;
        }
        break;
    case 2:
        if ((((unsigned char (*)(int))func_80029178)(0x86) & 0xFF) &&
            (((int (*)(int))func_80148800)(param_1) & 0x10)) {
            ((void (*)(int, int))func_80149CB4)(param_1, 3);
            return 1;
        }
        break;
    }
}
