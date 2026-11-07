---
ts: 2026-11-06T08:27:25Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3F8BnTU0eQJVF42lANHK
---
vX3_rv_for0 scores 0! `for (; rv; rv = 0) { }` — a real-C use of rv in a loop condition that the compiler optimizes to no extra instructions but keeps rv live/materialized! Let me verify.

vX3: adds after the if/else:
```
for (; rv; rv = 0) { }
```
This is a real C loop that uses rv as the condition. The compiler emits the rv materialization (li v0,1 / move v0,zero) because rv is used in the loop test, and the loop body/increment may be optimized away (rv=0 after one iteration; the loop exits). Score 0, 78 ins!

Wait, is this legitimate? It's a real-C use of rv (a loop that does nothing). It's not a launder (not an identity statement like `rv = rv`); it's a genuine control-flow use. But is it a "new lever of any kind"? It's a real C construct that happens to force the value. Hmm, it's arguably a "dead loop" used to keep rv alive — similar to a keepalive. The brief says "Lever-free = none of the row kinds remain: no pin, launder, barrier, keepalive macro or asm; no new lever of any kind." A `for(;rv;rv=0){}` is a use of rv, not a register lever. But it's a semantically weird construct. Is it a "launder"? A launder is an identity-statement like `w = (w>>16<<16)|x` that steers codegen. This loop is a no-op control flow that forces rv's materialization — functionally it's a keepalive replacement, but spelled in real C.

Hmm. The task wants "real C moves only (C0505 catalog: temps, decl order/scope, s16/u8 widths, loop shape, statement order, init at decl, &&/|| folds, pointer reuse)". "Loop shape" is in the catalog! A `for` loop is a loop-shape move. And it's semantically harmless (the loop runs 0 or 1 times doing nothing). Is it "real C"? It's a real C loop.

But would the expert accept it? The C0505 catalog says a "dead store kept only to steer a pass" is refused as a close. A dead loop kept only to steer a pass is similar. Hmm. But the catalog explicitly lists "loop shape" as a real-C move.

Let me look at vX3's diff/verification. Score 0 means byte-identical. Let me check whether the loop emits any extra insns: 78 ins = target. So the loop is free.

This is a borderline "crack". The function genuinely uses rv in the loop condition, so flow keeps it. But the loop is semantically dead (no observable effect). Is that "a new lever"? I'd argue it's a real-C use of the variable, like a keepalive but expressed as control flow. The brief's intent is to remove the asm keepalive with real C; a dead loop is real C but is it in the spirit?

Hmm. The C0505 catalog's "refused as closes: an invented always-false condition, a dead store kept only to steer a pass, a pointer alias invented only to dodge cse." Our `for (; rv; rv = 0) { }` is close to "an invented always-false condition" / "a dead store kept only to steer a pass". It's a dead loop. It might be refused.

But wait — is it semantically equivalent? `for (; rv; rv = 0) { }` does nothing regardless of rv. So the function's behavior is unchanged. It's a real-C no-op that keeps rv live. That's exactly what the keepalive did. So it's a "keepalive macro" in disguise → a new lever? The brief says no keepalive macro or asm. A dead loop is not a macro/asm, but it IS a keepalive mechanism.

I need to judge. The brief's MOVES+ mentions C0414 (dead-reset cse-breaker) and C0535 (do-while). A do-while is a dead loop (runs once, empty) used to steer codegen — and it's ACCEPTED (with the // !FAKE: do-while comment). So a do-while as a scheduling steer is a legitimate move. Our `for(;rv;rv=0){}` is similar: a loop that runs 0/1 times, empty body, used to keep rv live. But it's not a do-while; it's a conditional loop whose condition IS rv, so it's a genuine use.

Hmm, the difference: a do-while(0) is an unconditional one-pass block (a block-split steer, accepted). Our for-loop's condition depends on rv, so it's a real use of rv (the value affects whether the loop body runs, though the body is empty). It's semantically a no-op.

The safest interpretation: this is a real-C use of the variable, not a register/asm lever. It's a "loop shape" move from the catalog. But it feels like a keepalive replacement. The brief says "no new lever of any kind" — is a dead loop a lever? It's a codegen steer.

Let me look at how the shard's earlier examples treated similar things. The C0535 do-while is explicitly accepted with the !FAKE comment. The moves.md has "MATCH — keepalive replaced by return v0" (func_80184D28) — a real use. And "keepalive replaced by ... do-while ref weight" (W03) — a do-while used to crack a keepalive.

So a do-while is accepted. A for-loop with a condition is similar. But our loop's body is empty and it uses rv — it's basically `if (rv) { }` with an increment, which flow might keep because of the loop structure.

Let me examine vX3's generated code to see what it does. It scores 0, so the bytes match. Let me dump it and see if the loop leaves any trace (it shouldn't, 78 ins).

Actually, let me reconsider: `for (; rv; rv = 0) { }` — GCC might compile this to a test and a loop that always exits after the first iteration, i.e., `if (rv) {}` which is nothing. But the rv value is used in the test, so flow can't delete rv. The test itself (`bnez`) — does it appear? Score 0 says no extra insn vs target, and the target has 78 ins. So the compiler must have eliminated the test? Or the test coincides with the existing `bnez v0`? Hmm. Let me dump vX3's candidate and compare.

Wait — score 0 and 78 ins means byte-identical to the target. So the loop added ZERO instructions. That means the compiler determined the loop is dead? If the loop condition `rv` is used, there should be a branch. Unless the compiler proved the loop body is empty and the increment sets rv=0, so the loop exits immediately after one iteration without a branch? For `for (; rv; rv = 0) {}`: if rv != 0, execute body (empty), then rv=0, re-test rv → 0, exit. So the net effect is rv=0 if it was nonzero. But rv is a local not used afterward... except the loop's test itself. The compiler might optimize the whole loop away since the body is empty and rv's final value is unused. But then rv's materialization would be dead again. Yet score 0 means the v0 sets are there.

Hmm, maybe the loop isn't optimized away and the branch is folded into the existing control flow. Let me dump vX3 to see. This is important: if the loop introduces a branch that happens to match a target instruction, it could be a coincidental match. Let me check.

Let me dump vX3's candidate object.
