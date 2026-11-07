---
ts: 2026-11-06T06:06:59Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG23
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_mbYxGHl6mT4JiriTFqTA
---
Now, plan. Item 1: func_80181E08 in ov_SC06_025. Kinds: launder,pin. Levers:
- `register s32 *pp __asm__("$23")` and `pf __asm__("$22")` — pins (register-asm).
- `__asm__("" : "=r"(otz) : "0"(otz));` — launder.

Goal: lever-free body scoring 0.

The comment says: "Loop 1 hoists both out-param addresses into callee-saved regs. Written as plain locals the pointers land in $fp/$s6 instead of $s7/$s6: gcc's allocno_compare ranks `zpush` (3 refs, loop-weighted) above them. Pinning the two pointers frees $fp for `zpush` and reproduces the target exactly."

So the lever-free goal: make `pp` and `pf` win $23/$22 over zpush without pins, e.g. by adding refs to pp/pf (loop-weighted) so their allocno priority beats zpush. Classic move: +refs via do-while(0) or extra use. Or reduce zpush's refs. Or split.

And the launder on otz: "Zero-byte re-tie: without it combine folds `move $s1,$v0; move $a0,$s1` into a single `move $a0,$v0` (the target keeps both). §189-C form." A real C 2nd set: `otz = otz;`? Hmm. C0414 dead-reset cse-breaker. Or `otz = (s16)otz` — but otz is used for otz*4 addressing and func_801823D4. Actually a real 2nd set of otz: e.g. `otz = otz + 0;`? That's identity → combine folds. Moves catalog: "real 2nd set" — e.g. `otz = (s16)otz` when value is s16-range. RotTransPers4 returns s32; otz then used as `otz * 4` index and passed to func_801823D4 and func_8012E28C. Hmm, (s16) cast changes value potentially. But maybe safe? No — must be byte-exact codegen, not semantics? Actually the check is codegen match only (score = insn diff). But it must be a legitimate representation.

Wait — for score 0, the C body must produce the target instructions exactly. Semantics don't matter for scoring, but the project's rule is real C. A cast `(s16)otz` adds sign-extension instructions though — sll/sra pair. That changes codegen.

Better: the launder keeps `move $s1,$v0; move $a0,$s1`. Target: two moves. The asm re-tie "=r"(otz) : "0"(otz) is a zero-byte tie. A plain-C equivalent: `do { } while (0)`? From G14: "the launder tied-output on sc -> empty do { } while (0) (plain C keeps the CFG shape the asm forced)". And G22: "do-while(0) around raw=t splits the EBB so the lbu qty takes v1 and t v0". And C0535: do{}while(0) splits cse1 EBB.

So for otz: wrap in do{}while(0) to split the EBB so combine cannot fold the copy? Let's just try.

Plan of attack per item:
1. Copy current def from src to <dir>/orig.c (and nopin.c maybe).
2. Write candidate win.c with levers removed (pins dropped, asm removed), then add real-C moves until score 0.
3. Score with dt.sh.

Budget 20-30 min per item. 5 items. That's 100-150 min. Hmm, big. Let's be efficient.

Let me start item 1. First check that the orig.c isn't present (dir only has fn/kinds/tu). Generate orig.c from src lines 4904-4994 plus needed typedefs? The --body mode compiles the function definition only; it needs the types (V8_SC06_025_80181E08, G4, G3, Unkstruct_80181E08). Those are likely in the TU's include or declared earlier. How does --body work — it substitutes the body into the TU at the function's location, so preceding declarations are available. Yes: "--body: FILE holds the function's definition only" — it splices it into the TU.

So orig.c = the function definition text as in src (lines 4904-4994).

Let me build a script to extract the function body from src by name. Actually simpler: sed range. Let me create a small extraction helper under my shard dir.

Let me first look at how the delever_search --try reports score. Run baseline on orig.

Let me write extract script: find line with `^void func_NAME(` or `^s32 func_NAME(` and take to matching closing brace at column 0.

I'll write a Python script under .run/P40/T11/G23/bin_ex.py. Wait, writing scripts under .run/P40/T11/G23/ is allowed ("write only under .run/P40/T11/G23/ plus appends to moves.md").

Let's do it.
