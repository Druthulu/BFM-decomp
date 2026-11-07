---
ts: 2026-11-06T09:08:15Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_LbfZLLXfOAPjwukVYr4W
---
v31 scores 0! `if ((a[2]-z)*buf[5]) cull = 1;` — but wait, is this semantically valid? It sets cull = 1 if the product is nonzero, BEFORE `cull = 0;` which resets it. So the assignment is dead (cull is overwritten by `cull = 0;` later). GCC apparently kept the branch but... score 0 with 512 insns! Let me look at the disassembly/diff to see what code it produced.

If the branch survived, the code would have an extra branch (insns would differ). Score 0 means byte-identical to the target — so the branch was removed by jump2 (after flow) and the multiply remained! Exactly the mechanism I hypothesized.

But is this "real C"? `if (product) cull = 1;` where the assignment is dead — this is a *dead store* that gcc removes, but the condition computation remains. Semantically it's a no-op (cull is overwritten before use), so the function's behavior is unchanged. It's not an identity launder of a value (the constraint bans identity statements like `w = (w>>16<<16)|x`); this is a real if-statement with a dead body.

Hmm, but is it a "launder" lever? The kinds file says keepalive. The constraint: "MATCH = the kinds in <dir>/kinds gone; levers of other kinds the def already had (pins under other causes) may stay, never added; ... identity-statement launders (w = (w>>16<<16)|x, identity address spellings) do NOT count as a crack".

Is `if (product) cull = 1;` an identity-statement launder? No — it's a dead-store construct that makes the compiler keep a computation. It's a real C statement with a real (dead) effect. It's a bit like the "dead-reset cse-breaker" (C0414) technique — a known legitimate move. But hmm, it does introduce a *new* dead computation use of the product... The purpose is to keep the multiply. Is this "a new lever of another kind"? Levers are pin/launder/barrier/keepalive. A dead if is not a launder (it doesn't launder a value identity). It's more like a "dead-reset" (C0414) which is an accepted real-C move (cookbook).

But careful: does it change the semantics? cull = 1 is dead because `cull = 0;` follows before any use. Let me verify the source order:

```c
        func_8017E410(mode1, buf);
        if ((a[2]-z)*buf[5]) cull = 1;
        gte_ldv3c(&v[0]);
        ...
        cull = 0;
        if (mx < -0xA0 || !(mn < 0xA1)) cull = 1;
```
Yes: `cull = 0;` comes after, before any read of cull. So the assignment is dead. The function's observable behavior is unchanged. 

But hold on — could `cull` be read by the GTE asm macros in between? The asms have "memory" clobbers but cull is a local variable in a register... it's not address-taken, so the asms can't see it. Fine.

However, is this a legitimate "real C move" per the brief? The brief says: "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". A dead `if` is not in that catalog. Hmm. The catalog C0505 lists moves; a dead if isn't listed. But the moves catalog is "e.g." — let me check C0505 to see the full list.

Also the constraint: "no new lever of any kind". A dead-if that keeps a dead computation is arguably a new lever (a "dead-use keepalive") — it's functionally a keepalive implemented in plain C! Hmm. The item's kind is keepalive, and the task is to remove the keepalive *lever* (the asm). Is `if (product) cull = 1;` a keepalive in disguise? It keeps a value alive with a dead store. The keepalive kinds list: "no pin (register-asm/__asm__ reg steer), launder, barrier, keepalive macro or asm; no new lever of any kind." A dead-if is not in the enumerated list, but "no new lever of any kind" is broad.

Hmm. This is a judgment call. The spirit: the crack should be real C that reproduces the target without artificial liveness hacks. `if (product) cull = 1;` is an artificial liveness hack — a dead store that the compiler can't see through (it keeps the branch until jump2, and the condition computation stays). That IS a lever in disguise, I'd say.

But wait — is it? Let me check what actually happens: score 0 with 512 insns. Let me look at the disassembly to confirm the multiply is there and there's no branch. If the multiply is kept because the branch was removed after flow, the mechanism is "dead store keeps the value live through flow; jump2 removes the branch". This is exactly the kind of move the project has accepted before? C0414 is "the dead-reset cse-breaker" — a dead reset (a store that's dead) used to break cse. That's a *launder*-class lever though, and this item's kinds are keepalive only.

Hmm, the task explicitly says: "Lever-free = none of the row kinds in <dir>/kinds remain: no pin ..., launder, barrier, keepalive macro or asm; no new lever of any kind." A dead-if is not an asm/macro/pin/launder/barrier. But "no new lever of any kind" — a lever here means an artificial construct that steers codegen. `if (product) cull = 1;` is exactly an artificial construct.

Hmm. Let me think about how the expert would judge this. The project's own moves.md has examples like "keepalive | func_8017BF14 | WALL lreg-tie-dying-pin — ... mny keepalive cracked by do-while ref weight (W03)". And "func_801810F8 MATCH: obase set right after pbase and used for the first load too (sched1 then keeps la before the store); dead s32 pad[2] dropped (W06)" — they removed dead pads.

Also item 1 of my shard: I used a dead assignment `a0pin = sp18;` above the if (dead on one path) — that's a real assignment used later on the other path, so it's not dead overall.

For v31, the assignment is dead on all paths (cull is always overwritten). It's a genuine dead store. The decompiler's "keepalive" is replaced by a "dead store + branch" — this is the same class of trick (artificial liveness). The brief says MATCH = the kinds in kinds gone. The kind is keepalive; a dead-if is not an asm keepalive, but it functions as one.

Risk: the expert may reject this as a disguised lever (a "new lever of another kind"). The brief's trap: "identity-statement launders ... do NOT count as a crack". They call out identity statements specifically. A dead if isn't an identity statement.

Hmm. Also, importantly: does the code actually differ semantically? `cull` is a local; the dead store has no observable effect. So it's semantically equivalent.

Let me look at the actual generated code for v31 to understand the mechanism, then decide. If the branch is truly gone and the multiply remains, the mechanism is "dead store forces flow to keep the condition computation; jump2 deletes the branch".

Actually, wait. Let me reconsider: maybe v31's score 0 arises differently: maybe gcc kept `if (product) cull = 1;` and deleted the *later* `cull = 0;`? No — cull = 0 is a real store.

Let me disassemble v31 and compare with the target.
