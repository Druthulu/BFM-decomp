---
ts: 2026-11-06T21:16:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cW50
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_B67xjWeb4sv49OZYPkeO
---
q moved things around: the sll is v1 and the load went to a1. Different. Not helpful.

Time: ~14:26, 28 min. I should stop soon. But let me try one more strong idea before recording a wall.

Idea: the launder raises e's refs. What if I make e a *parameter-like* value that's used twice by making the lim load use e via the SYMBOL but forcing a separate materialization? 

Actually, here's a new thought: what if we use `e` for the lim load and the condition, but the lim load uses `e` in a way that produces the target's `lui at; addu at,at,a1` (symbol+off)? In target, the lim load address is sym+off. If e is REG_EQUIV=sym, then `e + off` can be folded to `sym + off` (lui at; addu). And the condition's `e + off + 2` would be... also foldable to sym+off+2. But cse chose to keep e materialized for the condition. Why? Because the condition needs e as a base in a register (a0) after the slt, while lim is before. Actually in target, the condition address `addu v0,a0,a1` uses a0=e (materialized). So the compiler decided to materialize e for the condition but use sym directly for lim. That's exactly the REG_EQUIV behavior: the lim use can use the equivalence (sym+off), while the condition use... also could. But it materialized e.

Hmm, this is getting too deep.

Let me try one more class: change the *type* of `off` to s16 or unsigned to alter its priority/live length. And try making `idx` used directly for the lim load (so off is only for the condition): `lim = D_801E8F78[idx][0];` already. 

Actually — what if I make off's live range longer by moving its definition to right after the call (before idx)? off needs idx. What if I define off = (s16)param_2 * 4? No, idx comes from the array.

Let me try reducing off's n_refs: write the condition address as `(u8*)e + off + 2` and the lim address as `D_801E8F78[idx][0]` — off is used in both (cse). If I write the condition as `((s16*)((u8*)e + off))[1]`, same.

What if I compute the condition address from `idx` directly: `D_801E8F78[idx][1]` — then off is only used for the lim address (n_refs=2). But p.c (natural array) gave 148 insns. Because the condition's address becomes a separate computation. Hmm, p had e removed entirely.

What if we KEEP e for the condition but compute the address as e + off (needs off). 

OK, let me try: reduce off's refs by making the lim load use `e` (so off only in the condition)? No, that's 146.

Let me try making e have n_refs=4 via a genuine double-use that cse can't merge: use e in the condition's two operands at DIFFERENT offsets that both load from e+off:
- first: `*(s16*)((u8*)e + off + 2)` (offset +2)
- second: `*(s16*)((u8*)e + off + 2)` — merged.

What if the second is `*(s16*)((u8*)e + (off + 2))` — same.

I keep hitting the same wall.

Let me try the "real 2nd set" via a branch on the loaded value:
```
s16 v = *(s16*)((u8*)e+off+2);
if (v == 0 || (func(v)&0xFF)==0) idx=-1;
```
This was c.c, score 4. e still 1 use.

What if `e` is used to load the value, and also compared:
```
if (e[1] == 0 || ...)
```
where e = sym (not row). e[1] = sym+2, not sym+off+2. Wrong.

Hmm.

Let me try a genuinely different structure that might shift the allocation: compute `lim` and `e` in the opposite order and use `e` for the lim load but keep the symbol for the condition... no.

Given time, let me make one more attempt: use a `union` or `struct` to make the address computation produce a 2nd use. Or, simplest: change `e`'s declaration to be initialized at decl (`s16 *e = (s16 *)D_801E8F78;`) and remove the assignment statement. Init at decl is in the catalog. Might change birth/refs. Test.

Also try: declare e as `s16 *e;` and assign `e = (s16 *)D_801E8F78;` but move the assignment BEFORE `off` and `lim` (earlier birth) — tested v2 (e first, lim, off) = 4.

Let me test init-at-decl and a couple more, then wrap.

Actually, wait. Let me reconsider the score 4 diff: "register pairs (mine -> target, count): a1->a0 x3, a0->a1 x2". This says the diff is just a permutation. The score counts 5 instruction mismatches. If I can't fix allocation, this is a WALL. But the task wants a lever-free body that scores 0 (MATCH). Score 4 is a WALL (best=4).

But hold on — maybe there's a simple trick: the `pad[2]` and the declaration ORDER of locals could affect global-alloc's allocno numbering and tie-breaks. The allocno order tie-break is by allocno number (lower first). If I change the order in which pseudos are created (e.g., declare/assign e before off), the allocno numbers change. But we tried statement reorder.

Actually — allocno numbers are assigned by pseudo reg numbers, which are assigned in order of RTL creation (source order). If e is defined before off in the source, e's pseudo number < off's, so on a tie e wins. But we tried e-first (v2) = 4. Did e actually get a lower pseudo number? The source order changed but the compiler may reorder. Hmm.

Let me try making e's assignment come before the lim load AND before off (v2 did e first, lim, off) = 4. So no.

Let me try init-at-decl (which may create the pseudo earlier, at function entry). Test t.c:
```
s16 *e = (s16 *)D_801E8F78;
```
and remove the assignment. This makes e live from entry to use — long live range, lower priority → worse. Probably.

Let me instead try to REDUCE e's live range: assign e as late as possible, i.e., right before the condition, but target has it before slt. The slt is `t < lim`; e's def is before slt in target. So e must be defined before the slt. Currently e is after lim, before slt. That's already the latest.

Hmm, what if e is defined before `lim` but after `off`? Then e's live range extends over the lim load (birth earlier) → longer → lower priority. Worse.

What if off is defined AFTER e? e born first, off born later. Then off's live range shorter → higher priority → off still wins a0.

I'm convinced this is a genuine WALL (global-alloc priority: off outranks e because e is last in the allocno order). Wait, e is LAST (lowest priority) even though its computed priority seems higher. Let me understand why e is last. Maybe allocno_live_length for e is not 4. The flow dump said "Register 79 used 2 times across 4 insns". But that's from ONE flow dump. There might be multiple flow dumps (before/after certain passes). The relevant one is the last flow before global-alloc. Let me check which dump line 18 belongs to. Line 12-42 are early. Let me find the flow dump nearest to global-alloc. There may be a "Register 79 used X times across Y insns" repeated later. Let me grep all occurrences of "Register 79 used" in cand.i.flow.
