---
ts: 2026-11-06T12:37:08Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_6GBHAvXINNARSQ00ccOO
---
Interesting: with `arg1` used directly, the compiler still does `andi v0,t3,0x1` — so arg1 is in t3, not a1! That means arg1 was moved to t3 somewhere. Because arg1 is used later (`if (arg1 & 0x8000)` at line 64 and `if (arg1 & 1)` at 71) — so arg1 is copied into a callee-saved-ish register t3 for its later uses.

The launder forces a1v=arg1 in $5 at the top, so the first test uses a1 (in place).

Hmm, so the launder makes the FIRST test happen on the incoming register. Real-C: can't.

Wait — the target's `andi a1,a1,0x1` at 2-3 tests a1. So the target tests arg1 in a1 before copying it to t3. That's the launder's effect: a1v is pinned to $5 and set from arg1 at the top; the first use of a1v happens before any copy.

With `a1v = arg1;` (plain), gcc might still do it... l0 = same 2. Hmm, l0 = `a1v = arg1;` with the pin → still `andi v0,t3`.

Because the copy `a1v = arg1` is a real insn (move a1,a0 or whatever), and gcc instead rematerializes... 

OK so the launder is a register steer with no C equivalent (that's why it's a launder kind).

Hmm. But hold on: the launder row kind is what we must remove. l0 (plain assignment) = 2. So the launder is cracked only if we reach 0.

Let me try other spellings for a1v:
- `a1v = arg1;` where a1v is `register s32 a1v __asm__("$5")` → 2.
- What if we DON'T pin a1v and just use `arg1` in the test... n1 = 2.
- What if we pin arg1? Can't pin a parameter.
- What if a1v is used in more places to force the copy?

Alternatively, maybe the target's `andi a1,a1,0x1` arises because arg1 is ALSO used at lines 64/71 — and the compiler keeps arg1 in a1 until it needs it in t3. In the target, arg1's later uses (line 64 `arg1 & 0x8000`, line 71 `arg1 & 1`) — where's t3? 

Let me dump the target's first insns to understand.

Actually, time check: ~07:30, item 4 at ~15 min. This item is the most promising (2/3/2 residuals). Let me think about what's achievable.

Total lever-free (v0.c) = 13 with 154 ins (the barrier merge costs 2 insns). Since the barriers produce a structural merge (jump2), the count differs.

Priority: the barrier's 12 is the biggest, but the merge loses 2 insns which no real-C move can restore... unless we prevent the cross-jump.

Preventing jump2's merge of the two arms: jump2 merges identical tails. The arms:
```
if (arg1 & 1) {
    b4b = D_8017E918;
    D_801152AA = 0xFFF;
    var_v0_3 = pos + 2;
} else {
    b4b = D_8017E918;
    D_801152AA = -0xFFF;
    var_v0_3 = pos - 2;
}
```
The common tail is `b4b = D_8017E918;` (identical) — jump2 merges the arms up to the differing store.

n4 duplicated `b4b[1] = var_v0_3;` into the arms → still 12. Hmm.

What if the arms are made structurally different, e.g.:
```
if (arg1 & 1) {
    D_801152AA = 0xFFF;
    var_v0_3 = pos + 2;
} else {
    var_v0_3 = pos - 2;
    D_801152AA = -0xFFF;
}
```
Reordering within the else arm — that changes the insn order but the arms still share the `b4b = D_8017E918` prefix.

The merge in mine: the if-arm jumps to 128 (the else's store). So jump2 merged the two `sh v0,0(at)` stores (with different v0 values!). It merged the STORE, not the constant load. That's a cross-jump of the store (the tail `lui at; sh v0,0(at)` is identical in both arms after the li).

So: to break it, make the store's form differ per arm, e.g. in one arm store a variable and in the other a constant? That's not the same C.

What about making the constant's computation differ: `D_801152AA = 0xFFF;` vs `D_801152AA = -0xFFF;`. In the target these are `li v0,4095` and `li v0,-4095` then `sh v0,0(at)`. Identical shape after the li. jump2 cross-jumps them because the `lui at,0x0; sh v0,0(at)` part is identical.

Real-C: hmm, what if I write `D_801152AA = (s16)0xFFF;` and `D_801152AA = -(s16)0xFFF;`? Same insns.

What if the arms store different-width values? no.

Alternatively, put the store AFTER the var_v0_3 computation in one arm and BEFORE in the other (like the target!). Look at the target: if-arm: `li v0,4095` (delay slot) → `lui v1; lw v1` → `lui at; sh v0,0(at)` → `j` → `addiu v0,t4,2` (delay). else-arm: `lui v1; lw v1; li v0,-4095; lui at; sh v0,0(at); addiu v0,t4,-2`.

Hmm, the target's if-arm computes var_v0_3 in the delay slot of the `j`. So the store is before the addiu in the if arm, and before it in the else arm too.

The merge in mine happens because both arms' `lui at; sh v0,0(at)` are identical and jump2 redirects the if-arm's jump to the else's store.

To prevent: make the if-arm's store not mergeable — e.g. if in the if-arm the store uses a different address register or the order differs.

What if in the if-arm I write the store as `D_801152AA = 0xFFF;` but in the else arm write `*(s16 *)&D_801152AA = -0xFFF;`? Same code.

Hmm.

What about reordering the statements in the else arm (e.g. var_v0_3 before the store):
```
} else {
    b4b = D_8017E918;
    var_v0_3 = pos - 2;
    D_801152AA = -0xFFF;
}
```
Then the else arm's addiu comes before the store, so the arms' tails differ in position → jump2 can't merge the store into one place (the if-arm would need the addiu after the store). Actually jump2 could still merge the `lui at; sh` sequences if they're identical and at the end of both arms... In the if-arm the store is last (after addiu? no, before). Hmm.

Let me just try: reorder within the else arm (2 variants) and within the if arm.

Also: maybe put the `b4b = D_8017E918;` OUTSIDE the if (hoist). Then both arms lose the load... but the target has the load in both arms. Actually wait — look at the target: if-arm 120-121 `lui v1; lw v1` and else-arm 126-127 `lui v1; lw v1`. So b4b is loaded in both arms. If I hoist it before the if, we'd get one load — the target has 2, so no.

Hmm, BUT: the C code has `b4b = D_8017E918;` in both arms, which is silly; the original source probably had it once. The target's 2 loads might be because of the barrier preventing... no, a barrier wouldn't duplicate a load.

Let me try the reorder variants (cheap, 4 tries).

Also for the launder (2) and keepalive (3), think more:

launder (2): target `andi a1,a1,0x1`. Mine `andi v0,t3,0x1`. So arg1 is in t3 at that point in mine. That means the compiler copied arg1 to t3 BEFORE the test. Why? Because arg1 is live across calls? No calls. Because arg1 is used later at 64/71 and the copy is hoisted?

If arg1 were used only in the first test, the compiler would test a1 directly. The copy to t3 is hoisted because of register pressure (a1 is call-clobbered, but there are calls? Let me check: the function calls nothing... Actually `(temp_a1 * b8[0]) / var_a3` — a division! That's a call to __div? No, MIPS has no div; gcc 2.7.2 with -O2 might emit a div call (library). Hmm, there are `div` instructions in MIPS but no trap; for C division by a variable, gcc emits a call to `__divdi3`? For s32 it emits `div $zero,...` + `mflo`. 

So arg1 (a1) must survive the div? No, the div is after the test.

The copy to t3: arg1 is used at lines 32, 64, 71. Between them, the div/mod and many stores. a1 is call-clobbered; the div doesn't clobber it. Hmm.

Whatever the cause, the target tests a1 in place at the very top (insn 2), meaning arg1's value was in a1 and used before any copy. In mine the copy to t3 happens first.

Could I force the order by putting the test before anything else? It IS the first statement after the launder.

Idea: what if a1v is used in the FIRST test and then arg1 later (not a1v)? i.e.:
```
a1v = arg1;
if (!(a1v & 1)) {...}
...
if (arg1 & 0x8000) ...
```
With a1v pinned to $5, the copy `a1v = arg1` forces a1 ← a0 (a real move!) unless coalesced. In the target there's no move (the launder's asm with "0"(arg1) makes arg1 and a1v the same register).

So real C needs arg1 and a1v to be the same register: `a1v = arg1;` with the pin — the copy would be coalesced if possible, but since arg1 is used later (t3 copy), it can't.

What if I use a1v for ALL arg1 uses (lines 32, 64, 71)? Then arg1 is used only in the copy, and a1v (pinned $5) takes over. The copy `a1v = arg1` would be a move a1←a0 at the top... The target has no such move? Let me check the target's first insns: `andi a1,a1,0x1` — a1 already holds arg1 (it's the parameter register). So no copy.

With `a1v = arg1;` and a1v pinned, gcc must copy a0→a1 (1 insn) unless it can coalesce. Since arg1 is used later (in t3 copy), it needs a0 preserved... 

Hmm, but wait: what if I don't use the pinned variable at all and just test arg1 (n1 = 2, `andi v0,t3`)? The problem is arg1 gets copied to t3 first. WHY? Let me look at the target's first ~10 insns and mine's to understand.

Let me dump target 0-20 and mine (n1) 0-20.
