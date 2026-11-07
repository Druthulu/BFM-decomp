---
ts: 2026-11-06T11:34:56Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG28y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_SQrv2Z3tRk6ka9YY6zGl
---
Key insight from moves.md: the pin/opaque-copy lever is commonly replaced by a **HImode (s16/u16) temp copy** which escapes cse's equivalence class:

- line 202: `pin | func_8003DF8C | MATCH — u16 i; u16 j: the HImode copies of arg0/arg1 escape cse, so the target's opaque $a3/$t0 parameter copies survive (score 0)`
- line 203: `pin | func_80181E64 | MATCH — s16 v and the store reads v: the HImode copy t = v escapes cse, so the target's opaque move s8,v0 survives`
- line 217: `pin | func_80182ED4 | MATCH: copy hoisted above the branch via s16 temp (tmp=(s16)t; u=tmp) — HImode copy escapes cse equivalence class, so or v1,v0 survives in the bnez delay slot`

So for the `n = 3 + zr` opaque copy, I could use an s16/u16 temp: e.g., declare `s16 n` instead of `s32 n`? The target has `li v0,3` (s32 constant) though. Hmm, n is a count compared to i (s16). If n is s16, `n = 3` would still be a constant load li. But would it survive? The issue is the noop-move deletion eating the constant.

Actually, the target `li v0,3` in delay slot comes from the shared `n = 3` insn being copied into the delay slot by reorg. With a plain constant `n = 3`, the else arm is eaten. Hmm.

Let me reconsider: What exactly is at target insn 60? Let me look at the target disassembly around there. Let me get the target .s or dump. The delever_search compares against build. Let me find the target object/asm. Maybe I can look at the target listing to understand.

Actually let me try the HImode trick for n: declare `s16 n;`? But then `n = 4` and `n = 3`, `cnt = n`, `i < cnt`. Hmm the target has `li v0,3` so it's a word constant; an s16 n assigned 3 would still emit li. Let me just try variants.

But first, let me reconsider the third diff (store ordering). The memory barrier kept the `D_801151D0 = ot` store after the OT-link RMW. Without it, sched hoists the global store above. Can real C fix ordering? Options: make D_801151D0 store depend on a value loaded after the RMW — e.g., `D_801151D0 = (s32)ot;` where ot was updated by the RMW? No, ot is `ot += 10` after. Actually the store is `D_801151D0 = ot` after `ot += 10`, and the RMW uses `D_800AE7BC[*pbh]`. The scheduler hoists the global store above the RMW because it thinks they don't alias. Real C that creates a dependency: e.g. compute `ot` such that it depends on a load from the RMW chain. But the value stored is ot (address), which already is updated from pbh. Hmm.

Actually wait — in the diff, mine has the store (lui at + sw s0,0(at)) at insns 128-129, target at 134-135. So mine hoisted it 6 insns earlier. The target keeps it last. To prevent hoisting, need a memory dependence.

One real-C way: make the store value depend on the last RMW store. E.g.:
```
((PTag...)ot)->addr = (u32)ot;
ot += 10;
D_801151D0 = (s32)ot;
```
The RMW store writes through `ot`; the final store writes ot's value to global. They don't alias in the compiler's view (different addresses: struct member vs global symbol). The barrier told it they might alias.

Could we express D_801151D0 as potentially aliasing? If D_801151D0 were declared as an array or struct with the same type as the RMW target... The comment says "Re-declaring D_801151D0 as a one-field struct via a §37 asm-label alias works identically". That's a real-C-ish change (type change), but uses asm-label alias (an `__asm__`). Hmm, the brief says no asm. Could declare it as `extern s32 D_801151D0;` but access via a struct pointer? E.g. `extern struct { s32 v; } D_801151D0;` then `D_801151D0.v = ...`. That changes the type of the extern declaration (a declaration change outside the body? The extern is block-scope inside the body, so it's inside the body). The brief says "no signature or decl change outside the body (callers stay as they are)". Block-scope externs are inside the body, so allowed. But would `extern struct {s32 v;} D_801151D0;` conflict with other decls? It's block scope, so it shadows. The symbol name is the same. That's real C (a type change), no asm.

But would a struct-typed store be treated as MEM_IN_STRUCT_P and thus alias with the RMW (which is also struct)? The comment says "The OT-link store is MEM_IN_STRUCT_P + varying while D_801151D0 is a plain SYMBOL_REF, which is exactly the pair true_dependence drops". So making D_801151D0 MEM_IN_STRUCT_P would make true_dependence NOT drop the dependence → keeps order. That's the trick! "Re-declaring D_801151D0 as a one-field struct via a §37 asm-label alias works identically" — the asm-label part is only to alias the name to D_801151D0 if the C identifier differs. But we can just name the struct variable D_801151D0 directly: `extern struct { s32 v; } D_801151D0;`? Wait, that would make the C symbol D_801151D0 of struct type — but the actual object is an s32 at that address. The store `D_801151D0.v = x` stores a word at the same address. That's fine at the ABI level, just a different C type. And the symbol name is still D_801151D0. 

But does declaring `extern struct {s32 v;} D_801151D0;` produce MEM_IN_STRUCT_P? A store to a struct member `D_801151D0.v` — the field is s32; the address is &D_801151D0 + 0. MEM_IN_STRUCT_P is set for component refs. Yes, likely.

Hmm, but does that conflict with the earlier `extern s32 D_801151D0;` in the same function? I'd replace it. But D_801151D0 is read at the top: `func_80137D08(D_801151D0, ...)`. So I'd use `D_801151D0.v` there too. But then the read is a struct member read — same codegen (lw). Fine.

Alternatively, maybe simpler: use a union or just a one-field struct type defined at file scope? I can only edit the body, but I can declare a local struct type? C doesn't allow local struct definitions with a tag easily (GCC allows local struct definition? No, struct definition must be at file scope in C89? Actually you can define a struct inside a function as a declaration: `struct S { s32 v; };` at block scope is allowed in C89? GCC 2.7.2 with -std=gnu89 — yes, local struct declarations are allowed as declarations). Hmm, but a local struct type's tag is scoped. Simpler: `extern struct { s32 v; } D_801151D0;` — anonymous struct type in an extern declaration; that's valid C (the type is unique to this declaration). Then `D_801151D0.v`.

Wait, but can you write `extern struct { s32 v; } D_801151D0;` and then assign? Yes.

But there's a subtlety: `D_801151D0.v` — a component ref with constant offset 0. MEM_IN_STRUCT_P. Good.

Let me first tackle the biggest structural issue: the delay slots. Let me look at target asm around insns 55-95 and 125-140 to understand exactly. Let me get a disassembly of the target. Where is it? delever_search compares with build/. Let me find the target object. The tool builds from build/ presumably. Let me check tools/delever_search.py usage to see how to get a target listing.

Actually, easier: the .s file exists? For a matched function, build/ has the object. Let me check if there's a way to dump. Let me look at the tool briefly.

Let me check tools/delever_search.py --help.
