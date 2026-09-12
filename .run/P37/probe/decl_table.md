# T2 probe (ii) — the canonical prototype (the definition's ANSI signature) per TU × callee; seed 37; 4828 judgements; 941 s wall

Population: 93994 lying declarations in 4109 TUs (argcheck). Sample: per TU, every lying callee repaired ALONE (its declarations in that TU), judged on the object.

| TU kind | judgements | IDENTICAL | DIFFERS | COMPILE-ERROR | no edit | causes (non-identical) |
|---|---:|---:|---:|---:|---:|---|
| main | 41 | 19 | 0 | 22 | 0 | {'compile: src/800.c: At top level:': 21, 'compile: src/800_b_2.c: At top level:': 1} |
| md | 80 | 29 | 0 | 51 | 0 | {'arity (the call passes a different count)': 47, 'conflicting declaration elsewhere in the TU': 3, 'compile: src/md_MAIN_003/md_MAIN_003_jr_800D1': 1} |
| ov | 4666 | 4406 | 0 | 260 | 0 | {'conflicting declaration elsewhere in the TU': 114, 'arity (the call passes a different count)': 73, 'compile:  1546 | #define NULL 0': 8, 'compile:  1547 | #define NULL 0': 4} |
| shared-header | 41 | 19 | 0 | 22 | 0 | {'arity (the call passes a different count)': 16, 'conflicting declaration elsewhere in the TU': 4, 'compile:  1548 | #define NULL 0': 2} |
| **all** | 4828 | 4473 | 0 | 355 | 0 | |

**The definition's signature is a free replacement for 4473/4828 judged (TU, callee) pairs (92.6 %); 0 move bytes, 355 refuse to compile (arity contradictions and conflicting declarations).** Per callee, the non-free cases are the declaration solver's input (T3): the definition's width or return axis, or a byte-proven K&R call.

Of the DIFFERS: 0 have a narrow parameter in the definition (`s16/u16/s8/u8`: the caller now converts — the width rule); 0 were `()` declarations.

Rows: `.run/P37/probe/decl_rows.jsonl`.
