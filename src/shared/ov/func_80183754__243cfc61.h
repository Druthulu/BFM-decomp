/* func_80183754 — shared body (overlay slot 0x80128158, h_exact 243cfc61). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80188F08(void);
extern void func_8016F094(s32 *a0);
extern s32 func_800CF854(void);
extern void func_800D1744(s32 *a0);
extern void func_80183B64();
extern void func_80181CE0(void);
extern void func_80183C94(void*);
extern s32 D_8018EA90;
extern s32 D_801A7F50;
extern s32 D_801A7FF0;
extern s16 D_800B9ABA[];
void func_80183754(s32 *a0) {
    s32 v0;
    ((void (*)(s32 *))func_80188F08)(a0);
    func_8016F094(a0);
    v0 = func_800CF854();
    if (v0 != 0) {
        *(s32 *)((s32)a0 + 0x204) = 1;
    } else {
        *(s32 *)((s32)a0 + 0x204) = 0;
    }
    *(s32 *)((s32)a0 + 0x208) = 0;
    func_800D1744(&D_8018EA90);
    *(s16 *)((s32)a0 + 0x136) = 2;
    *(s32 *)((s32)a0 + 0xB0) = (s32)&D_801A7F50;
    *(s32 *)((s32)a0 + 0xCC) = (s32)&D_801A7FF0;
    *(s16 *)((s32)a0 + 0x132) = 0;
    *(s32 *)((s32)a0 + 0x44) = *(s32 *)((s32)a0 + 0x44) | 0x3000000;
    D_800B9ABA[0] = 0x1E0;
    func_80183B64(a0);
    func_80181CE0();
    v0 = *(u8 *)((s32)a0 + 0x214);
    *(u8 *)((s32)a0 + 0x214) = v0 + 1;
    ((void (*)(s32 *))func_80183C94)(a0);
}
