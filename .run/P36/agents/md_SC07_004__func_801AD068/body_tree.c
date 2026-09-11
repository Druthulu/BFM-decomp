void func_801AD068(void *arg0) {
    if (func_8012BEE8((s32)arg0) != 0) {
        func_80016714(*(void **)((u8 *)arg0 + 0xCC), 0x38);
        func_80016714(*(void **)((u8 *)arg0 + 0xD0), 0x38);
        func_8012C218(arg0);
    } else {
        /* target keeps this guard value in $v1; unpinned it lands in $a0 (5 mismatches) */
        register s32 v1 __asm__("$3") = *(s32 *)((u8 *)arg0 + 0x1C);  // !FAKE: pin $3 — NEEDED DIFFERS (P36 rung B tus9)
        s32 t;      /* address-taken => lives in 0x10($sp); every assignment is a real store */
        s32 *p;

        if (v1 < 15) {
            s32 v0;

            /* arms textually swapped vs. the natural reading so gcc emits the real
               `j .L801AD0D8` + delay slot instead of a delay-slot-fused shortcut */
            if (v1 >= 12) {
                v0 = 0xF - v1;
                v0 = v0 << 5;
            } else {
                v0 = v1 << 3;
            }
            func_80016450(v0 & 0xF8, 1);
        }

        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x18) += 0x1C0;
        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x1C) =
            *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x18);
        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x1A) += 0x80;
        *(u16 *)((u8 *)*(void **)((u8 *)arg0 + 0x20) + 0x12) += 0x100;

        func_801ADE1C(D_801B07F0, (u16 *)D_801F8A98, (s8 *)D_801F8AB8, (u8 *)D_801F8AE8);

        /* the two write-backs are ASYMMETRIC IN THE TARGET and the asymmetry is spelled here:
           D_801F8D18 is reached through a NAMED POINTER LOCAL, so its address is materialised
           (lui+addiu $a0) before the read and the read folds onto it (`lw 0($a0)`), sharing one
           base with the swl/swr. D_801F8D58 is named bare, so the read %lo-folds
           (`lw %lo(D_801F8D58)($v0)`) and the store re-materialises its own base ($a1). */
        p = &D_801F8D18;
        t = *p;
        t -= ((Obj_801AD068 *)arg0)->dE0;
        *(Align1W_801AD068 *)p = *(Align1W_801AD068 *)&t;
        func_801AD220(arg0, *(void **)((u8 *)arg0 + 0xCC));

        t = D_801F8D58;
        t -= ((Obj_801AD068 *)arg0)->dE4;
        *(Align1W_801AD068 *)&D_801F8D58 = *(Align1W_801AD068 *)&t;
        func_801AD220(arg0, *(void **)((u8 *)arg0 + 0xD0));
    }
}
