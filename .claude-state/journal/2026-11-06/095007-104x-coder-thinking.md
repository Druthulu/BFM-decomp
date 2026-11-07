---
ts: 2026-11-06T16:50:07Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_Pki72Mc5MIl0hdk1W2JF
---
AddPrim is a *function* (extern s32 AddPrim(s32, void*)) in this TU, not a macro. Good.

So only the two gte macros need expansion. Let me update the item-2 splice.py to expand them from the original .i text:

The expansions (from t.i lines 45156-45157):
```
    __asm__ volatile ( "lw $12, 0( %0 );" "lw $13, 4( %0 );" "ctc2 $12, $0;" "ctc2 $13, $1;" "lw $12, 8( %0 );" "lw $13, 12( %0 );" "lw $14, 16( %0 );" "ctc2 $12, $2;" "ctc2 $13, $3;" "ctc2 $14, $4" : : "r"( m ) : "$12", "$13", "$14" );
    __asm__ volatile ( "lw $12, 20( %0 );" "lw $13, 24( %0 );" "ctc2 $12, $5;" "lw $14, 28( %0 );" "ctc2 $13, $6;" "ctc2 $14, $7" : : "r"( m ) : "$12", "$13", "$14" );
```

But careful: my splice strips // and /* */ comments, and these asm lines contain `//`? No. But they contain `"$12"` etc. — fine. However, my regex for /* */ might eat something? No.

Also, the body .c has `gte_SetRotMatrix(m);` — I'll replace with the expansion (with the arg). Implement in splice.py:
- For `gte_SetRotMatrix(ARG);` → expansion with ARG substituted.
- For `gte_SetTransMatrix(ARG);` → expansion2.

But note: after splicing, the .i already has these asm lines (they're valid in cc1). Good.

However, there's another subtlety: the original .i's function body may have additional differences (e.g., the `for` loop preserved). Fine.

Wait, but my earlier scoring via delever_search used the REAL pipeline (cpp) so it was faithful — scores like 52, 47, 8, 5 are real. The dumps were unfaithful only for the gte macros. So the residuals I saw via dt.sh are real. Good — the diff output from dt.sh is from the real scorer. I can trust dt.sh diffs; only my pass dumps need the fix.

Actually — since the gte macros expand to asm, and the pin removal affects things, the dumps would help. Let me fix splice.py and re-dump.

Given time (09:56 now, item started 09:44), let me focus. The fp pin removal gives 47 with a cascade. Let me first understand the allocation from a faithful dump of no_fp.

Update splice.py to expand the two macros.
