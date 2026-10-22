---
ts: 2026-10-22T13:07:43Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_UoOupdh0YeWB6ARKKRXg
---
- h1 (ax/by u32, ay/bx s16): 37 — worse.
- h7 (all u32 + (u16) 2nd sets + cast stores): 6 (same as g1).
- h8 (all s32 + (u16)): 6.

So g1/g7/h8 are at 6, with the remaining issues:
1. `lhu` vs `lh` (the loads) — because ay/bx became 32-bit.
2. the extra `andi` (the (u16) cast).
3. the addiu s1,s1,117 scheduling.

Hmm. The `lhu` issue: the loads of out.vx/out.vy are `lhu` in the target. With ay/bx as s16 they were `lhu`?? Let me verify: in the ORIGINAL (with the launders), the score is 0 → so the loads are `lhu` ✓ with ay/bx as s16.

Hmm! So GCC loads a SIGNED short as `lhu`?! That means GCC knows the value is used as unsigned... hmm, or the struct field type is unsigned.

Hmm, `typedef struct { short vx, vy, vz, pad; } SVECTOR;` → signed. But the load is `lhu`. Hmm! GCC's mips: when loading a signed 16-bit value into a register where only the low 16 bits are used... hmm, GCC's "LHI" insn? Hmm, in mips.md there's `LHI` = "load halfword into register (sign-extended?)". Hmm.

Actually! GCC's mips backend has this: a load of a QImode/HImode MEM into a pseudo → the "load_extend" optimization: if the value is used as unsigned, use LHU (zero-extend); if signed, use LH. GCC decides based on the *use* (the "extend" mode). Since ay (s16) is later used in `ay + 0x75` (an int promotion → a sign extension) hmm.

Hmm, but the target has lhu → so in the target the values are treated as UNSIGNED. And with the current source (which matches the target), the loads are lhu ✓.

So GCC decided "unsigned" for those loads. Why? Because of the launder? Hmm, no...

OH WAIT. Maybe it's because the value is loaded into a variable that is only used in 16-bit contexts (the stores) — hmm, but ay is used in `ay + 0x75` (an int add) → a sign extension would be needed → `lh`.

Hmm, but the target has `lhu` AND `addiu s1,s1,117` (ay + 0x75) — so the sign doesn't matter for the add (the upper bits are garbage either way) → GCC used the cheaper/zero-extending load ✓ (GCC's "load_extend" optimization picks the extension based on whether the sign matters; for an add, it doesn't → lhu is fine).

So the load's signedness depends on the uses. In my g1 (ay as u32), the uses need the FULL 32-bit value → GCC must sign-extend the s16 field → `lh` ✗.

So: ay/bx must stay s16 ✓ (h1 was 37 ✗ — hmm, but h1 had ax/by as u32 which changed other things).

So the combination I want: ay/bx s16 (for the lhu loads) + ax/by with a real 2nd set at no instruction cost.

h1 = ax/by u32 + (u16) 2nd sets + ay/bx s16 → 37. Hmm, worse. Why? The ax/by u32 conversions changed the stores' forms (`sh` of a 32-bit reg ✓ same) hmm, and maybe the allocation.

Hmm. Let me look at h1's diff to understand. Actually, let me think:

What if ax/by stay s16 but the 2nd set is a real conversion that's free? For an s16 variable, any conversion is a no-op ✗.

Hmm, so the 2nd set must be on a 32-bit variable → which changes the load's signedness ✗.

Hmm! Unless the 32-bit variable is NOT loaded from the struct but computed: e.g. `ax = ay + 0x7B` — if ax were u32, then ax = ay + 0x7B (the int add) ✓ and ax's 2nd set `ax = (u16)ax` → the andi ✗.

Hmm, the andi: 1 extra instruction. The target has 207 and g1 has 208.

**CAN WE AVOID THE ANDI?** What if the 2nd set's value is used only in 16-bit contexts → GCC's narrowing optimization drops the zero-extension → the 2nd set becomes free ✓ but then it's a no-op set ✗ (does the set count survive? if GCC's combine removes the extension but keeps the set (as a copy), the set count could survive!).

Hmm, g1's andi is present, so the zero-extension wasn't optimized away. Because by (u32) is used in `prim.y0 = by` (a 16-bit store) — hmm, and the andi is at mine[85], right where the 2nd set is.

Hmm, what if the 2nd set were `by = (u16)by;` and by's only use is the 16-bit store → GCC's combine: (set by (and (reg by) 65535)) then the store uses the low 16 bits → the `and` is redundant → combine should remove it! But it's there (in g1). Hmm, maybe because by is pinned to a hard reg ($20) → the RTL is (set $20 (and (reg $20) 65535)) — a hard-reg pseudo → combine can't remove it (the pseudo's value must be consistent) ✗.

So the pin on by forces the andi ✗.

Hmm! What if the 2nd set is on `ax` only (not by)? Then by keeps its launder... no, we can't keep the launder.

Hmm, so: we need ax AND by to each have a 2nd set, at zero instruction cost.

**IDEA: MAKE ax/by's 2nd set a *copy from a 16-bit temp* that GCC can coalesce?** Hmm.

**IDEA: What if the 2nd set is a store+reload?** no.

**IDEA: What if ax/by are declared as s32 but the 2nd set uses a SIGN extension (s16)?** → 2 extra insns ✗ (v7: 211).

Hmm, hmm. What about a 32-bit variable whose 2nd set is `(u16)` and whose value is NOT pinned (ax isn't pinned!) → for ax: (set ax (and (reg ax) 65535)) → if ax's uses are all 16-bit, combine removes the `and` ✓ (a normal pseudo can be rewritten). But for by (pinned $20) it can't ✗.

So: **by's 2nd set must be free too.** Hmm, by is pinned → its RTL is a hard-reg set → the `and` can't be removed → 1 extra insn.

Hmm, unless the 2nd set on by is a *copy* (a move) — a move is 1 insn ✗ (the target has no move for by... hmm, does it? Let me check the target's disassembly around the second block: maybe there IS a move!).

Let me look at the target's code around the second prim block. Let me dump the target for item 4 and examine.

That will tell me what the launders produced (the launder's set is zero-width, so no instruction, but the REGISTER may be re-tied).

Let me dump the target's disassembly (207 ins) and look at the region of the second block.
