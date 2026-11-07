---
ts: 2026-11-06T12:28:12Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG31y
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_3wKefJiX1a8Th9mGrDEL
---
There's a file-scope `extern s32 D_801151D0;` at line 3627. A block-scope declaration with a different type (struct) would conflict at compile time? In C, block-scope extern redeclaration with incompatible type vs file scope → error "conflicting types". Hmm, the original function re-declares it at block scope as s32 (consistent).

Workaround: use a symbol alias with __asm__: `extern struct S151D0 s151D0 __asm__("D_801151D0");` — that's a symbol rename, not a codegen lever (like the worked example's aB9A02 alias). The constraint says no `__asm__` reg steer; symbol-name asm label is a name, not a codegen lever. The worked example (T10/func_80181F4C/win.c) kept exactly such an alias and it was accepted as a MATCH. Also moves.md line 320-323 mentions the 1-field struct alias for D_801151D0 as a MATCH move in G28x.

But careful: is it a "new lever of any kind"? The struct alias is a real C memory-shape change (MEM_IN_STRUCT), and it's in the catalog/moves as an accepted move. The asm label is only to bind the symbol name; the orig body already uses `__asm__("func_...")` labels for calls. I'll note it in notes.md.

Actually — maybe simpler: use a pointer cast to a struct type:
```
struct S151D0 { s32 v; };
...
ot = (s32 *)((struct S151D0 *)&D_801151D0)->v;   // hmm
```
The load `D_801151D0` → `((struct S151D0 *)&D_801151D0)->v`. The store: `((struct S151D0 *)&D_801151D0)->v = (s32)ot;` → this is a MEM with MEM_IN_STRUCT_P set (since the base type is a struct). No new declaration needed! The address is `&D_801151D0` (a plain address) cast to a struct pointer. 

Would gcc set MEM_IN_STRUCT_P? The MEM would be `(mem:SI (plus (reg) (const_int 0)))` with alias set... MEM_IN_STRUCT_P is set in the RTL based on the type's aggregate-ness in the expander. Since we access a field of a struct through a cast pointer, yes it should be mem/s.

Let's test that first.

Also for the load `ot = (s32 *)D_801151D0;` → `ot = (s32 *)((struct S151D0 *)&D_801151D0)->v;` — this might introduce an extra lea? `&D_801151D0` with field 0 → same address, no extra insn.

Let me try.
