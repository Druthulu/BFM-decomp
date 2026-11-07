---
ts: 2026-11-06T12:03:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_u5Yhzx5cWz5WUv39F9Ax
---
Still 2. The store sink is unfixable without the barrier. This matches the sibling WALL func_801810E4 (sched-store-sink, best 2).

So item 4 = WALL, best 2, wall=sched-store-sink.

But let me make sure I've spent 20 min. It's 05:03, item 4 started ~04:56. Only 7 min. Let me continue a bit more with genuine attempts to reach ~05:16.

Actually, let me reconsider: the score 2 is very close. Maybe there's a clever way. Let me think about the scheduler once more.

The store `sw v0,16(s0)` and `li a0,2432`. The target has sw then li. Mine has li then sw. 

What if the store used a register that the li a0 conflicts with? The li writes a0. If the store's address base were a0 (not s0)... but it's s0.

What if the store's VALUE v is in a register that the li needs? The li writes a0; v is in v0. No conflict.

What if I make the store's value depend on a0? E.g., `CAST_WIDTH(...,0x10) = v + (a0 - a0);`? identity, folds.

Hmm.

What if I reorder the SOURCE so the final call's li is generated BEFORE the store? Then sched would have li then sw — matching mine (wrong). So the opposite.

Wait, the target has sw then li. The source order is: store (in middle block), then tail stores, then call (li a0). So source order is sw ... li. The scheduler in the target keeps sw before li (barrier). In mine, sched moves li before sw. 

To prevent sched from moving li up, I need a dependence or barrier between them. The tail stores (unk14 etc.) are between the store and the call in source. But sched moved li above the store AND the tail stores? Let me check mine's order: li a0 at 29, sw 0x10 at 30, lui v0,0x20 at 31, sw unk14 at 32... So the li a0 moved above the store 0x10 but the tail stores are still after. So the li a0 moved up just past the store 0x10. Interesting — only one slot.

Hmm, so the li a0 is scheduled at position 29, right after the v computation (lui 0xfffd at 28), before the store 0x10. In the target, the store 0x10 is at 29 and li at 30.

sched1/sched2 priorities. The li a0 (needed by the jal at 37) has some priority. The store 0x10 (v0 value, ready at 28) has another.

If I could make the store 0x10 "more ready" or higher priority... The store's value v0 is ready at 28 (lui 0xfffd). The store can issue at 29. The li a0 is also ready. sched picks one first. 

Maybe the scheduler's tie-break depends on the RTL order. In the target, the store's RTL comes before the li's RTL (source order), so sched might keep it. In mine, same source order (store before call). So why does sched move li up?

Hmm, maybe it's not sched but the register allocation / reload that inserted the li earlier. Or sched2.

Let me try a completely different structure for the final call: what if I call func_8002D4C8 via a function pointer or cast? No.

What if I make the final call's first arg not a constant but the same 0x980 from a struct field? No.

Let me try: `func_8002D4C8((s32)0x980, 0);` — same.

What if I split the call: `func_8002D4C8(0x980, 0);` → the li a0 is the arg. If the call were `func_8002D4C8(v & 0 | 0x980, 0)`? identity, folds.

Hmm.

Let me accept the wall. But let me try ONE more creative idea: use the "do-while splits cse1 EBB" (C0535) on the store AND ensure the store is in a different EBB than the li. A do-while around the store creates a separate EBB. Tested (v_s8_store_dw = 4, v_store_tail_dw = 2). Hmm, v_store_tail_dw = 2 (same).

Let me try a do-while around the TAIL stores (not the store 0x10), so the tail is a separate EBB and the li can't hoist above the store 0x10? v_tail_dw was tested earlier? I did v_tail_dw in gen5 (score 2). No change.

OK, WALL. Let me finalize.

Actually, let me reconsider the score: 2 with `s8 two` + `do{two=2;}while(0)`. That's a great result but not 0. The wall is the store sink. Best = 2.

Wait — is the `s8 two` + `do-while` body "lever-free"? Yes: no pin/barrier/asm. s8 is a width choice (allowed, C0505 catalog: s16/u8 widths). do-while is allowed (C0535). So the best lever-free body = v_s8_dw_two, score 2.

Let me finalize item 4:
- result = WALL
- best = 2
- tries: let me count. orig(1)+nopin(1)+gen(5)+gen2(4)+gen3(6)+gen4(4)+gen5(3)+gen6(2)+gen7(2)+gen8(3)+gen9(3) = 1+1+5+4+6+4+3+2+2+3+3 = 34. Plus some. Let me say 34.
- wall = sched-store-sink
- evidence: "sched sinks the 0x10 store below the final call's li a0; s8 two + do-while fixed the v1/v0 swap, only a memory barrier holds the store. Best 2/44 ins"

Let me trim to ≤140: "s8 two + do-while fixed the v1/v0 reg swap; sched still sinks the 0x10 store below the final call's li a0 (only a barrier holds it). Best 2/44" ~135. Good.

Let me write the notes, results, moves. But I need to spend until ~05:16 for 20 min. It's 05:03. Let me do a few more genuine attempts (~10 more min) before finalizing.

Let me try harder on the store sink. Ideas:
1. Make the store 0x10 the LAST thing before the final call, and make the tail stores depend on it? No.
2. Insert a real dependence: make the final call's second arg (currently 0) depend on v? `func_8002D4C8(0x980, v & 0)` — folds to 0. But what if `v & 0` doesn't fold because v is opaque? v is computed; `v & 0` = 0 folds.
   What about `func_8002D4C8(0x980, (v ^ v))`? folds.
3. Make the final call's FIRST arg depend on v: `func_8002D4C8(0x980, 0)` → the first arg 0x980. If I make it `0x980 + (v & 0)`, folds.
4. Use a `volatile` on the store? Lever.

Hmm. What if I make the store's ADDRESS depend on v? `CAST_WIDTH(s32, (u8*)a0 + (v & 0), 0x10) = v`? folds.

What if I use a real dependence that doesn't fold: e.g., `func_8002D4C8(0x980, v != 0)` — that changes the arg from 0 to (v!=0), wrong semantics. No.

Hmm. The target's final call is func_8002D4C8(0x980, 0). If I change the second arg, semantics differ.

What if the store and the li have a memory dependence? The store writes a0+0x10 (memory); the li writes a0 (register). No memory dependence.

What if I make the final call use a0 as an argument that reads the struct? No.

OK. Let me try the "init at decl" of the tail (moves.md 241/243) — declaring a local array with init at decl near the tail might change sched2. Let me try:
```
    s32 tail[1] = {0x200000};
    ...
```
No, that changes the stores.

Let me try: declare a dead local `s32 zz = 0;` right before the store, hoping the sched orders the li differently. Actually that adds an insn (li zz,0) which might be deleted.

Hmm.

Let me try a few "dead" init-at-decl variants:
- v_dead_init: `s32 zz = 0;` at the middle block, unused. gcc deletes it. But its birth might affect sched.
- v_tail_init: `s32 t14 = 0x200000;` then `unk14 = t14;` etc.

Let me test a batch. These are real-C moves (init at decl).

Actually, let me look at the func_801810E4 win/notes to see if there's anything I can learn (it's the same wall). Let me find it.

Let me find the shard dir for func_801810E4.
