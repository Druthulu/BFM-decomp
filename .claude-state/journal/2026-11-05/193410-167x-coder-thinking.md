---
ts: 2026-11-06T02:34:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_ZL5wvvhMtXyNr82F6dmN
---
`own_thread_p(thread, label, allow_fallthrough=1)`: for the fall-through, allow_fallthrough=1 → returns 1 if no CODE_LABEL in the thread (from thread to the first active insn) — basically the immediate insns before the first active insn. If there's a label right at the fall-through start, own_thread_p returns 0. So a label between the branch and the addiu (or at the addiu) → own_fallthrough = 0 → the fall-through fill is skipped → nop.

But wait, `own_thread_p(NEXT_INSN(insn), NULL_RTX, 1)`: thread = NEXT_INSN(insn) = the delay-slot position. It loops from thread to `active_insn = next_active_insn(PREV_INSN(thread))`. PREV_INSN(thread) = the branch insn; next_active_insn(branch) = the addiu (skipping notes/labels). So the loop covers insns between the branch's NEXT and the addiu, i.e., notes and labels. If a CODE_LABEL is there → return 0.

So if we can get a CODE_LABEL between the bnez and the addiu at reorg time, the fill is blocked! And the label would be deleted at final if unreferenced... but jump2 (before reorg) deletes unreferenced labels. So the label must be referenced at jump2 and reorg time, but the reference must disappear before final? The only pass between reorg and final is final's own... Hmm, the label would remain in the final asm if referenced.

But wait — the label could be referenced by a branch that is in the *same* thread and gets optimized by reorg? Or a label referenced by a *jump table*? Hmm.

Actually, maybe the label doesn't need to be referenced at all: jump2 deletes unreferenced labels, but what about a label created AFTER jump2? Does anything between jump2 and reorg create labels? reorg itself creates labels when filling delay slots (emit_delay_sequence creates a label!). Hmm.

Hold on: reorg processes functions and may create labels; but the fill decision for our branch happens in the same pass.

Hmm, what about the `dbr` pass being run twice ("Reorg pass #1, pass #2")? The dbr dump showed "Reorg pass #1 ... Reorg function #0 ..." etc. Reorg runs multiple passes over all functions. A label created in pass 1 could affect pass 2. But our function is compiled separately (one function per rest_of_compilation), so "Reorg function #0/#1" refers to... hmm, the dbr dump for a single function shows two "Reorg function" entries — maybe the prologue and the body?

OK, time check: item 2 is at ~20 min. The label trick is speculative. Let me test it cheaply: add a label between the branch and the store in C via a goto structure:

```
if (unk98 == 0) {
    goto L;      // forward goto to L
L:
    unk34 = state + 1;
    ...
}
```
The `goto L; L:` with L immediately after: the compiler may delete the jump at the first pass (jump-to-next) AND delete the label (unreferenced). So no label at reorg.

What if the goto is from *inside* a do-while so the label is referenced and the jump survives? Hmm.

What about `if (unk98 == 0) { ... }` where the body is also the target of the switch's dispatch? No.

Let me test the simple goto anyway (it's cheap) plus a few label-ish variants:
d1: `if (unk98 == 0) { goto L0; L0: unk34 = state+1; ... }`
d2: `if (unk98 == 0) { if (state) goto L0; L0: ... }` (adds branch)
d3: wrap the if body in a `do { ... } while (0)` with a `break`? no.
d4: `while (0) { ... }`? 

Let me also try the "case 0 body as a labeled block" idea:
```
case 0:
L0:
    if (unk98 == 0) { ... }
```
A label at the case body, unreferenced → deleted.

Hmm.

Actually — WAIT. Let me reconsider: maybe the target's nop is not about own_fallthrough but about `stop_search_p`: if the first insn of the fall-through thread is an ASM_INPUT... that's the barrier. Lever-free alternatives that make stop_search_p return 1: a JUMP_INSN or BARRIER (no), a SEQUENCE (no), an asm (no). Or `labels_p` true with a CODE_LABEL: `stop_search_p(trial, !thread_if_true)`. For the fall-through fill, thread_if_true=0 → labels_p = !0 = 1 → a CODE_LABEL stops the search! So a label at the fall-through start stops the scan → no fill.

But the label must exist at reorg time. So we need a label that survives jump2 (referenced) but whose reference doesn't appear in the final asm... impossible? Unless the reference is a `j` that reorg converts/deletes. Hmm.

What if the label is referenced by the *switch dispatch* (a jump table entry)? The function uses a switch on state with cases 0,1,2. GCC might emit a jump table if there were more cases... With 3 cases it uses comparisons (target shows beq/bne). So no table.

What if the label is referenced by a branch that reorg's `delete_jump` removes as redundant? For example, a branch to the label that is the same as the fall-through... 

OK, I'll try the goto variants and then likely WALL. Let me also try the "case 0 body written as if/else with an empty else" etc.

Actually, here's another thought: the *barrier* is a memory clobber. A lever-free equivalent could be a real *memory access* that emits no code? No.

What about a `(clobber (mem))` from a function call with a struct return? no.

Let me try d1-d4.
