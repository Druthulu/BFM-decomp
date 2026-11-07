---
ts: 2026-11-06T05:11:49Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG21
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lKmuMSmy7CyKxdDK9s1N
---
`cse_end_of_basic_block`: `while (p && GET_CODE (p) != CODE_LABEL)`. So the EBB ends at a CODE_LABEL, not a loop note. So the do-while(0) doesn't split cse's EBB (contradicting my reading of C0535 — maybe C0535's split came from a CODE_LABEL the do-while caused via loop.c, or from `loop.c` running before cse2).

Hmm wait — maybe the do-while causes loop.c to run and *loop.c* can insert labels, but cse1 runs before loop.c.

Anyway. Let me consider: what if the reload is NOT from cse but from `flow`/`combine`? The candidate reuses the loaded v1 value for both comparisons. If cse1 did it, the .cse dump would show. Let me check the u2 cse dump: is the second load present in the .cse dump?

Let me look at the dump files: v1.i.cse etc. Let me grep the u2 dump (need to run hdump for u2). Actually, let me check the .combine/.cse dumps for the third block.

Time is ticking (item 2 started 21:53, now ~22:15 → 22 min). I have a score-0 win.c on all 141 includers. The only concern is whether the cast counts as a launder. Let me try to find an alternative for a few minutes, and if not, keep u3 but document the concern in notes.md. Actually, the expert will judge; but the brief is binding: identity address spellings do NOT count as a crack. If I'm unsure, I should find an alternative or report honestly.

Hmm, wait. Let me reconsider: is `*(s16 *)&D_80078EA6` really an *identity* spelling? The declared type is `u16`; the cast reads it as `s16`. The *comparison* `(s16)D_80078EA6 >= 0x81` already treats it as s16. So the load itself is the same HImode access with a different signedness. The generated `lh` is identical. The only effect is the alias set.

Honestly, this is a type-pun alias trick — a compiler-internal alias-set difference, not a real C semantic change. I'd call it a launder.

Let me look for a cleaner alternative using a REAL aliasing store. What if we make the store to EA4 happen through `base` (the D_80078E78 pointer) at offset 0x2C? The reloc would change. No.

Hmm, what about the *first* load being through a different alias set so cse doesn't record it? E.g., change the FIRST comparison to a cast: `*(u16 *)&D_80078EA6 < 0x80`? That's the same type as declared (u16) → same alias set → no change. `*(s16 *)&D_80078EA6 < 0x80` (s16) → the first load gets the s16 alias set; the second `(s16)D_80078EA6` gets the u16 alias set → different → reload! That's the same trick on the other load.

What if the difference is in the *mode* rather than the alias set? E.g., the second comparison reads a `u8`? `*(u8 *)&D_80078EA6` would generate `lbu` — mismatch.

Hmm.

OK, alternative idea: **make the second comparison depend on the stored value** so the reload is forced by a true dependency? No, the comparison is on EA6.

Another idea: **split the EBB with a CODE_LABEL**. cse's EBB ends at a CODE_LABEL. A real C construct that creates a CODE_LABEL between the store and the second load, without emitting code: a `goto` to a label! If we write:

```
D_80078EA4 += a1;
goto L;
L:
if ((s16)D_80078EA6 >= 0x81) ...
```

GCC's jump optimization removes the redundant `goto L; L:`. But maybe it keeps the label if it's referenced... Hmm, `delete_unreferenced_labels` runs in jump_optimize. The goto→fallthrough is optimized in `jump_optimize_1` (the `simplejump_p` redirect to the next insn). Then the label is unreferenced → deleted.

What if the label is referenced by a *branch that survives*? E.g., the enclosing `if` branch jumps to it? Consider:

```
if ((s16)D_80078EA6 < 0x80) {
    D_80078EA4 += a1;
    goto L;
}
L:
if ((s16)D_80078EA6 >= 0x81) ...
```
That changes the CFG (the join target). Hmm.

What about using a `switch`? no.

OK, let me consider another angle entirely: maybe the reload can be forced by *volatile-free* means: the store's value depends on the loaded value? E.g., if the second comparison is on `D_80078EA6` and the store is `D_80078EA4 += a1`, no.

Hmm, hold on — what about making the store and load *the same symbol*? The target's store is to D_80078EA4 (reloc) and the load from D_80078EA6 (reloc). Fixed.

What if we make the store through `D_80078EA6`? No.

Alright, let me look at this from the "what would the expert accept" view. The brief's constraint list explicitly says identity address spellings don't count. The cast is borderline. But the moves.md line 55 shows `(u16 *)a0` pointer casts used in a MATCH — that's a pointer *reuse* move, not an identity address spelling (the pointer a0 is a parameter, reused for a different access).

Hmm, `*(s16 *)&D_80078EA6` — the `&D_80078EA6` is an address-of an existing object; that's the "identity address spelling".

I think I should try to find a real alternative. Let me think about what the memory clobber does that a real store could do:

The asm memory clobber marks ALL memory as clobbered. cse then invalidates all memory equivalences. A real store to ANY global would invalidate equivalences for that alias set. Since in gcc 2.7.2 without strict aliasing, all globals share an alias set? If so, the store to D_80078EA4 WOULD invalidate the EA6 load equivalence... but it doesn't (the compiler reuses the load). So they must be in different alias sets OR cse handles them as distinct symbols.

Actually, `memrefs_conflict_p` for two MEMs with symbol_ref addresses: it compares the symbols. Different symbols → no conflict, regardless of alias sets. So the alias-set theory may be wrong; the cast difference might be something else.

Let me actually verify WHY the cast forces the reload. Maybe it's not the alias set but the *mode/type* of the expression causing a different RTL (e.g., a sign-extend insn?). The insn count matched the target (114), so no extra insns. Hmm.

Let me look at the t1/u3 disassembly to see the difference from u2. Both 114 vs 111: u3 has the reload. Let me diff u2 and u3 disassemblies to confirm the only difference is the reload (and register v1/v0).

Actually, let me try a *different* way to force the reload: use a `s16` local variable loaded through a cast... same.

Hmm, let me try the dead-store idea empirically — cheap:

w1: `D_80078EA6 = D_80078EA6;` between the store and the inner if.
w2: `D_80078EA6 = (u16)D_80078EA6;`
w3: a local `s16 t; t = D_80078EA6;` before the store and `if (t >= 0x81)` — no, reuse.
w4: `if (D_80078EA6 + 0 >= 0x81)`.

Let me test w1/w2 and see if they force the reload and what insns they add.

Actually, a cleverer idea: make the *store* kill the equivalence by storing through a `u8 *` view of EA4 with a 4-byte width? No, the store must be `sw`.

What if the store is `*(s32 *)(void *)&D_80078EA4 += a1`? The cast changes the store's alias set (if any), potentially making it conflict with the EA6 load → reload. But it's an identity cast again.

Hmm.

Let me try a completely different structure for block 3: what if we write the inner check as an `else` of the outer? No.

OK, let me try the dead-store variants and see.

Actually, wait! Here's a cleaner idea: **make the second load a different *mode* expression that still emits `lh`**: `if ((s16)(D_80078EA6 - 0) >= 0x81)` no. What about `if ((s16)(D_80078EA6 & 0xFFFF) >= 0x81)`? fold.

Hmm.

What about **reading EA6 as an `s16` through the `D_80078EA4` symbol's alias**... no.

Let me just test w1/w2/w4 quickly and see if any forces the reload without extra insns.
