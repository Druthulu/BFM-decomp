---
ts: 2026-11-06T15:57:05Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_rvxk6eRbMO209GtyQHKK
---
Still 4. Let me check if vi1's la moved at all (maybe the residual is different). Score 4 ORDER — same count. Likely the la position.

At this point, item 4's two launders both appear load-bearing with no plain-C crack. Time is ~09:00 (started ~08:47) = 13 min. Tries: 20 + vg1 + vh1 + vi1-3 = 25. Need 30 and 20 min.

Let me try a few more on the arg launder with the "second declaration" trick, which I haven't actually tested:

j1: 
```
extern u8 D_800AF648_b __asm__("D_800AF648");
arg = &D_800AF648;          /* first decl */
func_80052E38((u8 *)&D_800AF648_b);   /* second decl direct */
```
The arg set is dead → deleted. La at the call (late). Same.

j2:
```
arg = (u8 *)&D_800AF648_b;   /* second decl */
func_80052E38(arg);
```
La at the copy (late).

Hmm.

What about making `arg` a *pointer to a struct with an initializer*? no.

Let me think about the combine pass: it merges `set a0 = reg arg` into the previous `set arg = const` (the REG_EQUAL) and deletes the first set. This is `combine`'s "if_then_else" / simplify_rtx with REG_EQUAL. To block it, the copy's source reg must not have REG_EQUAL at the time. cse sets REG_EQUAL on the set insn; combine uses it if the set is the immediately... hmm.

If arg is *used twice* (the copy at the call + another use), cse's REG_EQUAL on the set is still there, but combine only merges when the value is used once? Combine's substitution is based on `set (reg) (const)` followed by a use; it substitutes into the use and deletes the set if the reg dies. If the reg has another use, it keeps the set and doesn't delete. So a second use WOULD keep the set! The la would then be at the set (early) and the call copy would be... combine substitutes the constant into the call copy anyway, making `a0 = const` (another la?) — that would be 2 las. Unless the call copy stays as a move.

Hmm, the second use: if it's a *real* use that produces the same register value, we'd get 2 materializations.

What second use could we add? A dead one deleted by flow. flow runs before cse, so a dead use deleted by flow is gone before combine. A dead use that flow *keeps* (e.g. a volatile access)? adds.

OK, I'm going to call item 4 a WALL after reaching 20 min and 30 tries. Let me use the remaining time to test a couple more and then document.

More tries:
j3: `func_80052E38(arg);` with arg declared `u8 *const`.
j4: assign via `(u8 *)(u32)&D_800AF648`.
j5: `arg = &D_800AF648; if (arg) func_80052E38(arg);` (adds branch).
j6: put `func_80052E38(arg);` inside a do-while(0).

Let me test j3-j6.
