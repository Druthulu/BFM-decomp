---
ts: 2026-11-06T01:39:21Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_dzCPbnoqnmMuBlq7KE8A
---
Crucial: "If a jump references the end of the function, try to turn it into a RETURN insn" — `redirect_jump (insn, NULL_RTX)` when the label's next active insn is 0 or a RETURN. Hmm, the epilogue label (return_label) is followed by the epilogue code (lw ra; ...; jr ra = RETURN). So next_active_insn(label) is the first epilogue insn, not a RETURN. Hmm.

And "Detect jump to following insn" only handles condjump_p. For unconditional jumps to the next insn, where's the deletion? Maybe in `delete_jump`/`thread_jumps`? Let me look for where simplejump to next is deleted: search "jump to following". Hmm, maybe the code is in the `this_is_simplejump` block further down. Let me search for "simplejump" and "reallabelprev".

Actually: `reallabelprev = prev_active_insn (JUMP_LABEL (insn))` then the condjump check. For an unconditional jump whose target label's prev is itself... the label is at the end. If the jump is the last insn before the label (i.e., zero's block ends with jump and label immediately follows), then prev_active_insn(label) == the jump → but the check requires condjump_p. So unconditional jump-to-next is NOT deleted here. It might be deleted in `delete_dead_jumps`? Hmm.

Wait — but for vA (with return) the score was 9, identical to nopin. Maybe the return jump wasn't emitted at all. Let me dump vA and check.

Actually let me first check whether a `return;` at the end of the function gets elided by the expander. In gcc, c-parse/expand: `expand_return` for `return;` calls expand_null_return. There's a known optimization in stmt.c: "if (this is the last statement in the function) ... don't emit a jump". Hmm, expand_null_return_1's use_goto path. Let me look for "return_label" placement and a special case.

Actually in expand_function_end, there's:
```
  /* If the function returns a value, ... */
  ...
  /* Output the return label. */
  ...
  if (return_label) emit_label (return_label);
```
Hmm.

Let me just test: dump vA and see if a jump to the return label exists in .jump / .rtl.

Let me compile vA with --keep and dump.
