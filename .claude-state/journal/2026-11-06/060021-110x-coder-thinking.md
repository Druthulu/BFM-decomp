---
ts: 2026-11-06T13:00:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_5AdpsdD4EcuR77nVsM8F
---
Mine: `li $2,1; beq $4,$2,$L666` — no `move v1,a0`.
Target: `move v1,a0; li v0,1; beq v1,v0`.

So iv2c coalesced into iVar2 (a0=$4). The launder asm prevented it.

Lever-free ideas to keep the copy: 
- Make iv2c a *different type* whose conversion needs a real copy — but the copy itself is what we want (`move v1,a0`), and the compare uses v1.
- The asm `"=r"(iv2c) : "0"(iv2c)` creates an output that's a new value (gcc can't coalesce because the asm output is a fresh pseudo).

Lever-free: make `iv2c` come from a computation that gcc can't merge: e.g. `iv2c = iVar2 & 0xffff;`? That would add an andi. Hmm, unless combine folds `andi` + compare... 

What about `iv2c = iVar2 + 0;`? folds.

What about declaring iv2c as `int` and initializing from a *different expression* that's equal but not obviously: e.g. `iv2c = (iVar2 ^ 0);`? folds.

Hmm, what about making iVar2 itself die at the copy so the copy is a "real" move? It already is: iVar2 = a0 and iv2c = a0; the compare uses iv2c. Since iVar2 is dead after (used later? iVar2 is used at `r = (uint)(iVar2 << 3) | c6b;` — yes! iVar2 is used later). So the copy `iv2c = iVar2` should be needed (both live)... but gcc coalesced iv2c with iVar2 (same register), which is legal since the values are equal and iVar2 isn't modified between.

That's cse/local-alloc coalescing: iv2c and iVar2 have the same value → cse replaces iv2c with iVar2 → the copy disappears.

To prevent cse from merging: make the copy a different *mode* (HImode) per the moves.md note (line 217): `tmp = (s16)t; u = tmp;` — HImode copy escapes cse's equivalence class.

I tried n2 (`iv2c = (short)iVar2;`) — no change. Hmm, maybe because iv2c is `int` so the (short) cast is folded away (iVar2's value is known to fit).

What if iv2c is declared `short` (n1) — that was also 7. Hmm, n1 changed `int iv2c;` to `short iv2c;` but the assignment `iv2c = iVar2;` — the conversion int→short might be a no-op (value known 1..16) → cse merges.

Per the moves.md note, the trick was `tmp = (s16)t; u = tmp;` — a two-step: an HImode temp then a wider copy.

Let me try: 
```
short sh = iVar2;
int iv2c = sh;
if (iv2c != one) ...
```
Hmm.

Or maybe the right approach: use the `s16` cast on the *source* with an explicit temporary of a different mode.

Alternatively, use a union or a `u16` variable read/written... 

Hmm, let me think about cse's merging: `iv2c = iVar2` is a reg-reg copy; cse records iv2c ≡ iVar2 and replaces later uses of iv2c with iVar2 (then the copy dies). To prevent, the copy must not be a plain SET of a reg to a reg: e.g., if the copy involved a subreg/extend, cse can't equate them.

So: `iv2c = (s16)iVar2;` — if gcc emits a sign-extend (sll/sra) that's 2 extra insns; but if it folds (range known), no insn at all and cse merges. n2 gave 55 ins (same as c1) so it folded.

What if we force an extend that combines into a single `move`? For a HImode copy: `(s16)x` where x is in a register — gcc might use `move` if the value is already sign-extended... but then cse merges.

Hmm. What if `iv2c` is `u16` and the compare is `iv2c != 1`? cse would merge too (same value).

OK, what if we make iVar2 die before the compare by reordering the statements? In the C:
```
{
    int iv2c;
    register int one __asm__("$2");
    iv2c = iVar2;
    one = 1;
    if (iv2c != one) uVar5 = 0;
}
uVar1 = ...;
...
r = (uint)(iVar2 << 3) | c6b;
```
If iv2c's value is needed only in the compare and iVar2 is used later, coalescing is still possible (same value, same reg).

What if the copy is made AFTER a point where iVar2 could have changed? no.

Honestly, the launder is a deliberate anti-coalescing device. Lever-free replacements for anti-coalescing: the cookbook C0535 do-while (EBB split) — cse wouldn't merge across a block boundary? cse1 works per EBB; if the copy and the compare are in different EBBs... but the copy and the compare are adjacent, in the same block.

Hmm, what about C0414 dead-reset: a dead reset of the source variable between the copy and the use would break the equivalence... but iVar2 is used later, so a reset would change it.

Let me try: `iv2c = iVar2; one = 1; if (iv2c != one)` → the `one = 1` is a pinned $2 set between them. That's already there.

What if we write the compare as `if (iv2c - one != 0)`? Hmm, that'd emit subu.

What if `if (iv2c != 1)` directly? Then `li v0,1`... but `one` is a pinned $2 variable that must stay (pin allowed). The target has `li v0,1` then `beq v1,v0` — so `one` in v0.

Hmm, what if `iv2c` is computed as `iVar2 << 0`? folds.

What if the copy goes through a *pointer*: `int *pi = &iv2c; *pi = iVar2;`? That's a memory store — no.

Let me try a few:
- o1: `short sh2 = (short)iVar2; int iv2c = sh2;`
- o2: `iv2c = iVar2 & 0xffff;` (andi might combine with the compare: `andi v1,a0,0xffff; li v0,1; beq` — extra insn)
- o3: do-while around `iv2c = iVar2;`
- o4: `iv2c = iVar2; one = 1;` in a do-while.

Actually, hmm: what about making `iVar2` be a different variable at that point: `int t2 = iVar2; iv2c = t2;` — more copies.

Wait. Actually, let me reconsider: in the target, the copy is `move v1,a0` where a0 = iVar2 (from `addiu a0,v0,1`). And `li v0,1` (one). So iv2c = v1.

If gcc coalesced iv2c with iVar2 (both a0), the compare uses a0. To break it, maybe make iVar2 *die* at the copy... it doesn't (used later).

Hmm, what if the later use of iVar2 is *before* the compare in the C? Looking at the C: `r = (uint)(iVar2 << 3) | c6b;` comes after. And `uVar1 = p4s | ... | uVar5;` uses uVar5 (set in the compare).

Hmm, what if I move the `r = ...` computation BEFORE the compare block? That changes the order of the store `*puVar3 = r` — target has it after.

OK, what about the `sw v0,-4(t0)` order diff (mine 40, target 39)? That's sched1 ordering.

Let me try the o-variants quickly. If none work, item 4 is a WALL at 7.

Actually — hold on. Let me reconsider the launder's exact semantics: `__asm__ __volatile__("" : "=r"(iv2c) : "0"(iv2c));` — an asm with output iv2c and input tied to the same reg. This makes gcc treat iv2c as a *new* value (defined by the asm), forcing a separate pseudo. Lever-free equivalents: none that are real C.

BUT: the shard's kinds are keepalive,launder. If I keep the launder, it's a WALL/PARTIAL:PARTIAL:launder. Per the expert: "PARTIAL:<kept> means every row kind not in <kept> is gone from win.c" — so PARTIAL:launder means keepalive is gone but the launder stays, and win.c must score 0 with only that kind kept.

So: if I remove the keepalive asm and KEEP the launder asm, does the body score 0? That would be PARTIAL:launder — a valid result! Let me test: c1 + restore the launder asm.

Similarly for item 3: PARTIAL:launder (keeping the launder, dropping the keepalive) — if it scores 0, that's a PARTIAL.

Let me test both! That's the smart move: PARTIAL is a legitimate result and much easier.

Item 4: restore the launder, keep the keepalive removed → score?
Item 3: restore the launder (`"=r"(decoy) : "r"(ba)`), remove the two keepalives → score?

Let me test item 4 first.
