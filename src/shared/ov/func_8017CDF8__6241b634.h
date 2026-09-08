/* func_8017CDF8 — shared body (overlay slot 0x80128158, h_exact 6241b634). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147324(s32 arg0);
extern void func_8017D030(int);
void func_8017CDF8(Ent_8017BFE0_8017CDF8 *param_1)
{
    s32 t;
    t = param_1->f1c;
    param_1->f1c = t + 1;
    if (t < 0x20) {
        param_1->f2a = param_1->f2a - 0x10;
    } else {
        if (param_1->f30 == 0) {
            func_80147324(param_1->f2c);
        }
        param_1->f1c = 0;
        param_1->f02 = param_1->f02 + 1;
    }
    ((void (*)(Ent_8017BFE0_8017CDF8 *))func_8017D030)(param_1);
}
