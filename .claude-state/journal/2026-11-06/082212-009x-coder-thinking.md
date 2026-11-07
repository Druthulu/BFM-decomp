---
ts: 2026-11-06T15:22:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO04x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_1IifqBWsHlPHKJ1QpoZU
---
Two launders in this function:
1. `__asm__ __volatile__("" : "=r"(flags) : "0"(flags));` — launder on `flags` after `flags = raw`.
2. `__asm__ __volatile__("" : "=r"(ret) : "0"(ret));` — launder on `ret` before `if (fire != 0)`.

Both are launder kind. I need to remove both and find real-C replacements that keep the score at 0.

Known techniques from moves.md:
- "real 2nd set `pv &= 0xFF000000`" — a real second set of the variable kills the sched1 birth boost / cse equivalence.
- "C0414 dead-reset cse-breaker": e.g., `m1 = 0;` after a call empties the cse equivalence class.
- "do-while(0) splits cse1 EBB" (C0535).
- "pointer reuse", "stmt order".

For the first launder: `raw = call(); flags = raw; __asm__(flags)` — the comment says the launder re-ties the global so cse can't substitute flags<->raw, keeping `raw` local ($v0) and `flags` global ($s1). A real second set of `flags`... but flags is used later as `flags & 0x8000` and `flags & 0x6000`. Hmm.

Actually the launder here is `"=r"(flags) : "0"(flags)` — output = input tie, which is essentially a no-op that forces the variable into a register at that point. Replacing with a real 2nd set: something like `flags = flags;`? No, that's identity (not allowed, and would be optimized away). A "real second set" e.g. `flags = raw | 0;`? That folds. Hmm.

Maybe `flags = raw; raw = flags;`? That's the two-copy thing.

Let me think about what cse does. `raw = call(); flags = raw;` — cse's canon_reg would substitute raw for flags, making one allocno (global since it lives across calls). The launder makes flags opaque: an asm with output "=r" and input "0" tied means the asm forces flags into a register and defines it, and cse can't propagate across the asm (it doesn't know the asm preserves the value). So flags stays a separate pseudo.

A real-C way to keep two distinct pseudos: make `flags` a genuinely distinct value, e.g. `flags = raw ^ 0;` folds. Something that cse can't prove equal... but then the later uses `flags & 0x8000` must still equal the same value semantically.

Options used in the moves list: "§373 dead-reset `p1 = 0;`" — that's when the variable is only used as an address holder, then reset. Not applicable directly.

For `flags`: if I write `flags = raw;` then use `flags` later — the issue is cse substitutes. What if I set `flags = raw & 0xFFFF;`? That changes value (raw is s32). No.

Alternative: use a different real statement that produces the same value but with a second set: e.g. `flags = raw; ... if ((raw & 0x6000) != 0x2000)` first uses raw. Then `m = flags & 0x8000;` and `flags & 0x6000`. So `flags` is only read after the first if. If I drop the launder and instead do something like re-assign flags after the first if: `flags = raw;` at the top and then before use `flags = flags | 0;` no.

Hmm — what about dead-reset style: since cse merges raw and flags, could I make `flags` a value derived in a way cse can't canonicalize: e.g. store raw to a local, reload? That would be a memory round-trip — real C: `s32 tmp; tmp = raw; flags = tmp;`? cse would still merge.

Actually the key: cse's canon_reg replaces a reg with its equivalent if the equivalent is cheaper/older. To prevent, make the equivalence not exist: `flags = raw;` creates a copy. cse merges copies. But if between the copy and the use there's a *store to memory* that could alias? No aliasing of regs.

Another known approach: `flags = raw; if ((raw & 0x6000) != 0x2000) {...}` — after the calls inside the if, the equivalence may... no, cse doesn't invalidate reg equivalences across calls for local regs? Actually cse does invalidate equivalences at basic block boundaries. raw's equivalence to flags: if the first `if` block is a separate EBB, then at the join... Hmm, the uses of flags are after the if. cse works per basic block. `raw = call(); flags = raw;` then `if ((raw & 0x6000)...)` — that's in the same block. Then after the if, `m = flags & 0x8000` is in a new block, and cse must know the value of flags. cse uses reg_eqv table within extended basic blocks.

Wait — the issue per comment: "cse canon_reg substitutes one for the other, so the surviving allocno is the GLOBAL". This is about register allocation merging (local-alloc/global-alloc coalescing? or cse's canon_reg rewriting all uses of one reg to the other). Since flags lives across calls it's global; raw is local. If canon_reg rewrites uses, the andi reads the global.

The launder asm makes the copy opaque. Real-C: prevent copy propagation at combine/rtl level. A dead-reset won't help here since flags must keep the value.

Idea: make `flags` computed differently, e.g. `flags = raw & 0xFFFF0000 | (raw & 0xFFFF)`? That's identity, not allowed (identity spellings don't count) and would fold anyway.

Hmm, maybe restructure: the first test uses `raw`, and flags is used later. What if flags is set *later* rather than at the top: `raw = call(); if ((raw & 0x6000) != 0x2000) {...}` then `flags = raw;` right before `m = flags & 0x8000`. But then the copy is immediately before uses in the same block — cse merges them trivially.

Alternatively, the value in the target: `andi $v0,$v0,0x6000` for the first test (raw in $v0) and later `$s1` holds the saved copy. The launder forces flags into a register at that point ($s1). Hmm — with the launder being a tie, flags gets a register. Without it, the copy is coalesced.

A real-C alternative that creates a genuine second definition: use the variable in a context that requires a real copy. E.g. `flags = raw;` and then `raw = flags;`? Both copies... cse would merge to one.

What about making flags a *different type*: e.g. `u32 flags = raw;`? cse still merges regs of same mode (SImode). 

What about assigning `flags = raw` and then modifying raw? E.g., the first `if` uses `raw`; if after the copy we assign `raw = 0;`? That's a dead reset — but raw is used in the first if. Sequence: `raw = call(); flags = raw; raw = raw & ...`? changes the test.

Hmm, wait. Let's reconsider: cse's reg_eqv. If `raw` is assigned and then `flags = raw` (a copy), cse records flags ≡ raw. Uses of flags get rewritten to raw if raw is "cheaper"? canon_reg: it replaces reg with the first in the equivalence class... Typically cse prefers the *older* reg or the one with lower regno. The launder forces a use of flags between so it's born.

The moves list has examples: "launder asm on vol dropped; vol 2nd set `vol = vol | 0x3000;` right before the call" — so they used a real second set that produces a different value legitimately. Here we need the same value.

What about `flags = raw & 0xFFFFFFFF;`? folds.

What if we split flags into two variables: one for the & 0x8000 test, one for the & 0x6000 test? The uses: `m = flags & 0x8000;` then `if (m != 0 || (flags & 0x6000) != 0x2000)`. If I write `flags` as `raw` directly in both uses, we lose the $s1 saved copy entirely. Target has TWO pseudos: local $v0 that dies at andi, global $s1 surviving the calls. Wait, but the calls are inside the first if. Let me re-read:

```
raw = call();
flags = raw;
asm(flags);
if ((raw & 0x6000) != 0x2000) {
    func_8012ADE4(...); func_8017E878(...);
    ...
}
m = flags & 0x8000;
if (m != 0 || (flags & 0x6000) != 0x2000) { ... }
```

So flags must survive the calls in the first if → $s1. raw dies at the andi → $v0. So actually we need a genuine second value live across the calls. The launder forces flags into a reg (a real move to $s1 presumably happens at the call site save).

Real C idea: instead of `flags = raw`, compute `flags` from something that cse can't equate. But it must equal raw's value.

Hmm, what about writing `flags = ((s32 (*)(s32))func_8012CBA4)(a0);` — i.e. call twice? No, changes behavior.

What about a real second set through a memory round trip: `*(volatile s32*)&local = raw; flags = *(volatile s32*)&local;` — that's essentially an asm-free launder via volatile; is that a "lever"? The brief says launder means no barrier/keepalive/asm. A volatile local store/load is a "real C" memory round trip but... it would be a lever of kind "barrier" probably. Actually the kinds taxonomy: launder = identity asm; barrier = something else. Volatile memory round-trip is likely "barrier" kind. Hmm. We can't add levers of other kinds either ("no new lever of any kind").

So we need genuinely different C that yields the same machine code. Let's look at what the cracked examples did for similar situations. E.g., func_8018AA98: "pv &= 0xFF000000 (compound assign) = a REAL 2nd SET of the pinned pv, kills the sched1 birth boost of the pv load". func_80182F3C: "real 2nd set `c = (u8)c;` after each `& 0xFF` keeps c in a1".

For flags: a real 2nd set would be something like `flags = raw;` ... then `flags = flags & 0xFFFFFFFF`? Not real.

Hmm, but maybe there's a legitimate restructure: The value flags is used twice: `flags & 0x8000` and `flags & 0x6000`. What if we assign flags after the first if from raw? i.e. `raw = call(); if ((raw & 0x6000) != 0x2000) { calls } flags = raw; m = flags & 0x8000; if (...)`. Then flags is a copy of raw in the join block. raw is dead after? No — raw used in the first if. In the join block, `flags = raw` and uses. cse would merge flags with raw (copy in same block) → one reg, but raw is already dead after the copy, so the merged allocno's live range... The target wants $v0 local (dies at andi) and $s1 global. With `flags = raw` after the if, the merged pseudo lives from call through the second if, i.e. across the calls? No, the calls are before, in the if. So the merged reg would live from call to second if, crossing the calls in the first if → global. Hmm but then both uses of raw before the if are the same pseudo; target has raw's first use ($v0) and flags' second use ($s1) different regs.

OK, this is subtle. Let me just start experimenting. First, set up: copy orig.c, and test removing the launders to see baseline score.

Let me look at the worked example notes for method.
