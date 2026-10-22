---
ts: 2026-10-22T12:40:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG16
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_EyhpqiYFgGhGLK2v1RP1
---
Baselines are 0 (as expected: the tree carries the levers). Now the goal: remove the launder (row kind) and get score 0 still.

Also count includers. Let me write a script listing includers for each header.

Note the `!FAKE: launder` comment lines. When removing the asm, we need the compiler to still produce the same code without the launder. That's the hard part: the launder is there because the plain C doesn't produce the target's code.

Let's think per item.

### Item 2: func_8012C2D0 (19 ins) — smallest, start here.

```c
s32 func_8012C2D0(void)
{
    s32 p;
    s32 it;
    it = (s32)D_80120194;
    __asm__ __volatile__("" : "=r"(it) : "0"(it));  // launder
    p = it + 0x658C;
    goto test;
copy:
    return it;
test:
    it = (s32)D_801202A0;
    __asm__ __volatile__("" : "=r"(it) : "0"(it));  // launder
    if (it == p) goto zero;
body:
    if (*(u16 *)it == 0) goto copy;
    it += 0x10C;
    if (it != p) goto body;
zero:
    return 0;
}
```

The launder on `it` prevents GCC from... hmm, what does the launder do here? The asm with output "=r"(it) and input "0"(it) tells gcc that it is a register, and the value is unchanged. It creates a "copy" pseudo of it, breaking cse equivalence, i.e., it forces `it` to be in a register and not folded.

Without the launder, `it = (s32)D_80120194;` then `p = it + 0x658C`. GCC would materialize D_80120194 into a register (it needs `it` later at `copy: return it;`). Actually `it` is reassigned at test: to D_801202A0. Hmm, so `it` has two definitions.

Wait: at `copy: return it;` — it returns the value of it at that point (D_80120194). Hmm, but the loop modifies `it` by += 0x10C. So `it` at copy is D_80120194 + k*0x10C. Right, it's a pointer walking.

Without the launder, GCC's cse might treat `it = (s32)D_80120194` and `it = (s32)D_801202A0` — different symbols, so no merge. But the issue: the launder prevents gcc from knowing that the value of `it` after the asm equals before, so it keeps a copy pseudo → different register allocation.

Let's just try: remove the two launder asm lines and score. Then iterate with real-C moves.

Note the constraint: "identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack". So we need a genuine removal, and the score must be 0.

Let me try.

### Item 3: func_8012C750 — same launder pattern (2 launders in else branch).

### Item 1: func_8012B4B8 — launder on `src` which is pinned to $5. Removing the launder: `src = (int *)&D_800AE620;` then reads src[0..7]. The launder forces src to be materialized in $5. Without it, GCC might do `lw t0, 0($a0)` directly from the base... Actually with `src` being a register var pinned to $5, GCC will keep it. But cse's find_best_addr may substitute the constant address into the loads (the "cse-const-addr" wall seen in moves.md!). That's exactly the wall: `launder | func_80183098 | WALL cse-const-addr — cse: find_best_addr rematerialises the +4 address for cam->y (lui+addiu) instead of the base reg; only an opaque (asm) base keeps lh 4(s1)`.

So for 8012B4B8, removing the launder will likely trigger cse-const-addr: the loads `t0 = src[0]` become `lw t0, 0(base)` with base rematerialized per use, i.e. lui/addiu per access rather than one $5. That's the wall to overcome.

Hmm, but wait: `src` is `register int *src __asm__("$5")`. The pin means it's a hard-reg pseudo. Does find_best_addr still rematerialize? The moves.md entry for func_80183098 says "only an opaque (asm) base keeps lh 4(s1)". Hmm.

Alternatively maybe the answer is: keep the pin but write the address differently, e.g. use a static const or make `src` a pointer into a struct... Hmm.

Actually the trick for cse-const-addr: if we make the address come from something GCC can't fold, like a pointer stored through an opaque path. But we can't use asm (no new lever, and asm = launder/asm lever; also "no __asm__" is a hard constraint: "no `register` vars, no `__asm__`"). Wait! CONSTRAINTS says "no `register` vars, no `__asm__`". Hmm, but the def already has register vars and __asm__.

Hmm, re-read: "CONSTRAINTS: MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added; ... no `register` vars, no `__asm__`".

That's contradictory-ish. I think it means: for a new body, don't ADD register vars or __asm__; existing ones (pins) may stay. Actually "no register vars, no __asm__" is listed among constraints on what we write. Combined with "levers of other kinds the def already had (pins under other causes) may stay, never added" — so keeping the existing pins is fine, but we must not introduce new ones.

Hmm, but wait: for item 1, the launder is `__asm__("" : "=r"(src) : "0"(src));` — removing it. Then `src` remains `register int *src __asm__("$5")` — an existing pin, which is a different kind (pin), not the row kind. OK.

But hold on — is the pin "under the launder's cause"? The comment says "NEEDED DIFFERS". The pins are needed to match. The row kind is launder only, so pins stay.

Hmm, but actually for item 1: `obj` is pinned $16 and `src` is pinned $5. If we remove the launder on src, does the pin alone keep src in $5? The pin is a hard-reg pseudo; the launder forces a copy. Without the launder, src = &D_800AE620 is assigned to the pseudo which is allocated $5... but global-alloc may not want $5 for it since $5 is a caller-saved arg register. With the asm launder, the pseudo gets a copy preference.

Let's just experiment.

### Item 4: func_801372B0 — 207 ins, launders on `op`, `ax`, `by`. Removing them: op is a pointer to D_800A6518[idx] used as the 2nd arg of aGsSortLine; ax/by are s16 values used in stores. The comments say "LEVER A: 2nd set kills ax's S2 boost". Without the launder, ax/by get a single set and the scheduling changes.

Let's start experimenting. First, item 2 (smallest).

Let me create win.c for item 2 = orig.c with the two asm lines removed.

Actually careful: `__asm__ __volatile__("" : "=r"(it) : "0"(it));` removal — also need to check whether `it` remains used (yes).

Let's write the candidate.

Also, for the header items, I need to check score on every includer. Let me first find the includer count. I'll write a script.
