---
ts: 2026-11-06T15:28:11Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rGffRppSAxp5mNas4P7B
---
make_regs_eqv(regno, first) — merges regno into first's qty. So for `(set flags raw)`, cse does insert_regs(dest=flags, classp, 1) where classp is the src's class? Let me look at the insn processing (cse_insn ~5968). Actually the key: when it processes `(set flags raw)`, src_eqv = canon_reg(raw) = raw (first). Then insert_regs(dest, src_eqv_class, ...) → make_regs_eqv(flags, raw) — flags joins raw's qty, with raw as first. Then canon_reg(flags) → raw. So uses of flags become raw, and uses of raw stay raw.

But in mine the andi reads s1 (flags). Hmm — that means the andi was rewritten to the merged reg which got allocated to s1, i.e. raw and flags are the same pseudo (one qty), and the allocator put it in s1. And the `move s1,v0` is the call-result → qty copy. Wait, the qty's "first reg" is the pseudo assigned by the call (`raw` = call result). The andi on the qty reads the qty's register = s1 (since the qty is global, s1). The move s1,v0 is the assignment of the call result to the qty. So there's ONE qty.

In the target, there are two qtys: raw (call result, v0) and flags (s1), the copy between them.

To prevent cse from merging: the asm creates a new value. A real-C equivalent must make flags' definition not a simple copy of raw.

New idea: assign flags from raw through a value-preserving arithmetic that gcc won't fold: `flags = raw & 0xFFFFFFFF;` folds. What about `flags = raw * 1;` folds.

Hmm, what about a *signedness* change: `u32 flags; flags = raw;` — modes are both SImode, and cse compares GET_MODE (both SImode) → merges.

What about `flags = (s32)(raw & 0xFFFFFFFF)` — folds.

The only non-foldable value-preserving ops are calls, volatile loads, and asm.

Hmm, but there's another trick: change the *structure* so the two uses don't need the same qty. What if the second if uses a *recomputed* value from the call? No.

Wait. Maybe the trick is to make the first test's operand a different expression that cse keeps in raw: e.g., test `raw` with a different mask value so cse doesn't rewrite? cse rewrites the operand regardless.

Hold on — canon_reg only rewrites regs whose qty is valid AND returns qty_first_reg. For raw's use at the andi: raw's qty is merged with flags; first = raw (since flags joined raw). So canon_reg(raw) = raw — no rewrite! Then why is the andi on s1?

Unless the merge went the other way: `(set flags raw)` → insert_regs for dest with classp = src's class. Let me read the cse_insn code at 5968.
