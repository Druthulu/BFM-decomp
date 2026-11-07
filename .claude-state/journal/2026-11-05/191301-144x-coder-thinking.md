---
ts: 2026-11-06T02:13:01Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG18x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_IRXPh4kSKhkUUuFHDvmW
---
Insn 368 is a simple jump (set (pc) (label_ref 374)). condjump_p should be false. But the gdb breakpoint fired on uid 368 with the condjump path... unless the breakpoint condition matched a different insn whose uid happens to be 368 in another context (there's only one function in the mini TU).

Wait, the condjump_p call is at 0x80f31cb; if it returns 0, it jumps to 0x80f3207. The backtrace shows the delete happened at 0x80f31f5, i.e., after condjump_p returned true. Hmm.

Unless... `reallabelprev == insn` was true and condjump_p(insn) returned true because insn 368 at that moment is a *different insn object* with uid 368? No.

Hold on: maybe the deletion happened at a later iteration of the `while (changed)` loop, after insn 368 was MODIFIED. E.g., during the first iteration, insn 368 was converted to a RETURN by redirect_jump(NULL). Then... no, a RETURN isn't a condjump.

OR: insn 368 was *reused*: after some optimization, the jump was deleted and its rtx freed, and a new insn allocated with uid 368? UIDs are assigned from a counter; deleted insns keep their uid. A new insn gets a new uid. So no.

Hmm, wait: maybe the condjump_p call at 0x80f31cb is a different site — let me check the source at line 664: `if (reallabelprev == insn && condjump_p (insn))`. The disassembly: at 0x80f31c0 `mov $0xfffffed0,%ebp` (weird), `jne 80f3207`, `sub esp`, `push %edi`, `call condjump_p`, `test eax`, `je 80f3207`, then `mov 0x20(%edi),%eax` (JUMP_LABEL at offset 0x20=32, matches!), `push eax`, `call next_real_insn`, then `push %edi`, `call delete_jump`. Yes, this is exactly line 664-667.

So condjump_p(our simple jump) returned TRUE. Why? condjump_p in gcc 2.7.2:
```
int condjump_p (insn) {
  register rtx x = PATTERN (insn);
  if (GET_CODE (x) != SET) return 0;
  x = SET_SRC (x);
  if (GET_CODE (x) == IF_THEN_ELSE) return 1; ...
```
Our PATTERN is (set (pc) (label_ref 374)) — SET_SRC is LABEL_REF, not IF_THEN_ELSE → false. So the condjump_p call must be on a different insn... but we're breaking on delete_insn(uid 368). The insn passed to delete_jump is %edi. Is %edi == our insn? At 0x80f31ef `push %edi` — %edi is the current insn in the loop. Then delete_jump(insn) → delete_computation(insn) → delete_insn(insn). The uid read at the delete_insn breakpoint is 368. So yes, the current loop insn is uid 368 and condjump_p(368) returned true.

But our .rtl shows 368 as a simple jump. Unless the pass MODIFIED it before: in the same iteration, earlier code could have rewritten it. Let me look at the sequence before line 664: lines 620-667 include "Detect jump to following insn" and the redirect_jump(NULL) at 656. Could redirect_jump(NULL) turn (set (pc) (label_ref)) into (return)? redirect_exp: `if (code == SET && nlabel == 0 && SET_DEST == pc && SET_SRC is LABEL_REF && XEXP == olabel) return validate_change(insn, loc, gen_rtx(RETURN))`. So the jump becomes (return) — a RETURN pattern. condjump_p(RETURN) false.

Hmm, so condjump_p(insn) should be false either way. Unless redirect_exp changed it to something else.

Wait — maybe the jump 368 was deleted in a LATER pass of the while loop, after being converted to a RETURN and then... Hmm.

Actually, let me reconsider: maybe condjump_p is true because PATTERN 368 at that point is `(set (pc) (if_then_else ...))`? Could the earlier jump passes have rewritten the simple jump to a conditional? Unlikely.

Let me get more info: at the breakpoint, print PATTERN (offset 16) and the first words. Actually, let me instead break on `delete_jump` and print the insn's PATTERN code and uid for our function. Let me do: break delete_jump, condition uid==368, print PATTERN code and SET_SRC code.

Hmm, but if condjump_p returned true, PATTERN should be a SET with IF_THEN_ELSE. Let me check by breaking at 0x80f31cb (call condjump_p) with %edi uid==368 and printing. %edi at that point is the insn (pushed as arg). At 0x80f31cb, edi holds insn. Let me break there and print uid and PATTERN.
