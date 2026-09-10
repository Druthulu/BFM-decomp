/* func_80140D68 — shared body (overlay slot 0x80128158, h_exact 2e822a8f). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 *func_80140D68(out, src, idx, dx, ofs)
    s32 *out;
    Prim4 *src;   /* conformed to the fleet prototype; used only as (s32)src */
    s16  idx;
    s32  dx;
    s16  ofs;
{

    extern Hw4 D_8011516A[];
    /* §94 TYPE-CARRY: this typedef and its extern MUST be BLOCK-scope. extract_unit carries
       file-scope externs and #defines into each remapped sibling (Phase-27 _carry_macros) but
       NOT file-scope typedefs — so a file-scope Env_800D29F8 is silently dropped from every
       sibling and the family sweeps 0/137. Body-local typedefs DO survive (PTag_80140D68 below
       is the proof), so it lives here. */
         /* 0x14 stride */
    extern Env_800D29F8 D_800AE7BC[];


    u32 mhi;
    s16 *q;
    s32  a;

    out[0] = 0x04000000;
    *((u8 *)out + 0xC) = 0x70;
    *((u8 *)out + 0xD) = 0x10;
    mhi = 0x64808080;
    out[1] = mhi;
    *(u16 *)((u8 *)out + 0xE) = 0x4056;

    dx -= 0xD;
    q = (s16 *)(ofs * 2 + (s32)src);
    a = (u16)q[0] + (u16)D_8011516A[idx].x;
    a += dx;
    *(s16 *)((u8 *)out + 0x8) = a;
    *(s16 *)((u8 *)out + 0xA) = q[1] - 4;
    *(s16 *)((u8 *)out + 0x12) = 0x10;
    *(s16 *)((u8 *)out + 0x10) = 0x10;

    ((PTag_80140D68 *)out)->addr = *(u32 *)((PTag_80140D68 *)((D_800AE7BC[*(u16 *)&D_800B9A02].ot) + 2));
    ((PTag_80140D68 *)((D_800AE7BC[*(volatile u16 *)&D_800B9A02].ot) + 2))->addr = (u32)out;

    return out + 5;
}
