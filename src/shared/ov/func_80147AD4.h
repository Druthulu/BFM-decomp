/* guess_AddMoveVectorThenSetVelocity — shared body (overlay slot 0x80128158, h_exact 3e1daedf). ONE source: instantiated by #include at each
 * member's site in address order; the members are recorded in config/dedup.us.yaml (Phase 35). */
extern void func_80147CC8(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
extern void func_80147B5C(s32 a0, void *a1);
/* guess_AddMoveVectorThenSetVelocity: adds a1/a2/a3 to the move vector (+0x24/+0x28/+0x2C, each clamped to +-0x1F0000), then sets the velocity to it rotated by the model's angles
 * Confidence medium, xref chain: func_80147CC8: +0x24 += a1 etc. clamped +-0x1F0000; ApplyMatrixLV(rot(model +0x10/+0x12/+0x14), +0x24) -> buf; func_80147B5C: +0x10.. = buf
 * Names ledger: config/names.tsv guess_AddMoveVectorThenSetVelocity */
void guess_AddMoveVectorThenSetVelocity(s32 a0, s32 a1, s32 a2, s32 a3) {
    u8 buf[16];
    func_80147CC8(a0, a1, a2, a3, (s32)buf);
    func_80147B5C(a0, (s32)buf);
}
