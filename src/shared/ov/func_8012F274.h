/* func_8012F274 — shared body (overlay slot 0x80128158, h_exact 0bfaee44). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80015978(s32 a0, s32 *a1);
extern void func_8004914C(void *a0);
extern void func_800491AC(void *a0);
extern void RotTransSV(s32 a0, s32 a1, void *a2);
extern void func_80015954(s32 a0, s32 a1);
static inline void tail_8012F274(s32 *in, s32 e) {
    s32 out[2];
    s32 flag[2];
    ((void (*)(s32 *, s32 *, s32 *))RotTransSV)(in, out, flag);
    ((void (*)(s32 *, s32))func_80015954)(out, e);
}
void func_8012F274(s32 a0, s32 a1) {
    s32 v[2];
    s32 p;
    func_80015978(a1, v);
    p = *(s32 *)(a0 + 0x20) + 0x34;
    func_8004914C((void *)p);
    func_800491AC((void *)p);
    tail_8012F274(v, a1);
}
