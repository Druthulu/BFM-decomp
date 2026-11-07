---
ts: 2026-11-06T07:39:04Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG24
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_aCCoy88QvoVX3Kc5KzwM
---
Only 3 copy temps in block 0 (81,82,84) and 2 in block 1 (85,86). But the target shows 4 loads per struct copy. The lreg dump here is for the BASE (lever-free) candidate compiled through the dump pipeline, which is the SAME source. Wait, base has two struct copies. Block 0 = entry through the branch (contains both copies + call + decrement). Block 1 = if-body. Block 2 = fallthrough.

In block 0, the copies need 4 temps each but they can reuse registers (live ranges disjoint): group1 uses 3 temps (81,82,84) + v0(75)? Hmm 75 is "used 3 times across 3 insns" — that's the pointer v0 (3 refs: load from s1, then used in copies). Actually the pointer v0 is used twice in the two copies (as base) plus once assigned = 3 refs. Yes 75 = v0 pointer.

The 4 loaded values per struct copy: maybe combine merges some. Actually a 16-byte block move in GCC 2.7 expands into 4 word loads/stores using 1-2 temps, not 4! Wait, expand_block_move may use multiple. The target shows 4 distinct load dests (v1,a1,a2,a3) and 4 stores — so 4 temps live simultaneously. But the lreg says only 3+2 temps. Hmm, maybe the lreg dump's "Register N used" only lists pseudos needing allocation, and some got tied to hard regs (e.g., the loads' dest tied to the store's source?).

This is getting deep. Let me look at the sched dump or rtl dump to see the copy insns and their regs. Actually, let me look at the final allocation in the .lreg: ";; Register 81 in 2." means register 81 got hard reg 2 (v0)? That's reload output maybe. Hmm, the dump line ";; Register N in M" is the final assignment from reload? For base: 75→2(v0), 81→2(v0), 82→2(v0), 84→3(v1), 85→2, 86→2. That doesn't match the final asm (a0,a1,a2,a3). So the .lreg dump is pre-reload and local-alloc's choices are overridden? Actually the .lreg dump happens after local-alloc and global-alloc but before reload; the "Register N in M" is the renumbering. Hmm, 81→2, 82→2, 84→3 can't all be right for the final asm.

Maybe the dump pipeline differs from the scoring pipeline (different flags? no, same). The scratch base compiled by cc1_dumps_tu.sh uses the scratch TU and same flags plus dump flags. Should match.

Wait, the final asm from the score shows v1,a1,a2,a3 for the first copy. If local-alloc assigned 81,82,84 to v0,v0,v1, that's 2 registers, not 4. Then reload assigns? Confusing.

Let me step back. The practical question: can I find a real-C spelling scoring 0? The engine searched 191 candidates and never beat 14. The wall tags say global-hardreg-reserve. I've spent ~25 minutes on item1. Let me consider the possibility that the a0 reservation comes from the *local `(void)` declaration leak* — no.

Actually, hold on. Let me reconsider the call: the target calls func_800CAF84 with NO args. But what if the original source called it as `func_800CAF84()` and the compiler had to preserve a0 because the function's prototype is `(void)`... no.

Let me look at the target's a0 liveness from the RTL of the ORIGINAL (banked) source — but the banked source has the lever. The lever (pin+keepalive) IS what makes a0 live in the target? No! The target bytes are the ORIGINAL GAME bytes; the lever was crafted to reproduce them. The pin+keepalive in the source makes a0 live, which reproduces the target's a1-a3 allocation. So the target's natural C must have a0 live for some other reason.

The P36 lever approach: they added `register $4` pin + keepalive to force a0 live. The question is what natural C the original used.

Given the sibling func_800CB158 calls `func_800CAF84(arg0)` with the argument — maybe our function also calls `func_800CAF84(arg0)`, and the local `(void)` decl in func_800CB400 is a LEVER too (or a mistake) that leaks the type. But the file must build as-is. If we change func_800CB400's decl too, that's outside our body — not allowed. But our own function could use a different call spelling that still compiles: e.g., cast the function pointer:

`((void (*)(s32))func_800CAF84)(arg0);`

That's ugly but real C. Would it produce the same call? It would pass arg0 in a0, and the jal would have no move if arg0 is in a0. But the cast itself doesn't emit code. Let me test this! If the original called with arg0, a0 stays live across the copies → the copies use a1-a3, and the call needs no move. This could be the crack.

But would GCC 2.7 accept a cast of a function with `(void)` type to `void(*)(s32)`? Yes, with a warning maybe. Let me try:

```
extern void func_800CAF84();
...
((void (*)(s32))func_800CAF84)(arg0);
```

Hmm, but the local extern `()` still gets the leaked `(void)` type. A cast to a function pointer type and call through it should work.

Actually simpler: declare a local function pointer variable? That adds a register/insn maybe. The cast-in-call should be free.

Let me test. Also try `func_800CAF84((void*)arg0)` — that's "too many arguments" too. The cast of the function is the way.

Let me write v40: base with call replaced by `((void (*)(s32))func_800CAF84)(arg0);` and the local extern removed (or kept? keeping the `(void)` decl then casting is fine). Let me keep the original local extern line to minimize changes? The local extern `(void)` is inside our body and is a FAKE decl maybe. But keeping it doesn't hurt the cast.

Actually, the cleanest natural C: the original probably had NO local extern (since func_800CB400's decl already declares it, albeit leaking `(void)`), and called `func_800CAF84(arg0)` — which wouldn't compile. So the original source must have had something that compiles. Maybe the original our-function had its own `extern void func_800CAF84();`? Still fails due to the leak.

Wait — does the leak really apply? My minimal test had `void h(void) { extern void f(void); }` BEFORE `void g(s32 x){ f(x); }`, and it failed. But the file has func_800CB158 calling f(arg0) BEFORE h — works. So yes, source order matters.

So how did the original source call func_800CAF84 with an arg after line 238? Maybe it didn't; maybe the original call has no args, and the a0 liveness comes from elsewhere.

Hmm, but the target's jal has `nop` in the delay slot and no `move a0` — consistent with no-arg call. If the original called with arg0 and arg0 was live in a0, also consistent (no move needed). Both produce identical bytes IF a0 holds arg0. The difference is whether a0 is live across the copies.

Let me just test the cast version. If score 0, we've cracked it!
