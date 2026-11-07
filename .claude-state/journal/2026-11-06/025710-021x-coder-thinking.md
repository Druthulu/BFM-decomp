---
ts: 2026-11-06T09:57:10Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG26x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_y6m02E7PFjFrWFOyoBch
---
So `volatile` casts and declarations are class C levers. `register T x;` is class D lever. So no volatile, no register.

The row kinds are pin, keepalive. But "no new lever of any kind" means I can't add volatile/register either.

So how do we keep rv live in a void function? The only real-C construct: return it. But that changes the definition's return type.

Wait — maybe the function's return type can stay void while a *caller* uses the value? No, callers are fixed.

Hmm, what about `rv` being a *parameter*? No.

Let me reconsider: is the value in v0 actually necessary? Look at target: `li v0,-1` at 4400 is in the delay slot of `j 4424`. The branches at 43f0-43f8. Without the v0 values, the control flow might still match if we write the code so the branches are the same and v0 gets set by... no.

Actually — key insight! Look at the target: the branches at 43ec/43f0: `slt v0,a0,v1; beqz v0,43fc; slt v0,v1,a1; bnez v0,4404; subu a0,v1,a0`. The `slt` results land in v0 as a byproduct. The final `li v0,-1` and `sll v0,...` are the actual values. So without them, 15 ins differ.

Hmm, maybe the original source computes the value and the "return" is via a function pointer? no.

Let me look at how other coders cracked similar void+pin+keepalive items. moves.md line 28: `keepalive | func_80184D28 | MATCH — keepalive replaced by return v0; (s32 fn returned nothing; flow kept v0 sets only via asm use)`. So for that one the fn was declared s32 and the original "returned nothing" (void body); they added `return v0;`. That's the reverse: changing void→s32 return type? "s32 fn returned nothing" means the fn was already s32 and body had no return; the keepalive was replaced by `return v0;`. So no signature change there.

For our items, the definition is void. Changing to s32 conflicts with the callers' declarations. But wait — do the callers' declarations conflict at file scope? In the same TU, yes: `extern void func_8017F1F0(s32, s32);` after `s32 func_8017F1F0(s32, s32) {...}` → "conflicting types". GCC 2.7.2 might just warn. And the build flags might not have -Werror. Let me test it — cheap. But it changes the signature, which the brief forbids. Still, worth knowing.

Alternatively — maybe there's a different real-C trick: make the function's body a **tail call**? no.

What if the value is assigned to a variable that is the *return value of an enclosing construct*... no.

What about making `rv` a local struct/union member and the function returns... no.

Hmm, wait. Another thought: `void` function with an empty `return;` at the end — no.

What about the value being needed because the function is called via a function pointer whose type returns s32? Callers stay as they are; no.

OK here's another angle: maybe the target body can be reproduced by making the *branches themselves* set v0 as needed and the final `li v0,31` etc. by real code that has a side effect. For instance, if the branches store into `rv` and then the function does something with rv that is not dead: e.g., `D_801EEAEC[0] = rv`? That adds a store — target has no store.

No way around: the value must escape the function. The only escape without a call/store is the return value.

So: the item likely requires changing the return type to s32, which is a signature change forbidden. Unless... the decomp convention treats the return-type of the definition as part of the "body"? Hmm, "bare definition" is the body file — a bare definition includes the function's first line? The brief says "write a lever-free body of `func` ... (bare definition)" and POINTERS mention `--body` (FILE holds the function's definition only). So the body file includes the signature line. But "no signature or decl change outside the body (callers stay as they are)" — the signature line IS in the body file. Hmm, "outside the body" might mean outside the braces. The phrase "no signature or decl change outside the body" = don't change signatures or declarations outside the body; i.e., only edit inside the body. So changing void→s32 is forbidden.

Hold on. Let me reconsider whether the target actually requires the v0 sets. Score 15 with COUNT; maybe there's a different C structure where v0 is set as a side effect of the same slt comparisons? No, the values are -1, d*2, 31.

Hmm, what if instead of `rv`, the function does `if (cond) return;`-style early exits... a void function's `return;` at the end jumps to epilogue; doesn't set v0.

Wait wait. What about this: the target's `jr ra` with v0 set could be produced by a void function that *falls through* to a `return;`? No, v0 values are computed deliberately.

Let me look at the actual original game code convention: In many decomp projects, these functions originally returned s32 and callers ignored it. The decomp author declared them void to match the reconstructed callers, then pinned $2 to fake the return. The "real" crack might require declaring the definition `s32` — which in a single TU with callers declared void would conflict. But maybe the callers' `extern void` declarations could be... they're outside the body, fixed.

Hmm, but hold on: in C, if the definition returns s32 and the call site has an `extern void` declaration in scope, GCC 2.7.2: "conflicting types for `func_8017F1F0`" — is that an error or warning? Let's test. If it's just a warning, --try compiles fine and the object would match! But the bank judges the whole object; the TU would contain the warning but object bytes fine.

But the constraint explicitly forbids signature changes. However, maybe the expert intends "don't change the signature" to mean the parameter list/ABI, and the return type... no, that's still a signature.

Let me re-read the CHANGE line: "write a lever-free body of `func` in G26x/<dir>/win.c (bare definition) that scores 0." And CONSTRAINTS: "no signature or decl change outside the body (callers stay as they are)". 

Hmm. I think the intended reading: you may not alter the declaration/signature (the line with the name and params) — the body means the `{...}`. So the return type is off-limits.

Then these items might be WALLs. But four items all with the same pattern (keepalive,pin) — the shard is "singleton crack shard G26x". Maybe the expected answer is WALL for most, MATCH for some where a real-C trick exists.

Let me check the target more carefully: maybe the value doesn't need to be live at exit if the *epilogue* is reached from a jump that GCC emits anyway. No — flow deletes dead sets regardless.

Wait, actually — what if the assignments are not dead because rv is used in a *condition* later? E.g., a loop: `while (rv)`? No.

Hmm, let me look at item 4 (93 ins) — bigger, maybe there rv is used in a real computation.

Actually, let me step back and check git history: maybe the function was previously cracked lever-free and then a lever was added. `git log -p` for these lines. Let me check the file history for func_8017F1F0.
