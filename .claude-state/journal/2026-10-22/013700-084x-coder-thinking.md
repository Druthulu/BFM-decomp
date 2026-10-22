---
ts: 2026-10-22T07:37:00Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG15b
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_Bx5apHyyrWN5fbJg0wyS
---
Now I see: the census's "SCAN" body = lines 3097-3111, which starts at the `SCAN()` invocation and ends at the end of the block containing the launder at 3102. So the "body" is a chunk of the function func_8018D98C.

The launder at 3102:
```
        { s32 _m = (s32)&D_801C8344;
          __asm__ __volatile__("" : "=r"(_m) : "0"(_m));
          ((void (*)(s32, s32, s32))func_8012F14C)(*(s32 *)((s0) + 0x20) + 0x34, _m, (s32)(v10)); }
```
The launder gives `_m` a 2nd set → so the address &D_801C8344 is rematerialised at each call site instead of being hoisted into a callee-saved register (per the comment).

The lever-free replacement (per the comment's rationale): the address must be rematerialised at every call. The known recipe (from my item 1 and the moves.md "dead-reset CSE-breaker"): assign the address to a variable, use it, then reset it to 0 (a dead reset) before the next site — breaking cse's equivalence class so each site re-derives the address.

Hmm, but here the launder is per-site (each site has its own `_m` variable in a block scope). Hmm, the comment says "Each expansion gets a FRESH pseudo that cse/cse2 cannot unify with the other sites' identical (symbol_ref "D_801C8344")". Hmm, that's the tree's rationale for the launder.

Hmm wait, the launder's role per the comment: the asm gives `_m` a 2nd set so that the address is NOT hoisted into a callee-saved register but rematerialised at each call.

Now, how do I score this item? The body is a region, not a function. Let me test what delever_search --try does with fn=SCAN.

Let me try scoring the current region as a body: create orig.c = lines 3097-3111 and run dt.sh.

Actually, hmm: the delever_search's body mode: it compiles the TU with the body spliced in place of the function FN. For a non-function FN, the splicing probably fails or it may find the "Function SCAN" hmm.

Let me look at the body_span/splice logic in delever_search.py to understand what --body does for a macro-ish name. Let me grep for "def body_span" and the apply logic.

Actually, let me just TRY it: create orig.c = the region text and run dt.sh. If the score comes back meaningful (e.g. "score N"), then the harness handles it (maybe it splices the body into the TU by replacing the region).

Let me try.
