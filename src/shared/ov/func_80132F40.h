/* func_80132F40 — shared body (overlay slot 0x80128158, h_exact c5b3a460). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8012F038(int param_1, short *param_2, short *param_3);
extern void guess_RotTransSVWithMatrix(s32 a0, s32 a1, s32 a2);
extern s32 func_80135888(s32, s32, s32, s32);
extern u16 guess_g_PlayerPosX; // Names ledger: config/names.tsv guess_g_PlayerPosX
extern u16 guess_g_PlayerPosY; // Names ledger: config/names.tsv guess_g_PlayerPosY
extern u16 guess_g_PlayerPosZ; // Names ledger: config/names.tsv guess_g_PlayerPosZ
extern u8 D_80126BE0[];
void func_80132F40(s32 arg0)
{
    Svec_80132F40 v[4];
    register Svec_80132F40 *q __asm__("$17");  // !FAKE: pin $17 — NEEDED DIFFERS (P36 rung B headers1) wall:cse-copy-merge
    register s16 *p __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:cse-copy-merge
    register s32 h __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:cse-copy-merge
    register s32 c __asm__("$2");  // !FAKE: pin $2 — NEEDED DIFFERS (P36 rung B headers1) wall:cse-copy-merge
    register s32 hh __asm__("$4");  // !FAKE: pin $4 — NEEDED DIFFERS (P36 rung B headers1) wall:cse-copy-merge
    s32 w;
    s32 m;
    q = &v[1];
    v[0].vx = guess_g_PlayerPosX;
    v[0].vy = guess_g_PlayerPosY;
    v[0].vz = guess_g_PlayerPosZ;
    v[1] = v[0];
    if (func_80135888(*(s32 *)(arg0 + 0x20), *(s32 *)(arg0 + 0x58),
                      (s32)D_80126BE0, (s32)q) != 0) {
        do { } while (0);
        p = (s16 *)((*(s32 *)(arg0 + 0x58) & 0x0FFFFFFF) | 0x80000000);
        w = p[4];
        h = p[5];
        hh = h;
        c = (h < w);
        if (c) { m = hh; } else { m = w; }
        func_8012F038(*(s32 *)(arg0 + 0x20) + 0x34, &v[0], q);
        v[1].vy = m;
        guess_RotTransSVWithMatrix(*(s32 *)(arg0 + 0x20) + 0x34, q, &v[0]);
        guess_g_PlayerPosX = v[0].vx;
        guess_g_PlayerPosY = v[0].vy;
        guess_g_PlayerPosZ = v[0].vz;
    }
}
