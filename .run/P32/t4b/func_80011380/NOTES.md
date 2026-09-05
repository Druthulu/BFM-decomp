# func_80011380 (main/boot, -O0, 192 ins) — S83 hand probes (residual 6 = §474 PROVED floor: MULT(MULT(i,2),2) unmerged)
Target idx 70–83: `lw v0,0x10(fp)`; `lui/lw v1 = D_80074784`; nop; `addu a0,v1,zero` (t = load: assignment shape, load+copy);
`sll v1,a0,1; addu a0,v1,zero` (t = t*2); `sll v1,a0,1` (t*2); `lui/addiu a0 = &D_800629D6; addu v1,v1,a0; lbu a0,0(v1); sb`.
The draft's statement-expression `({ register s32 t = D_80074784; t = t * 2; t; }) * 2` gives 192 ins with the six register
roles shifted (load direct into t, no copy). Probes S2/S2b/S2c/S3 — a block-scoped `register s32 t` with the target's
assignment shape (`t = D; t = t*2; ...[t*2]`, initializer / compound / one-doubling variants): ALL 193 ins / 131 mismatched —
the block's (use) bracket / decl adds an instruction and shifts every branch (§474's expand_decl/use_variable finding).
Untested: the SAME two-statement shape with `t` declared at FUNCTION scope but as a `register` var whose other uses keep its
life short (stupid.c computes life from the (use) at function end → whole-function life → would take an $s reg — refute by
measurement); a `register` var that already exists in the function (reuse one of the case block's existing register locals,
e.g. the switch selector copy) so no new decl/use is emitted. Fable: read stupid.c:497 adjacency + expand_end_bindings.
