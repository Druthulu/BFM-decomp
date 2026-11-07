---
ts: 2026-11-07T00:27:23Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cP1
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_lF1Nkkp1ZebsdAXV1iqN
---
So invalidate_memory removes entries that are `in_memory` AND (all || (nonscalar && in_struct) || addr varies).

Our pointer load `(mem:SI (symbol_ref "D_80126B78"))`: addr doesn't vary; is it `in_struct`? in_struct means the address is a register or complex (in_struct is set for MEM whose address isn't a constant / is a REG or PLUS). For a symbol_ref address, in_struct = 0. So a nonscalar store does NOT invalidate it. Only `all` (a call, or asm clobber) invalidates.

And the load `(mem:HI (plus (reg) (const 18)))` — address varies (register) → invalidated by any store. Fine.

So the target's second pointer load must be because something invalidated ALL memory between use1 and use2: a call, or... the target has no call between. Hmm.

Wait, maybe the target doesn't reload the pointer for the second use because of invalidation but because of register pressure — i.e., the target compiled code where cse DID cache it but the value didn't survive? No, cse in the target's compile is the same compiler.

Hmm, unless in the target's source the two uses are of *different* expressions (not cse-equal) and the compiler emitted two separate lui/lw pairs. E.g., the target's source might use a *different global symbol* twice? No, we know the semantics.

Or maybe the target source reads D_80126B78 through a function-like macro/struct: e.g. `((Unk*)D_80126B78)->unk12` vs `*(u16*)((u8*)D_80126B78 + 0x12)`; RTL equal anyway.

Alternatively the target's second load isn't the pointer but a *different* address: `lui v0; lw v0` then `lhu v0,18(v0)`. It's the same.

Hold on — what if in the target's compile the pointer load at use1 is NOT the symbol but something else... Let me look at the target disassembly directly to understand. Let me get the target listing. Is there a target disassembly available? tools? Let me check .run/P40/T11/bin/ and see what tools exist. Perhaps delever_search --explain gives a diff, but a full target listing would help. There's tools/cc1_dumps_tu.sh, tools/alloc_table.py, hdump.sh. And presumably an objdump of the target.

Let me check the item's build target: the comparison is with "the function in build/". So there's a build/objdump. Let me find how delever_search finds the target: maybe build/*.s or the original binary via objdump. Let me check the tools dir for a script that dumps the target.

Simplest: ask the retriever? No — retriever is for code lookups; this is fine to inspect myself. Let me look for the target disassembly command in tools/.

Actually, the diff output already shows target lines. I can request a bigger tail (dt.sh tail_n) to see the whole diff. Let me get the full diff with tail 200 for w1.

But more useful: think about what real-C source produces the target.

Target shape around the two uses (from the diff):
```
target[25:29]: lui v0,0x0 ; lw v0,0(v0) ; lhu v1,42(s0) ; lhu a0,18(v0)
...
target[33:35]: lui v0,0x0 ; lw v0,0(v0)
target[36:37]: lhu v0,18(v0)
```
So both uses reload the pointer. If cse cached `(mem (symbol_ref D_80126B78))`, the second use wouldn't reload. For the target to reload, cse's table must have been cleared between → a CALL or an asm. There's no call between in the target... unless the target's source has something that cse treats as `all` invalidation: `invalidate_memory(&everything)` is called at line 7246 — let me look at that context.

Line 7246: in cse_insn, probably `if (code == CALL_INSN) invalidate_memory(&everything)`. Also a volatile asm with memory clobber (that's our barrier!). Hmm, but the target is the ground truth — it can't have an asm.

Wait, maybe the target uses `setjmp`-like? No.

Alternatively: cse's memory entry for the symbol load may be invalidated because cse only caches MEMs when `dest is not 0` etc. Actually maybe the entry isn't recorded at all because the load is `(mem (symbol_ref))` and cse only records loads whose... no, it records.

Hmm, what about *different* cse passes: cse1 then cse2. And the pointer value is in a hard register? In the target, use1's pointer goes into v0 (a call-clobbered reg). If the value stayed in v0 across the store, cse would reuse it. But the store to obj+0x14 uses some regs; v0 might be... The target computes `lhu a0,18(v0)` into a0, then subtracts.

Alternatively: maybe the target's source performs the two loads through *two different variables*, e.g., one via a local pointer `p = D_80126B78;` and one direct. Still cse-equal RTL (the local pointer load is `(mem (symbol_ref))` too). Unless one is `p` (a local variable holding the pointer, set earlier) and cse... same.

OK here's a thought: maybe cse DOES cache it, and the second load in the target comes from the *local-alloc/reload* rematerializing because v0 was reused (i.e., the value died). If the target's source has a call or something that forces a different allocation... Hmm, but a `lw` from the symbol is not rematerialized by reload normally.

Let me just look at the full target disassembly and my candidate's, with the actual instructions and registers. The dt.sh prints a diff tail; with tail 200 I'll get the full listing. Let me do that for w1.

Also, let me check how much time this item has. Started 17:24. Budget 20-30 min per item.

Let me get the full diff.
