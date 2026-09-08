/* func_8012A328 — shared body (overlay slot 0x80128158, h_exact 6f62feba). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 func_80012F74(s32, s32, s32, s32);
void func_8012A328(void)
{
    extern s8 D_801152C0;
    extern s16 D_801152C2;
    extern s16 D_80126940;
    extern s16 D_80126942;
    extern s16 D_80126944;
    extern s32 D_80126B58;
    extern s16 D_80127080;
    extern s16 D_80126CAE;
    Obj_80126B58 *p = (Obj_80126B58 *)&D_80126B58;
    s16 *q;
    s32 a, b;
    if (*(u8 *)&D_801152C0 != 0) {
        a = D_80127080; b = D_80126CAE;
        if (D_801152C2 < ((a - b) < 0 ? (b - a) : (a - b))) {
            q = &D_80126942;
            *q = func_80012F74(*q, p->f156, 4, 1);
        } else {
            q = &D_80126942;
            *q = func_80012F74(*q, D_80127080, 4, 1);
        }
    } else {
        s16 *r = &D_80126942;
        *r = func_80012F74(*r, D_80126CAE, 4, 1);
    }
    D_80126940 = p->f154;
    D_80126944 = p->f158;
}
