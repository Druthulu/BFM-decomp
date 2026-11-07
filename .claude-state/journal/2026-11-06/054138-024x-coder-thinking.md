---
ts: 2026-11-06T12:41:38Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO01
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_tnrzh3tYtsgIwKzVbdDg
---
I lost the mnemonics (parts[2]). Let me print both mnemonic and operands.

Anyway, the sequence around 342-346:
- 342: li a1,0xff (m24 = 0xFFFFFF → li a1,255? then... hmm)
- 343: andi? a1,a1,0xffff? 
- 344: lui a2,0xff00
- 345: sll a0,a0,0x2
- 346: addu a0,a0,s8

Hmm, so target has lui a2 at index+3 relative to mine. So target order: 342 li a1,0xff, 343 ..., then sll/addu (ott computation), then lui a2.

Wait, mine: lui a2 at 344, then sll a0, 2; addu a0, s8. Target: sll, addu first then lui a2.

Hmm, but that's exactly what the barrier does: ott computed, then mFF born. Removing the barrier lets sched1 hoist the pinned `lui a2` above the sll/addu.

Why does the pin set get hoisted? Because a pinned hard-reg set is placed FIRST in its block by sched1 (per the header comment). With the barrier, mFF's block starts at the barrier point which is after ott.

So: I need to keep mFF's birth after ott without an asm. Real C options:
- Make ott's computation be in a separate basic block, e.g., a `do { ott = ...; } while (0);` — that splits the cse1 EBB, and in sched1 a do-while(0) may also create a NOTE_INSN_LOOP_BEG? Hmm, C0535 says do{}while(0) splits cse1 EBB. But sched1 works on basic blocks. Does a do-while(0) create a separate basic block? It creates a NOTE_INSN_LOOP_BEG/END which affects loop.c, and flow may split. Actually a `do { } while(0)` where the body is a single statement... gcc represents it as a loop with a conditional at the end that's constant-folded; typically the loop is removed by jump opt, leaving a NOTE_INSN_LOOP_BEG/END but not a BB boundary.

Hmm. Alternatively: put the ott computation *inside* an if statement whose condition is true — that creates a basic block boundary. E.g.:

```
if (idx < 0x1000) {   // already checked above: `if ((u32)idx >= 0x1000) return;`
    ott = ...;
}
```
Hmm, that adds a test unless the compiler knows. 

Better real-C move: make mFF's value depend on ott? No.

Alternative: use `mFF` *before* it's assigned in a way that... no.

Alternative: since mFF is a pinned var, maybe assign mFF via a computation that's not a simple constant but is folded later: e.g. `mFF = 0xFFFFFF ^ 0xFFFF;` — that would be constant-folded at expand time to a `li`, still same. Birth order in sched1 depends on the RTL insn order which is source order... Hmm but the pin-set-first rule.

Hmm wait — actually the "pinned hard-reg SET placed first in its block" is sched1's priority boost. So within a block, the `lui a2` is scheduled first. With the barrier, ott is in the previous block so it stays before.

Real C to force a block boundary between ott and mFF: an `if` that the compiler cannot fold but whose body is trivial... that changes codegen.

Alternative approach: reverse it — make mFF not be a hard-reg pin? No, pins may stay but can't be removed? Actually "levers of other kinds the def already had may stay, never added" — we may remove them too. Removing the pin would change codegen and likely break other things.

Hmm, but wait. Another approach: give mFF more uses/refs so it's not... no, the issue is scheduling order not allocation.

Let me reconsider: what if I compute ott as part of the statement where mFF is used, but in a separate statement that comes AFTER mFF? I.e., swap source order: assign mFF first, then compute ott? Then target order would be mFF then sll/addu — but the target wants sll/addu then lui a2. So no.

Alternatively: `ott` could be computed by an expression that depends on `prim`, e.g. as an offset from prim. Hmm.

Another idea: use the pinned mFF to compute something needed by ott? No.

Alternative: convert the two `and`+`or` statements into a form where mFF's use forces it later. E.g., use mFF inside a compound expression evaluated after ott. In RTL, `li a2,0xff00` is an insn born at the point of the *first use* of mFF if the assignment is at the top... Actually the assignment `mFF = 0xFF000000;` creates a set at that program point. If I instead write the mask inline:

```
*(u32 *)prim = (*(u32 *)prim & 0xFF000000) | (*ott & m24);
*ott = (*ott & 0xFF000000) | ((u32)prim & m24);
```
then cse would... each use would create its own li a2, two of them, unless cse merges. But cse merges constants into one pseudo? The constant 0xFF000000 in cse becomes a pseudo if cheap_constant... With -O2 on mips, constants are usually loaded per use unless cse creates a REG_EQUAL and global cse keeps one. Hmm, risky but worth trying: it's the "init at decl" style alternative — actually let's try `u32 mFF = 0xFF000000;` declared/initialized at decl? No, decl-init would put it at function entry (way earlier).

Hmm. Let me look at this from the other direction: what did the "barrier" accomplish originally, and is there a known MATCH move from moves.md for a similar situation? Let me grep moves.md for "barrier" lines that mention "pin" or "birth" or "block".

Actually, since we're at 20-30 min budget per item and 5 items, and this is a 408-insn function, maybe a PARTIAL is realistic here: keep barrier 4 (and maybe others), crack some. PARTIAL is score 0 while keeping only the listed kinds. So if I crack barriers 1,2,3 but keep barrier 4, that's PARTIAL:barrier with score 0.

That's a valid outcome! PARTIAL:barrier = win.c scores 0 keeping only barrier levers. So I should aim for maximum cracking but a PARTIAL is a legitimate result.

But let's try to crack b4 quickly with a couple of real-C moves:
1. `u32 mFF = 0xFF000000;` moved after `ott` assignment but as a separate statement — same as now.
2. Try computing ott with a different expression shape: `ott = ot + idx;` (ot is u32*, idx is s32) — this yields sll+addu too but maybe different birth order. Actually `(u32 *)(idx * 4 + (s32)ot)` — the multiply by 4 becomes sll. Alternative: `ott = (u32 *)((u8 *)ot + (idx << 2));` Hmm, idx<<2 is sll then addu. Same.

Actually the problem isn't ott's shape, it's the sched1 hoisting of the pinned set. Unless... the pinned set gets placed first only when it's the *only* set in the block? Hmm.

3. Add a dependency: make mFF's value derive from a variable that's computed near ott. E.g.:
```
u32 maskhi = 0xFF000000;  // not pinned
```
No, mFF is pinned; we want to keep it.

4. Maybe make ott's computation be part of the same statement as the load that follows, i.e.:
```
*(u32 *)prim = (*(u32 *)prim & mFF) | (*(u32 *)((u8*)ot + (idx<<2)) & m24);
```
and drop the ott variable, then define ott for the second statement... but the second statement needs ott.

Let me try a few variants quickly:
- v1: `u32 mFF; ...` assign after ott (current) — score 2.
- v2: inline 0xFF000000 in both stores (remove mFF var but keep pin? no).

Hmm, let me consider: does the barrier-4 removal actually matter for the "kinds gone" requirement? kinds = barrier. All 4 barriers must be gone for MATCH. But PARTIAL:barrier means win.c keeps barrier(s). So if I crack 1,2,3 and keep 4, that's PARTIAL:barrier.

Given the budget, let me first see if b2 (score 28) and b3 (score 10) can be cracked with real C. Those are bigger.

Barrier 3 (score 10, count 407 vs 408): 
```
tc = tpage & 0x10;
ub = sy;
if (tc) {
    ua = ub - 0x100;
} else {
    barrier
    ua = ub;
}
ub = ua + rec->h - 1;
```
Without the barrier, one instruction disappears (count 407 vs 408). The barrier presumably prevents jump2/cross-jump from merging, or prevents dbr from filling a delay slot. Actually removing an insn → probably the `j` of the else arm gets deleted after cross-jump merges the two arms... no, arms differ (subu vs move).

Hmm: with the barrier, the else block is non-empty and starts with the asm. Without it, `ua = ub;` in else. Then `if (tc) ua = ub - 0x100; else ua = ub;` → could be converted to `ua = ub - (tc ? 0x100 : 0)`? Or jump2 merges `j` into the join. Count drop by 1 = the `j` instruction removed (fall-through rearrangement). And the barrier prevents the arm from being a fall-through target...

Let me look at the actual diff for b3.

Let me be efficient and get diffs for b2 and b3.
