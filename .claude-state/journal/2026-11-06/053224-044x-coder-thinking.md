---
ts: 2026-11-06T12:32:24Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_0TjbK1bYFx6rBv1Du7Vm
---
At 1a88 the jal (func_8012CAE4) then `j 1e3c` (the return epilogue) with nop delay. So the early `return ret;` compiles to just a jump to the epilogue with v0 as left by the call. Interesting: no move.

And at 1aa4: beqz a0 → j 1e3c.

So the target's C for those returns must be something that returns the pseudo ret without a copy. If ret is v0 (pinned), `return ret` = `move v0,v0` → deleted. So it works because ret IS v0.

Lever-free: can we make the early returns not use ret, without adding insns? Options:
- `return 0;` → emits li v0,0/move v0,zero → extra insn (target has none). Not good.

Alternatively, the target's C might genuinely be `return ret;` with the pin. So without the pin we must find a C form where the return-value pseudo gets v0.

Idea: since gcc's `expand_return` emits `v0 = ret` at the return, and target has no such move, the target's ret is in v0. To get a pseudo into v0 naturally, the pseudo must not conflict with v0 anywhere and global-alloc must choose it (density). But global-alloc prefers callee-saved regs for long-lived pseudos. ret's live range from entry (uninitialized use) to the end → global.c gives it a callee-saved reg (s0) — as seen in mine.

So: eliminate the uninitialized early uses of ret! If the early `return ret;` were replaced by a form that doesn't reference ret, the pseudo's live range would start at the first arm's def.

But what can the early return be, that emits no insn and doesn't reference ret? The target's asm shows the return jumps to the epilogue leaving v0 untouched. If the C were `return ret;` with ret in v0 → no insn. If the C were `return 0;` → li v0,0. If the C were... hmm, `return;`? No, the function is s32.

What if the early returns return a *different* pseudo that also lands in v0? E.g. a local `s32 r2;` uninitialized and returned — gcc would still need it in v0.

Hmm, what if the early return is `return func_8012CAE4(...)`? func_8012CAE4 is void.

What about `return (s32)func_8012C1B8();`? no.

Alternative: keep `return ret` but initialize ret in a way that... no, the issue is the live range crossing calls.

Hold on. Let me reconsider: is it really the live range from entry? Let's check mine's asm: `li s0,25` in arms → ret in s0. If the early uses were removed, would global-alloc give v0? Density/priority: ret would have defs in ~6 arms and uses at STORE; its live ranges are short. Global-alloc assigns call-clobbered regs to pseudos with short live ranges and callee-saved to those crossing calls. With short ranges, v0 is a candidate but so are a0-a3, t0-t9, v0/v1 — the choice is by priority order. Hmm, uncertain.

Actually — the target's arms `li v0,22` etc. and the store `sh v0,2(s1)` at the end. Also `lh v0,112(s1)` reloads unk70 in v0 at the end of arms.

So ret in v0 naturally. To achieve it lever-free, maybe there's a well-known move: make the arms `return` directly instead of `goto STORE`, i.e., duplicate the store? No, single store.

Another approach: `s32 ret;` declared inside... no.

What about making the value be the return expression at the STORE label only: 
```
STORE:
    ((...)->unk2 = ret;
    return ret;
```
What if instead:
```
    ((...)->unk2 = ret;
    return ((...)->unk2);   /* reload from the stored halfword? */
```
That would emit lh v0,2(s1) — extra insn (though target might have... no).

OK, let me test the hypothesis quickly: remove the early `return ret;` uses by replacing them with `return 0;` in a scratch candidate and see if ret gets v0 (score will still be off by the li insns, but I can see the allocation). That's diagnostic.

Actually better: let me test a candidate where the early returns are `return ret;` but ret is declared *after*... no.

Diagnostic c2: replace early returns with `return 0;`.
