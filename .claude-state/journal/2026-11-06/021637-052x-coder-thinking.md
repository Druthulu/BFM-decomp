---
ts: 2026-11-06T09:16:37Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_FY8ptdzQDqQ769iU6ZhE
---
Priority = (floor_log2(refs) * refs * size) / (death - birth), higher first.

Target: res and flg both in the tail block. res: refs 3 (set 0, set &D, use asm) — but the asm is a USE at the end, so death = asm. flg: refs 2 (set load, use test). birth/death: res birth at `res=0`, death at asm. flg birth at load, death at test.

Hmm, with the pin res is hard $2 so not allocated. So we can't compare directly.

In lever-free, local-alloc allocates v0 to whichever has higher priority. Mine gives v0 to flg. So flg's priority > res's. Let's compute: floor_log2(3)=1, 1*3*1=3; floor_log2(2)=1, 1*2*1=2. res death-birth: res=0 to asm; flg: load to beqz.

The asm keepalive `__asm__("" : : "r"(res))` — is res live to the asm? Yes. So res birth earlier (res=0), death later (asm) → longer life → lower priority. flg: shorter life → higher priority. So flg wins v0.

To make res win v0, shorten res's life or lengthen flg's. Real-C moves:
- Set res as late as possible: `if (D_801F84AC) res = &D; else res = 0;` — then res birth at the branch; life still to asm. flg removed. Then res's life is from the if to asm (short) → wins v0. That's variant a4 but with if/else instead of res=0 before.
- Or make flg live longer (e.g. use flg later) — adds insns.

Variant: 
```
if (D_801F84AC != 0) {
    res = (s32 *)&D_801F832C;
} else {
    res = 0;
}
```
Then target codegen would be beqz → else; res=&D; ... but target's code has `move v0,zero` in the delay slot then lui v0. Hmm, target's structure: beqz v1,L; move v0,zero; lui v0;addiu v0; L. With if/else in source, codegen would be `beqz v1, Lelse; lui v0...; b Lend; Lelse: move v0,zero`. Different.

Actually target's structure corresponds exactly to `res = 0; if (flg != 0) res = &D;` with res=0 sunk into the delay slot. So source is right; only allocation differs.

What if res is declared `register`? Plain `register s32 *res;` without asm — "no `register` vars" forbidden by constraints! "no `register` vars, no `__asm__`". Right.

Hmm. What real-C move can make res win v0? res refs 3 vs flg 2 — refs part is higher for res but life longer. Let me compute precisely: qty_birth/death in insn counts. If res=0 and flg=load are adjacent and both die near the end... res death at asm (last insn), flg death at beqz. Life difference maybe 4-5 insns.

Alternative: give res MORE refs without adding instructions? E.g., `res = 0; ...; if (flg != 0) res = &D;` → refs 3. Could write `res = 0;` then `res = flg ? &D : res;`? adds.

What about making flg's life *longer* by using it in a way that costs no insn? E.g., `if (flg != 0)` then later `flg` used again — adds.

What about making res a different width (u32* vs s32*)? no.

Hmm, alternatively: maybe the real move is to eliminate the separate flg variable and load D_801F84AC directly in the test, but that changes codegen: `lw v0; nop; beqz v0` — the temp would be the load result; then res=0 must be before? Target: lui v1;lw v1;nop;beqz v1;move v0,zero. The load temp is v1. If source is `res = 0; if (D_801F84AC != 0) res=...`, the compiler creates a temp for the load — a pseudo with refs 2 (set, use), birth at lui, death at beqz — same priority as flg. Mine a4 gave same result.

Hmm. What if res is assigned *before* the load and the load's temp is created after: target order is load first, then res=0 in delay slot. Actually target: `lui v1; lw v1; nop; beqz v1,L; move v0,zero` — res=0 is in the delay slot of the branch, i.e., after the load and test in insn order. So the source order res=0 then if(flg) gives that.

Priority: res refs 3 vs flg 2. Let me actually compute qty values via a dump. The alloc_table.py tool can show local-alloc? Let me check its usage — it's for headers though. Alternatively use the .lreg dump.

Actually, maybe I'm overcomplicating. The 13 score has 2 components: reg swap + scheduling (li a0,11 placement). Let me try more variants systematically. But time budget per item... I've spent maybe 15 min. Let me think about which items are most likely crackable and allocate effort.

Actually, let me reconsider item 2 more cleverly: what if we don't use a `flg` variable at all and write:

```
res = 0;
if (D_801F84AC != 0) res = (s32 *)&D_801F832C;
```

Target needs the load into v1 then beqz v1. Mine (a4) produced same swap. What if we make the comparison use the value twice, e.g. `if (D_801F84AC > 0)`? same.

What if `res = 0;` comes *after* the if? 
```
res = &D_801F832C;
if (D_801F84AC == 0) res = 0;
```
Codegen: lui v0;addiu v0; lw v1; beqz v1, L; ...; L: move v0,zero. Not target order.

Hmm target order is: load, branch, res=0 (delay slot), res=&D. That's exactly `res = 0; if (flg) res = &D;`.

Let me look at the lreg dump to see the priorities. I can run cc1 dumps on the TU. tools/cc1_dumps_tu.sh <tu> <tag>. Let me check its usage.
