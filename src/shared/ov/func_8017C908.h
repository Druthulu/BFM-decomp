/* func_8017C908 — shared body (overlay slot 0x80128158, h_exact da26f0d2). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void ReadGeomOffset(s32 *a0, s32 *a1);
extern s32 RotTransPers(s32 a0, s32 a1, s32 *a2, s32 *a3);
extern void func_8004921C(s32 a0, s32 a1);
void func_8017C908(s32 a0, s32 a1) {
    s32 ofx;
    s32 ofy;
    s32 sxy;
    s32 p;
    ReadGeomOffset(&ofx, &ofy);
    func_8004921C(0, 0);
    RotTransPers(a0, a1, &sxy, &p);
    func_8004921C(ofx, ofy);
}
