/* func_8017129C — shared body (overlay slot 0x80128158, h_exact 86403336). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void *D_8011F738;
extern struct B16 D_800A5E88;
extern struct B16 D_800A5E98;
extern struct B16 D_800A5EA8;
extern void func_801719A4(int, int);
extern s32 func_80171990(u8*);
extern void func_80171384(void*);
void func_8017129C(int param_1) {
    S16 *p;
    func_801719A4(param_1, 1);
    p = (*(S16 * *)&D_8011F738);
    p[0] = (*(S16 *)&D_800A5E88);
    p[1] = (*(S16 *)&D_800A5E98);
    p[2] = (*(S16 *)&D_800A5EA8);
    *(unsigned short *)(*(int *)(param_1 + 0x20) + 0x2C) |= 0x20;
    *(int *)(*(int *)(param_1 + 0x20) + 0x80) = (int)p;
    ((void (*)(int))func_80171990)(param_1);
    ((void (*)(int))func_80171384)(param_1);
}
