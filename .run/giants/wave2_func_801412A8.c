#include "common.h"
typedef struct { u32 addr : 24; u32 len : 8; } PTag_1412A8;
typedef struct { u32 *ot; u32 pad[4]; } Env_1412A8;
typedef struct { u32 tag; u32 w1; u32 w2; u32 w3; } Prim_1412A8;
extern Env_1412A8 D_800AE7BC[];
extern short D_800B9A02;
extern u16 D_80115116;
#define OT_1412A8            (D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot)
#define getaddr_1412A8(t)    (((PTag_1412A8 *)(t))->addr)
#define setaddr_1412A8(t, v) (((PTag_1412A8 *)(t))->addr = (u32)(v))
#define addPrim_1412A8(ot, p) (setaddr_1412A8(p, getaddr_1412A8(ot)), setaddr_1412A8(ot, p))
Prim_1412A8 *func_801412A8(Prim_1412A8 *out, int a1, int a2, int a3, u16 a4, u16 a5) {
    Prim_1412A8 *p = out;
    int y = a5;
    
    int color = 0xF800F8;
    int val;
    if ((short)a1) {
        val = 0x5E;
        if (D_80115116 & 1) { color = 0xF89C00; }
    } else if ((short)a2) {
        val = (short)a3 * 0x5E / (short)a2;
    } else {
        val = 0x5E;
        color = 0xF89C00;
    }
    p->tag = 0x03000000;
    p->w1 = color | 0x60000000;
    p->w2 = a4 | (((short)y + 0xA) << 16);
    p->w3 = val | 0x20000;
    addPrim_1412A8(&OT_1412A8[2], p);
    p++;
    p->w1 = 0x60080808;
    p->tag = 0x03000000;
    p->w2 = a4 | (((short)y + 0xA) << 16);
    p->w3 = 0x2005E;
    addPrim_1412A8(&OT_1412A8[2], p);
    p++;
    p->w1 = 0x60FFFFFF;
    p->tag = 0x03000000;
    p->w2 = (((short)y + 9) << 16) | (u16)(a4 - 1);
    p->w3 = 0x20060;
    addPrim_1412A8(&OT_1412A8[2], p);
    p++;
    p->tag = 0x03000000;
    p->w1 = 0x60E0C0A0;
    p->w2 = (((short)y + 0xB) << 16) | (u16)(a4 - 1);
    p->w3 = 0x20060;
    addPrim_1412A8(&OT_1412A8[2], p);
    return p + 1;
}
/* BANK BLOCKER (Phase-29, 2026-07-18): match_one MATCH (198) but §29 narrow-param def-side wall.
 * Def needs u16 a4/a5 (lhu reloads, the crack depends on it); caller func_80141100's canonical decl
 * is int(6). Changing the caller decl to u16 compiles but ADDS masking insns in the callers (SHA fail
 * 072fd9af vs d19c9580) — not byte-neutral. Genuine §29 wall (return-widen has a macro escape, param
 * narrow does not). Fable/careful caller-threading follow-up. Draft above is the byte-correct body. */
