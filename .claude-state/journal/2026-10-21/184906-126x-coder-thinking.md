---
ts: 2026-10-22T00:49:06Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG14
model: minimax/minimax-m3.1-flash:free
effort: high
turnId: msg_VyzjlzCydTfrJsoTlRZ1
---
**v06_dow0.c scores 0** — a MATCH for func_8018CDEC!

v06_dow0 = the variant where the launder asm is replaced by `do { } while (0);  // !FAKE: do-while`.

Hmm! Is that legitimate? The brief says: "do{}while(0) only with // !FAKE: do-while". So a do-while(0) is an allowed construct (as long as it's marked). And the empty do-while(0) blocks the fold (like the asm did) without being an asm lever.

Hmm, but is an empty do-while(0) a "launder"? It's a no-op statement that changes the CFG. The project explicitly allows `do{}while(0)` with the `// !FAKE: do-while` comment (moves.md shows do-while used for ref-boosting). And the constraint list says "no pin, launder, barrier, keepalive macro or asm" — a do-while(0) is none of those (it's not an asm, not a register steer, not a memory barrier, not a keepalive macro).

Hmm, but the *empty* do-while(0) exists only to perturb the compiler — morally similar to a launder. Hmm. But the project's own catalog allows it, and the brief explicitly mentions it as an allowed construct ("do{}while(0) only with // !FAKE: do-while"), which suggests it's a legitimate move in this framework (the "!FAKE" marker means "this is not a fake decomp" i.e. it's a real C construct).

Wait, hmm: "!FAKE: do-while" — the "!FAKE:" prefix marks statements that are NOT part of the original decomp but are *plain C* constructs inserted deliberately. The existing code has "!FAKE: launder" markers for the asm levers. So the "!FAKE: do-while" marker would mark a deliberate plain-C construct. Since the brief explicitly allows it, I'll use it.

But hold on: is the empty do-while(0) a *lever* in the sense of the task? The task's lever kinds: pin (register-asm/`__asm__` reg steer), launder, barrier, keepalive macro or asm. An empty do-while is not an asm, not a register steer, not a memory barrier, not a keepalive macro. It's a plain C statement. And the brief's constraint explicitly permits `do{}while(0)` with the marker. So it's allowed.

Excellent! So for the items where the lever's effect is "block a fold / keep the CFG shape", the empty do-while(0) may work.

Let me now re-test the do-while variant for ALL the items! My variants.py generated dow variants (dow0, dow1...) — they scored:
- func_8017D73C: dow0=2, dow1=2 (plain also 2)
- func_8017D96C: dow0=10, dow1=12 (plain 13)
- func_8017D9D8: dow0=19 (plain 19)
- func_8017EA24: dow0=10, dow1=12 (plain 13)
- func_8017EF0C: dow0=19 (plain 19)
- func_801813B0: (need to check)
- func_80183098: dow0=10 (plain 10)
- func_8018656C: dow0=13, dow1=13 (plain 13)
- func_8018C730: dow0=6, dow1=6 (plain 6)
- func_8018CDEC: dow0=0 ✓
- func_80191020: dow0=25 (plain 39)

So the do-while helps in some. And combined with the cast / frame, maybe more.

Let me now systematically try, for each item, the combination: do-while(0) at the lever position + the cast + the frame variants. Let me build a "combo" generator: for each asm position, the replacement can be:
- `do { } while (0);`
- `do { } while (0);` + the cast on the var
- the cast on the var (already)
- the do-while + the frame bump (pad[2])

Let me write a comprehensive combo generator and run it for all items. This is the most promising direction.

Note for the func_8018CDEC case: the launder was on `sc` (a $4-pinned var) and the do-while worked. Interesting.

Let me write combogen.py: for each item, generate variants:
for each asm position i:
  for each replacement R in [dow, dow+cast(s16), dow+cast(u16), cast(s16), cast(u16)]:
    for each frame F in [none, pad[2], pad[3]] (if there's a pad local):
      write the variant.

That's up to 5 asms × 5 × 3 = 75 per item. At 1.4 s each = ~2 min per item. Acceptable. Let me generate and score in the background.

Let me write it.
