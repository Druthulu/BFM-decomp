---
ts: 2026-10-22T09:32:22Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cRM2
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_1PivL7ZzjNVpmT4F84XF
---
This is slow. Let me try a different tack: use the gcc source to find where a PLUS's operands get swapped when one is a SYMBOL_REF. Search in combine.c for "plus_constant" usage with SYMBOL_REF, or in the function `simplify_binary_operation` (which is in combine.c around line 4493?).

Actually — better idea: gcc 2.7's `expand_expr` may create the tree; but the swap we observed could ALSO be in *cse.c*... but the .combine dump already shows the swapped form.

Hmm, hold on! Maybe the .combine dump is not "after combine" but "combine's own dump of what it did"? In gcc 2.7, `dump_combine`? The file .i.combine has ";; Combiner totals: ..." at the end — that's the combine dump.

Let me test which pass does the swap by looking at the .rtl dump more carefully: is the .rtl dump really before combine? In gcc 2.7.2's compile_file:

```c
  /* Expand the functions... */
  ...
  dump_rtl (rtl_dump_file, ...)?
```
Hmm, in gcc 2.7, `dump_rtl` is called from `compile_function` (after expand) with the "rtl" dump flag ('r'), then after combine the 'c' dump, after cse 'b'?...

Our .cse dump shows the same swapped tree as .combine. So the swap is in combine (or between .rtl and .combine).

Let me grep combine.c for the code that handles "GET_CODE (x) == SYMBOL_REF" in a PLUS context — maybe in `plus_constant` (in fold-const.c?) or in `simplify_binary_operation`'s PLUS case. Let me find simplify_binary_operation's definition line.
