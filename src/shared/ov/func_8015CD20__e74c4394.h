/* func_8015CD20 — shared body (overlay slot 0x80128158, h_exact e74c4394). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
s32 func_8015CD20(s32 arg0) {
    extern void (*D_80181160[])(struct Ent_8015CD20 *);
    extern u8 D_80181114;
    extern u8 D_80181304;
    extern u8 D_80181314;

    s32 temp_v0;
    s32 var_v0;
    struct Sub_8015CD20 *sp;

    ((void(*)())func_80149FB0)();
    if (((s32(*)(struct Ent_8015CD20 *))func_801496D4)(((struct Ent_8015CD20 *)arg0)) != 0) {
        D_80181160[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((struct Ent_8015CD20 *)arg0)->unk1BC = 0xA;
        ((s32(*)(struct Ent_8015CD20 *))func_80149724)(((struct Ent_8015CD20 *)arg0));
        if (((s32(*)(struct Ent_8015CD20 *))func_80148AFC)(((struct Ent_8015CD20 *)arg0)) & 0xFF) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80181114);
        } else {
            ((void(*)(struct Ent_8015CD20 *))func_80146D90)(((struct Ent_8015CD20 *)arg0));
        }
        return;
    }
    temp_v0 = ((struct Ent_8015CD20 *)arg0)->unk234;
    if (temp_v0 == 0) {
        if (((s32(*)(struct Ent_8015CD20 *))func_80148980)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80181304);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x15);
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0xAA;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_8014891C)(((struct Ent_8015CD20 *)arg0)) != 0) {
            ((void(*)(struct Ent_8015CD20 *, u8 *))func_80146DB8)(((struct Ent_8015CD20 *)arg0), &D_80181314);
            ((void(*)(struct Ent_8015CD20 *))func_80147A84)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *))func_801473EC)(((struct Ent_8015CD20 *)arg0));
            ((void(*)(struct Ent_8015CD20 *, s32))func_80154150)(((struct Ent_8015CD20 *)arg0), 0x14);
            ((struct Ent_8015CD20 *)arg0)->unkB8 = 1;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_801489E8)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 + 0x71;
            goto block_13;
        }
        if (((s32(*)(struct Ent_8015CD20 *))func_80148A48)(((struct Ent_8015CD20 *)arg0)) != 0) {
            sp = ((struct Ent_8015CD20 *)arg0)->unk20;
            var_v0 = sp->unk12 - 0x71;
block_13:
            sp->unk12 = var_v0 & 0xFFF;
        }
    } else {
        ((struct Ent_8015CD20 *)arg0)->unk234 = temp_v0 - 1;
    }
    ((void(*)(struct Ent_8015CD20 *))func_8014FA04)(((struct Ent_8015CD20 *)arg0));
    if (((s32(*)(struct Ent_8015CD20 *))func_8014E434)(((struct Ent_8015CD20 *)arg0)) == 0) {
        D_80181160[((struct Ent_8015CD20 *)arg0)->unk0](((struct Ent_8015CD20 *)arg0));
        ((void(*)(struct Ent_8015CD20 *, s32))func_80147078)(((struct Ent_8015CD20 *)arg0), 0);
        ((void(*)(struct Ent_8015CD20 *))func_80159B70)(((struct Ent_8015CD20 *)arg0));
    } else {
        ((void(*)(struct Ent_8015CD20 *))func_801725E0)(((struct Ent_8015CD20 *)arg0));
    }
}
