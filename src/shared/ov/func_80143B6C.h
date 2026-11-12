/* guess_SpawnActorType1C — shared body (overlay slot 0x80128158, h_exact 0911480d). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern s32 guess_SpawnActor(s32 arg0, s32 arg1, s32 arg2);
/* guess_SpawnActorType1C: spawns an actor of type 0x1C with argument a1 next to parent a0; for a1 == 0 copies the parent model's +0x12 rotation word
 * Confidence medium, xref chain: guess_SpawnActor(0x1C, a1, a0); if spawned, a0 has a model and a1 == 0: child +0xFC = *(u16 *)(model + 0x12)
 * Names ledger: config/names.tsv guess_SpawnActorType1C */
s32 guess_SpawnActorType1C(s32 arg0, s32 arg1) {
    s32 iVar1;
    iVar1 = guess_SpawnActor(0x1C, arg1, arg0);
    if (((iVar1 != 0) && (*(s32*)(arg0 + 0x20) != 0)) && (arg1 == 0)) {
        *(s16*)(iVar1 + 0xFC) = *(u16*)(*(s32*)(arg0 + 0x20) + 0x12);
    }
    return iVar1;
}
