---
ts: 2026-11-06T09:58:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_bR5CCuoA4czAz9UuLZsk
---
Priority = floor_log2(n_refs) * n_refs * size / (death - birth). "We give shorter-lived quantities higher priority." Higher priority → allocated first → gets lowest reg.

So t: n_refs? t has 2 defs + 2 uses = 4 refs? tb: 1 def + 1 use = 2 refs. 

pri(t) = floor_log2(4)*4*1/(death-birth) = 2*4/7 = 8/7 ≈ 1.14
pri(tb) = floor_log2(2)*2*1/5 = 1*2/5 = 0.4

So t has higher priority → allocated first → v0. But mine has t=v1! Contradiction.

Unless t's live range in mine is different. Wait — mine line 59 `addiu v0,v1,-8`: t is v1. Hmm.

Maybe t is not 4 refs; maybe cse/combine made t's first def dead? Let's see: mine has lw v1,76(s0); sh v1,6(s0) — t used once. Then lw v1,80(s0); addiu v0,v1,-8. So t has 2 defs, 2 uses = 4 refs. tb: lw v0,84; sh v0,14 = 2 refs.

pri(t)=8/(59-52=7)=1.14; pri(tb)=2/(58-53=5)=0.4. t wins → v0. But observed t=v1. So maybe death-birth computed differently, or birth/death are 0/0?

Hmm, maybe qty_birth/death use INSN_UIDs (which differ from sequential index by ~prologue). But relative same.

Alternatively — maybe `t` and `tb` aren't block-local qtys at all: maybe they're in the global alloc pool because... no, they're local variables used in one block.

Wait, maybe local-alloc merged `t` with a hard reg via copy? Or maybe the addiu temp got v0 and t got v1? Let's see: t is v1 in both defs, the addiu result v0. If there were a qty for the addiu temp living 59-61 (2 insns, 1 ref... n_refs=1 → floor_log2(1)=0 → pri 0). Hmm.

Let me reconsider: perhaps cse canonicalized the two `t` definitions into distinct pseudos and one is a copy? Eh.

Actually, maybe the reason is: `t` is defined by lw and used by sh — local-alloc might allocate it v1 because v0 has a suggested copy preference? No.

Let me instead just experiment empirically. The goal is to get t→v0 and tb→v1, and fix the delay slot.

Approach: Since this is a small function, let me try real-C moves:
1. Swap declaration order of t and tb.
2. Introduce a temp for unk50 instead of reusing t.
3. Reorder the statements: compute both loads then both stores.
4. Use `u16` for stores.
5. Change `tb` usage.

Actually, the cleanest: make t's live range longer/shorter to flip priority. Or make tb's priority lower (shorter life). If I move the tb statements later (after t's second def), tb's life shrinks. But statement order affects code order.

Hmm, but here's a thought: the target's code order is exactly the source order: unk4C load, store, unk54 load, store, unk50 load, sub, store. So we must keep order.

Alternatively, maybe the difference is which pseudo is "t" and which is "tb" in terms of qty priority due to cse. Let me try declaring `t` and `tb` differently, e.g., make tb a pointer/u16, or use a temp.

Let me just try a batch of variants and score them. Since scoring is cheap, let me generate variants.

Variant A: swap declaration order `s32 tb; s32 t;` — no effect on local alloc (qty numbering might change tie-break only).
Variant B: don't reuse t for unk50; use a separate variable `s32 u; u = s0->unk50; s0->unkA = u - 8;`. Then t: 2 refs (def52 use54) = life 2; tb 2 refs life 5. pri(t)=1*2/2=1; pri(tb)=1*2/5=0.4 → t first → v0. And u: 1 ref? pri 0. So t=v0, tb=v1. That matches target! But adds a variable — does it change the code? The addiu would use the same reg. The target's line 55 `lw v0,80(s0)` then 59 `addiu v0,v0,-8` — target uses v0 for the unk50 value, same as t. With separate `u`, u would be v0 too (or v1). Since t=v0 and tb=v1, u (next qty) would get... after t and tb, next free: v0 and v1 both free after their deaths; u born at 55 while t dead at 54? t's death is 54 (sh). So u gets v0. Good.

Actually careful: with separate u, t lives 52-54, tb 53-58. t priority 1*2/2=1, tb 1*2/5=0.4 → t first → v0. tb → v1. u born 55: at 55, t dead (54), tb live (53-58) in v1, v0 free → u=v0. Then addiu v0,u,-8; sh v0. That matches target lines 55,59,61 (v0). 

But does it add an extra instruction? No, same instructions, just different pseudo names. The qty count changes (3 vs 2), but insn count same.

Wait but target line 52-53: lw v0,76; lw v1,84 — yes t=v0, tb=v1. 

So variant B likely scores better. But there's also the delay-slot issue (line 75 nop vs move a0,s0). That's the a0 clobber barrier's effect. Without it, mine emits nop. Hmm. The final block:
```
    ((void (*)(s32))func_80146C3C)(s0);
```
Target: jal, delay slot `move a0,s0`. Mine: jal, delay slot nop, and presumably `move a0,s0` before? Let me look at insns 74-75: mine `jal` then `nop`; target `jal` then `move a0,s0`. In mine, where's the move a0,s0? Not present in the diff, so mine has it somewhere earlier? Let me check mine's full stream — I printed both; insns 74,75 mine: jal, nop. Target: jal, move a0,s0. There's no `move a0,s0` elsewhere in mine (not marked as diff), so mine lacks it entirely? That can't be — the call needs a0=s0. Unless s0 is already in a0? No, s0 is $16.

Wait, `((void (*)(s32))func_80146C3C)(s0)` — s0 is the variable pinned to $16. Lever-free, s0 is a normal variable. In mine, maybe arg0 is passed directly: the compiler could keep arg0 in a0 and pass it... but arg0 was moved to s0 at line 2 (`move s0,a0`). Then a0 gets clobbered by the struct copy (line 15 `lw a0,8(a1)`). So at the call, it must move a0,s0. Mine line 74 jal, 75 nop — so the move a0,s0 must be at... hmm it's absent. That means the compiler put a0=s0 earlier and reorg couldn't fill? Let me re-look: maybe mine's line 73 `sw v0,28(s0)` is the delay slot of the j at 72, then 74 jal. Before 74, insn 68 `andi a1,a1,0xffff`. No move a0,s0. So mine doesn't set a0 at all?! That would be a miscompile... unless mine's `s0` is actually in $4 (a0) — but line 2 `move s0,a0` shows s0 is separate, and line 15 clobbers a0.

Wait, maybe in mine the call is `func_80146C3C` called with... the cast `((void (*)(s32))func_80146C3C)(s0)`. Hmm.

Let me look again at the dump: mine 74 `jal 0 <func_800CCB20>` — that's the disassembly label; the jal target reloc shows func_800CCB20 but actually it's the call. Both mine and target jal. Then 75 mine nop, target move a0,s0.

If mine has no move a0,s0 before the jal, then a0 holds... a0 was last set at line 63-64 `lui a0,0; addiu a0,a0,0` = &D_800CD7A4 for func_800233CC call at 67. After that call, a0 is caller-saved and dead. So passing a0 to the second call would pass garbage. But maybe mine's `s0` variable is allocated to a0? But line 2 move s0,a0 and line 15 lw a0,... hmm.

Wait — maybe the disassembler's `move a0,s0` vs `nop`: in mine, the instruction at 75 is `nop` but the *previous* instruction before jal (74) — actually reorg delay slot fill: the instruction that would be `move a0,s0` got scheduled elsewhere? Let me print the raw words with operands, not just mnemonics. My dump only prints mnem. Let me print full text (objdump line). Let me update the script to print the full instruction text.

Actually `md.insns_from_object` gives dict with "mnem" only? Let me check masked_diff.
