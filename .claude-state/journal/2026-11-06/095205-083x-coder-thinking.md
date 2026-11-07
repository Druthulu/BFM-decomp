---
ts: 2026-11-06T16:52:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW48
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_2tuhxvhAOpydfYqsnlRy
---
This is about the equivalence classes. The relevant merge for fold_rtx: when an insn's source is a constant and some register has the same constant value, fold_rtx replaces the constant with that register if `CHEAPER`. Let me look at fold_rtx's handling.

Actually, maybe a simpler practical approach: since we know the target keeps each address fresh, maybe the original source used the symbols in a way that cse couldn't equate them: e.g. different *offsets* written into the pointer: `(void *)((s32)D_8018E2DC + 0)` vs plain. Identity.

Hmm, hold on. Let me reconsider the whole thing. Maybe the original source didn't have `s32 m` at all but passed the addresses through *different typed expressions*: e.g. group A passes `(void *)D_8018E2DC` (pointer) and group B passes `(void *)(s32)D_8018E2DC`. Both fold to the same rtx.

Wait — maybe I should look at the target's *first* argument: `D_801BFCC4 + 0x84`. Target loads D_801BFCC4 (a global pointer) fresh each call and adds the offset. That's already matching.

Let me look at this from a different angle: what does the C0505 catalog say about "cse-const-addr"? The walls list has "cse-const-addr — cse folds or substitutes a constant/absolute address the target keeps base-relative". Here the target materializes the constant at each use, and cse substitutes a register. The catalog says: "A named derived pointer q = p - k that cse keeps as a REGISTER address (find_best_addr, cse.c:2656-2721) — the la lever." So the *reverse* move: to STOP cse keeping an address in a register, we need... hmm.

Maybe the move is to make the address expression *not a constant at all* but a real computation that cse can't fold, e.g. `(void *)((s32)D_8018E2DC + (a0 & 0))` — that's a launder (identity).

OK here's another thought: what if the original source had the calls inside a `for` loop over a *pointer table*, and GCC's loop.c unrolled... no.

Wait wait. Let me reconsider the possibility that the target's code comes from a source where the address constants are passed *through a function-like macro* or where the symbols are declared as arrays of different element types so that the address arithmetic produces `const` rtx with different offsets: e.g. `D_8018E2DC + 0x30` written as `&D_8018E2DC[0x30]` — same const rtx.

Hmm, but note: target has `addiu a2,a1,48` — the +0x30 is computed from a1 (the address register), not a separate constant. That means the source's second argument `(void *)(m + 0x30)` was computed from m. Same as ours.

Let me look at what the *orig* (asm) cse2 does for the group B sites: reg 101 = symbol (fresh). And its uses: `(set (reg 104) (const (plus (symbol_ref) 48)))`. So the orig keeps separate pseudos per site.

Since the asm invalidates the value, the only way to reproduce is to have each site's value not be equivalent to the previous one. 

IDEA: What if the addresses are *loaded through a local variable that is assigned in a different basic block*? cse's table is per-EBB. If we introduce a label/branch between the sites, cse's EBB ends and the table is flushed. But a branch would add instructions.

Hmm, but maybe a *note* isn't enough. What about a `goto`? That adds a jump instruction — target has none.

What if the calls are separated by a *call*? Calls don't end the EBB (they don't flush cse's constant table, only memory).

Hmm.

Let me look at the target's other functions — maybe the same source pattern appears elsewhere in the game and was cracked. Search moves.md for "cse-const-addr" or similar launder cracks with the "symbol address" pattern. Let me grep the moves.md for "symbol" or "address".
