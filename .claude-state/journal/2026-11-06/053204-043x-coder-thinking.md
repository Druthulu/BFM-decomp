---
ts: 2026-11-06T12:32:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_BR6LxBaxeo8LdadwICA8
---
score 64, 256 vs 261. Big changes: the pin removal changed `ret` from $2 to $3? Actually mine has `li s0,25` etc. — ret got $s0! And target `li v0,25`. So ret (the return value) needs $2 but got $s0.

Wait, that's odd: ret is returned, so it should be v0. But ret is set in the arms and jumps to STORE where it's stored and returned. Because it's a global-ish live across calls, global-alloc gave it s0 (callee-saved) since it's live across calls (it's stored after... no, it's set at the end of each arm then STORE immediately).

Hmm, but in arms it's set right before goto STORE, so it's not live across calls... except the last `ret = ... + 1` at line 166.

Actually the target's arms: `li v0,22` — ret in v0. With the pin, gcc is forced to $2. Without, global-alloc chose $s0. Why? Perhaps because ret's live range spans the whole function? No... Let me look: at line 55 `return ret;` after the first call — ret is uninitialized there, so it's a live-in pseudo with a use at line 55 and line 60, and definitions in the arms and at 166. The pseudo has many definitions (one per arm) and uses; global-alloc may prefer a callee-saved reg because... the arm definitions are followed by a use in STORE (unk2 = ret) and a return. Between the def and use there's no call. Hmm.

But global.c's allocno priority/density: ret has many refs spread across the whole function → gets a callee-saved reg (s0). To get $2 (v0), gcc must consider it "return value"-ish.

Since the kind is "pin", the lever-free route: make the return value natural, i.e. `return <expr>` directly instead of the ret variable + goto. But the code has a common STORE label: `unk2 = ret; return ret;`. If we restructure to `return ret;` where the arms do `unk2 = 22; return 22;`? That changes code.

Hmm. Alternatively, note this is the "expand-void-return" family wall (moves.md 302-311): "keepalive,pin | func_80182420 | WALL expand-void-return — void def drops rv; keepalive keeps it live but global-alloc gives $3 not $2; pin $2 needs a real return". Here we have a real return but the value is still not v0.

Approach: maybe make `ret` the return expression directly at the STORE label: `return ret;` is already there. gcc's `current_function_return_rtx` is v0; when returning a pseudo, expand sets v0 = pseudo at the return. So the final `move v0,s0` appears (mine has `move v0,s0` at 248). The target has ret in v0 throughout, so no moves at all — and `li v0,22` in each arm.

For gcc to give the pseudo v0, it must be the return value pseudo... In gcc 2.7.2, the value returned by `return x` is copied into v0 at the return, so the pseudo never gets v0 unless... the pin forced it.

Alternative lever-free trick: use the return statement's value directly in each arm — i.e., avoid the shared `ret` variable by returning directly. But then the STORE (unk2 = ret) needs the value too. We could restructure:

```
STORE:
    ((Unkstruct *)param_1)->unk2 = ret;
    return ret;
```
If instead each arm does `((...)->unk2 = 22; return 22;` — the store and return both use the constant. But then the code would be duplicated per arm (each arm would have `li v0,22; sh v0,2(s1)`...). The target has a single `sh v0,2(s1)` at the end (common STORE). So the arms jump to the store with v0 = value. So the target's C is exactly `ret = 22; goto STORE;` with ret in v0 — meaning the C had ret as a variable, and gcc put it in v0 because of the pin.

Hmm, but could gcc naturally put ret in v0? The pseudo ret's live range: defs in arms, use at STORE. In global-alloc, allocno for a pseudo that's a return value gets preference? In gcc 2.7.2, `global.c` has special handling: allocnos for pseudos that are function return values (i.e., live at the return) get REG_V0? Hmm, there's `global_alloc` code: "If the pseudo is used as the return value..." Not that I recall.

Wait — maybe the answer: assign to `ret` and return it, but ALSO make gcc's `current_function_return_rtx` be the same pseudo. In gcc 2.7.2, `expand_return` for a simple `return x` does `emit_move_insn(return_rtx, x)` — so a copy. Unless the function's return value is the pseudo because of the tail... no.

Alternatively: use the s32 return value expression at the end: `ret = ...; goto STORE` → what if the arms use `return` directly with the store duplicated? no.

Let me reconsider: maybe ret CAN get v0 naturally with a different structure. Consider what makes a pseudo get a call-clobbered reg like v0: it must not be live across any call. In the arms, ret is defined after the calls and used immediately at STORE — not live across a call. But the *whole* pseudo (all defs/uses) is one allocno; the live ranges are per-region? In gcc 2.7.2 global-alloc, an allocno's conflicts come from the union over the whole function; the reg must be free (not conflicting) at every point in each live range. If any live range crosses a call, it needs a saved reg. Does ret's live range cross a call? The first `return ret;` at line 55 — that's a use of an uninitialized ret, at a point right after func_8012CAE4 call... it's a use, not crossing. Hmm, but the *pseudo* is "live" from function entry (since it's used at line 55 before any def? an uninitialized use makes it live-in at entry) to the return at line 170. So ret is live across many calls (its live range from entry to the end!). Because of the `return ret` at line 55/60 where ret is uninitialized.

That's why: the early `return ret;` with uninitialized ret makes the pseudo live from entry. In the target's C, those early returns probably returned something else, e.g. `return 0;`? No — target's code at that point... Let's look at the target's first region: `if (D_801ED4E4[...] == 0) { func_8012CAE4(param_1); return ret; }` — the target's return there returns v0 as it happens to be (whatever the call left). Hmm.

What does the target's asm look like at the beginning? If ret is v0 and the early return is `return ret` (uninitialized), the target just returns with v0 as-is. But gcc might treat the pseudo's value as whatever.

The cleanest fix: make those two early returns return a value that doesn't use ret, e.g. `return 0;`? That would emit `move v0,zero` or `li v0,0` — an extra insn not in target. Unless the target has something. Let me look at the target's asm near the start.

Let me dump target asm for this function.
