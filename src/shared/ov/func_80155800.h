/* func_80155800 — shared body (overlay slot 0x80128158, h_exact ac3af9dd). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_8001382C(s32 a0, void *a1, void *a2);
extern void func_80146DB8(s32 *a0, s32 *a1);
extern s32 func_80146E98(s32 a0);
extern void func_801473EC(s32 *a0);
extern void func_80147A84(s32 arg0);
extern u16 func_801487F4(s32 *a0);
extern u16 func_80148800(s32 *a0);
extern s32 func_801488A8(u8 *a0);
extern int func_80148AFC(void *a0);
extern s32 func_801496D4(void *a0);
extern void func_80149704(void);
extern void func_80149AD4(s32 *a0);
extern void func_80149B14(s32 *a0);
extern void func_80154134(u8 *a0);
extern void func_801599A4(void *a0);
extern void func_80159B3C(void *a0);
s32 func_80155800(s32 arg0) {
    extern s32 D_8011F730;
    extern int func_80155A44(int);
    extern s32 func_80155F80();
    extern int func_80155FF8(int, int);
    extern void func_8015A230(s32*);
    extern s32 func_80161208(void *);
    struct { s16 a, b, c, d, e, f, g, h, i, j, k, l; } sp10;
    u8 temp_v0;
    u8 temp_v1;
    s32 var_v1;
    ((Ent_80155800_80155800 *)arg0)->unk44 |= 2;
    if (((Ent_80155800_80155800 *)arg0)->unkB8 == 0x8000) {
        ((void(*)(void *))func_801599A4)(((Ent_80155800_80155800 *)arg0));
        ((void(*)(void *))func_80159B3C)(((Ent_80155800_80155800 *)arg0));
        return;
    }
    ((void (*)(void *))func_80155A44)(((Ent_80155800_80155800 *)arg0));
    if (((s32(*)(void *))func_80148800)(((Ent_80155800_80155800 *)arg0)) & 0x80) {
        temp_v1 = ((Ent_80155800_80155800 *)arg0)->unk1A9;
        if (temp_v1 >= 4U) {
            if (((Ent_80155800_80155800 *)arg0)->unk1C0 != 0) {
                ((void(*)(void *))func_80148AFC)(((Ent_80155800_80155800 *)arg0));
                ((void (*)(void *))func_80155F80)(((Ent_80155800_80155800 *)arg0));
                ((void(*)(void *))func_80154134)(((Ent_80155800_80155800 *)arg0));
                temp_v0 = ((Ent_80155800_80155800 *)arg0)->unk1AA;
                var_v1 = temp_v0 + 1;
                if (temp_v0 == 0) {
                    var_v1 = 2;
                } else if (var_v1 >= 5U) {
                    var_v1 = 1;
                }
                ((Ent_80155800_80155800 *)arg0)->unk1AA = var_v1;
                ((void(*)(void *))func_80149B14)(((Ent_80155800_80155800 *)arg0));
                return;
            }
            if (((Ent_80155800_80155800 *)arg0)->unk1AA >= 2U) {
                if (((Ent_80155800_80155800 *)arg0)->unk1A8 == 0) {
                    if (temp_v1 != 0) {
                        goto block_13;
                    }
                    goto block_15;
                }
                goto block_22;
            }
block_13:
            ((void(*)(void *))func_80148AFC)(((Ent_80155800_80155800 *)arg0));
            ((void (*)(void *))func_80155F80)(((Ent_80155800_80155800 *)arg0));
            ((void(*)(void *))func_80154134)(((Ent_80155800_80155800 *)arg0));
            ((void(*)(void *))func_80149AD4)(((Ent_80155800_80155800 *)arg0));
            D_8011F730 |= 3;
            return;
        }
    }
block_15:
    if ((((Ent_80155800_80155800 *)arg0)->unk1A8 == 0) && (((Ent_80155800_80155800 *)arg0)->unk1A9 != 0)) {
        if (((s32(*)(void *))func_801496D4)(((Ent_80155800_80155800 *)arg0)) != 0) {
            ((void(*)(void *))func_801599A4)(((Ent_80155800_80155800 *)arg0));
            ((void(*)(void *))func_80149704)(((Ent_80155800_80155800 *)arg0));
            return;
        }
        if (!(((s32(*)(void *))func_801487F4)(((Ent_80155800_80155800 *)arg0)) & 8) && (((s32(*)(void *))func_801488A8)(((Ent_80155800_80155800 *)arg0)) != 0)) {
            ((void(*)(void *))func_801599A4)(((Ent_80155800_80155800 *)arg0));
            ((void (*)(void *))func_8015A230)(((Ent_80155800_80155800 *)arg0));
            return;
        }
        goto block_22;
    }
block_22:
    if (((s32(*)(void *))func_80146E98)(((Ent_80155800_80155800 *)arg0)) == 0) {
        ((void(*)(s16, void *, void *))func_8001382C)((s16) -(s32) ((Ent_80155800_80155800 *)arg0)->unk20->unk12, &((Ent_80155800_80155800 *)arg0)->unk234, &sp10);
        ((void(*)(void *, void *))func_80146DB8)(((Ent_80155800_80155800 *)arg0), &sp10);
        ((void(*)(void *))func_80147A84)(((Ent_80155800_80155800 *)arg0));
        ((void(*)(void *))func_801473EC)(((Ent_80155800_80155800 *)arg0));
    }
    if (func_80161208(((Ent_80155800_80155800 *)arg0)) == 0) {
        ((void (*)(void *, u8))func_80155FF8)(((Ent_80155800_80155800 *)arg0), ((Ent_80155800_80155800 *)arg0)->unk1AA);
    }
}
