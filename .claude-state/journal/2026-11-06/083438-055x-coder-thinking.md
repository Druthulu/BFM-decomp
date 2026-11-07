---
ts: 2026-11-06T15:34:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mceVBF5OUj9kqX4sgGDk
---
Now I see the RTL:
- insn 21: reg 79 = v0 (raw)
- insn 24: reg 73 = reg 79 (flags = raw)
- insn 26: reg 73 = asm (opaque def of flags)
- insn 28: andi on reg 79 (raw)

So the target needs: reg 79 (raw) → $v0, reg 73 (flags) → $s1.

The asm is a real second set of reg 73. The question: what real-C statement produces a second set of flags that is value-preserving and free?

KEY INSIGHT: The asm's output is a *tied* operand — it both reads and writes flags. In C, a value-preserving second set that isn't folded... 

What about `flags = flags;`? gcc's cse deletes it. But `flags = (flags, flags)`? no comma expr in C89? It's fine but folds.

Hmm, what about `flags = flags ^ 0xFFFFFFFF ^ 0xFFFFFFFF;` folds.

What about a *conditional*: `flags = (flags != 0) ? flags : flags;` folds.

Hmm.

Alternative approach: change the *source* so that the first test uses the call expression directly and the copy is made from it:

```
raw = ((s32 (*)(s32))func_8012CBA4)(a0);
if ((raw & 0x6000) != 0x2000) { ... }
```
and then for the later uses, re-use `raw`. But we need $s1. What if we make a second variable that's *loaded from memory*? no.

What if we exploit the fact that the target's andi reads the hard reg v0 — maybe the C source used the call result inline in the condition and assigned it separately? Like:

```
s32 t;
if (((t = call()) & 0x6000) != 0x2000) ...
flags = t;
```
Same thing.

Hmm, what about making the second variable assigned via a *different call site*: no.

Let me think about the allocator side instead: what if we let cse merge, but force the merged pseudo to be *local* by making its live range not cross calls... impossible, the value is used after the calls.

What if the value used after the calls is recomputed? E.g. the second if could use `raw` but raw is recomputed... no.

OK here's another thought: maybe use a *second variable that is assigned in both branches* as I mused, but the copy at the top comes from a real second set... Hmm.

Wait, actually, maybe the crack is to move the copy to a place where cse's EBB ends, so the equivalence is not propagated. cse1 processes EBBs. If `flags = raw` is in a *different EBB* from the andi... The copy must be before the calls (live across). The EBB containing the call: calls don't end EBBs in cse1? A call invalidates call-clobbered regs but not local pseudos.

What if we split with a do-while(0) *around the copy* — tried a2: no change. Because cse1's canon within the block still deletes the copy? a2's dump? The copy in its own block: `(set flags raw)`; cse canon_regs src raw→raw, dest flags→? insert_regs(dest flags, classp) → joins raw's qty. Then the set becomes `(set raw raw)` → deleted. The block boundary doesn't help because the equivalence is *within* the copy's block.

What if the copy is `flags = raw` where raw is *not yet in the table* (i.e., first use)? Then flags gets a new qty and raw joins flags' qty, first = flags. Then uses of raw would be rewritten to flags! Hmm, interesting: in the orig RTL, insn 24 is `(set 73 79)`. If instead we write `flags = call(); raw = flags;` (b1), then insn: `(set flags v0)`; `(set raw flags)`. cse: flags = v0 → flags gets a qty from v0's class... v0 is a hard reg. Then raw joins flags' qty. Uses of raw → canon to the qty's first reg. If flags is first, raw's use at the andi becomes flags — same problem, and the andi on flags ($s1).

Unless the *first* reg in the qty is v0 (hard reg): canon_reg returns `first >= FIRST_PSEUDO_REGISTER ? regno_reg_rtx[first] : REGNO_REG_CLASS(first)==NO_REGS ? x : gen_rtx(REG, mode, first)` — for a hard reg first (v0), it generates (reg:SI 2)! So uses would become hard reg v0! That's exactly the target: the andi reads $v0!

Wait: `(set flags (reg v0))` — insert_regs for dest flags with classp = v0's class. Hmm, in cse_insn, for a simple set the dest gets `insert_regs (dest, src_elt, 1)`? If the src is a hard reg, does it merge flags into v0's qty? Let's look: the code around 6342-6500. Actually, `(set (reg 73) (reg 2 v0))` in the orig: after cse, insn 21 remained `(set (reg/v:SI 73) (reg:SI 2 v0))` in the a7 dump — wait, in the a7 dump, insn 21 was `(set (reg/v:SI 73) (reg:SI 2 v0))`. Hmm, in the orig dump, insn 21 is `(set (reg/v:SI 79) (reg:SI 2 v0))` and insn 24 `(set (reg/v:SI 73) (reg/v:SI 79))`.

So cse did NOT merge flags into v0's qty (good, hard regs aren't merged). raw (79) got its own qty from `(set 79 v0)`.

In b1 (`flags = call(); raw = flags;`), the RTL would be `(set flags v0)` then `(set raw flags)`. cse: flags gets a new qty (not merged with v0). Then raw joins flags' qty → first = flags. Uses of raw → flags. Same problem (andi on flags).

Hmm.

Let me think about what determines qty_first_reg: `make_regs_eqv(regno, first)` — the first reg keeps its qty. In `(set dest src)`, cse calls insert_regs(dest, src_elt, 1) where src_elt is the hash entry of the src. If src_elt exists and is a REG, make_regs_eqv(dest, src_reg) → dest joins src's qty, first = src. So `flags = raw` → first = raw. Uses of flags → raw. The andi on raw stays raw. But then why did the a7 build show the andi on s1?

Because the andi's operand reg 79 (raw) and flags reg 73 are the same qty (first=raw=79). canon_reg(79) = 79. The andi stays on 79. The later uses (flags, 73) become 79. So one pseudo reg 79, live from the call to the second if → $s1. And the copy `(set 73 79)` was deleted. So the andi reads 79 → $s1. Yes.

Target: andi on reg 79 = $v0 → so in the target, reg 79 must be *local* (die at the andi), and flags a separate pseudo.

So the only way: flags must NOT be equivalent to raw. A real second set of flags that gcc can't fold.

What if flags is defined by an expression involving a *memory load* that gcc must keep? E.g. `flags = raw;` where raw is... no.

What about making `raw` a `volatile`? That's a barrier lever.

Hmm, what about the "real 2nd set" of flags where the second set is a *different value that's corrected by a later op*? For example:

```
flags = raw & 0xE000;    // b2 → combine folds the later masks
```
The problem with b2: combine folded `(and (and raw 0xE000) 0x8000)` → `(and raw 0x8000)`? Actually the diff showed `andi s1,v0,0xe000` replacing `move s1,v0`, meaning flags = raw & 0xE000 was computed into s1, and the later `andi v0,s1,0x8000` remained? Wait the diff replaced mine[8] `andi s1,v0,0xe000` with target `move s1,v0` — only one insn difference there. So mine had: `andi s1,v0,0xe000` then later `andi v0,s1,0x8000` and `andi v1,s1,0x6000`. Target: `move s1,v0` then `andi v0,s1,0x8000`, `andi v1,s1,0x6000`. So b2 is nearly right except flags = raw & 0xE000 wasn't folded. If combine had folded the masks, flags' value would be raw and the copy would be a move... but then flags ≡ raw again.

Hmm wait, actually the target's later andis are `andi v0,s1,0x8000` and `andi v1,s1,0x6000`. If flags = raw & 0xE000 and combine folded `& 0x8000` into `& 0x8000` of the inner... it could produce `andi s1,v0,0x8000` and `andi v1,s1,0x6000` — that's not what we see (target has the andis on s1 which holds raw).

So the value in s1 must be raw itself.

OK, radical: what if we use an *intermediate that is a different C type with the same mode*? E.g. `union { s32 a; u32 b; } u;` no.

What if flags is a `float`/`double`? No.

What about making `flags` a *pointer*? `void *flags = (void*)raw;` — POINTER mode on mips is SImode too. cse: insert_regs checks GET_MODE only, both SImode → merges.

Hmm.

What about making flags a *different mode* but the uses cast: e.g. `s16 flags` and uses `((s32)flags & 0x8000)` — changes codegen.

What about `HImode` where the value is sign-extended already? raw is a call result; the two uses only care about bits 0x8000 and 0x6000 — those are bits 15 and 13/14, which ARE in the low 16 bits. So a truncation to s16/u16 preserves the masks! The andi 0x8000 on a u16 value... If flags is u16: `flags = raw;` truncates to 16 bits (andi 0xFFFF or nothing if stored in HI). Uses: `flags & 0x8000` → zero-extended u16 & 0x8000 = raw & 0x8000. `flags & 0x6000` same. So semantically identical!

Codegen: `u16 flags = raw;` — the assignment to an HImode pseudo... gcc 2.7.2 with -O2 keeps HImode pseudos in registers, using SUBREG. The value would need masking (andi 0xFFFF) at the set. Hmm, but if the uses only mask with andi anyway, combine might fold.

Target later: `andi v0,s1,0x8000` and `andi v1,s1,0x6000` — with u16 flags, s1 would hold the truncated value; andi on it is the same. The copy `move s1,v0` — would a u16 copy emit just a move? In gcc, `(set (reg:HI 73) (subreg:HI (reg:SI 79) 0))` — on mips, HImode regs are handled as SImode with the value in the low bits? The mips backend defines HARD_REGNO_MODE_OK and uses `movhi` = sll/sra? Let me just TEST it. Cheap.

Variant c: `u16 flags;` and `flags = raw;` — but the uses `flags & 0x8000` would need `(u32)flags & 0x8000`. Since flags is u16, integer promotion makes `flags & 0x8000` an int operation; gcc will zero-extend flags (andi 0xFFFF) then andi 0x8000 — could combine to one andi 0x8000? Since flags was already truncated... 

Let's just try. Variants:
- d1: `u16 flags;` assignment `flags = raw;` with the uses unchanged.
- d2: `s16 flags;`.

Also, another idea: use two different variables for the two masks:
```
raw = call();
if ((raw & 0x6000) != 0x2000) {...}
...
m = raw & 0x8000;
```
no copy at all → single pseudo. Not target.

Let me also consider the possibility that the target's copy is not `flags = raw` but something else that forces a real copy: e.g., a *function argument* or a *return value*. Hmm.

Let me test d1/d2. Need to add the ret=0 fix too. Let me restructure gen.py so that a `d` variant = ret fix + flags type change.

Actually let me just make the gen script apply ret=0 for all variants from now on (a7 base) except where testing. Simpler: add variants d1, d2 with both fixes.

I'll edit gen.py: add at the top after removing asms: if VAR starts with 'd', apply ret=0 fix, then flags changes.

Let me rewrite gen.py more cleanly to avoid the growing mess.
