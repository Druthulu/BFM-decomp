---
ts: 2026-11-06T15:01:30Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO03x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_9rDFJCnSmWhsxxvH5o6z
---
Baseline works. Now craft the lever-free body. The launder line is:

```
            /* lever 3: sched1 otherwise hoists the PAN multiply ahead of this one */
            __asm__("" : "=r"(vol) : "0"(vol));  // !FAKE: launder — NEEDED DIFFERS (P36 rung B t8_tus2)
```

Replace with a real second set. Try `vol = vol & 0xFFFF;`? Would likely produce an andi (+1 insn). Try splitting the vol computation:

```
vol = (0xA0 - av) * 0x7F;
vol = vol / 0xA0;
```

Let's test that as candidate a1.c. But careful: the whole body must be lever-free — other than this launder, are there pins? Yes: `register void *r4 __asm__("$4")` and `register s32 av __asm__("$5")`. kinds = "launder" only, so pins are allowed to stay (non-row kinds). Constraint: "levers of other kinds the def already had (pins under other causes) may stay, never added". Good.

But wait: if I change the vol computation and the pins interact... The `av` pin $5 might be needed. Keep it.

Let me create candidate a1.c = orig with the launder replaced by the split. Let me use sed-like Python or Write the whole file? Better: copy orig.c to a1.c and use Edit. But Edit requires reading the file (I have the content via src read). Let me use cp + python? Simplest: use `sed` to produce candidate. But the brief says read files with Read tool or ranged sed. Writing candidate via a script is fine.

Actually I'll just Write a1.c by copying orig and modifying — but Write requires content; I have the body from the src Read. That's 100 lines; writing it fully is fine but error-prone. Better use a small python replace script under the shard dir: gen.py that reads orig.c and applies textual substitutions from a spec. Hmm, but "One action per command" and scripts are fine.

Let me create a helper `mk.py` that takes orig, out, and old/new pairs? Simpler: use python with explicit strings.

Actually simplest: `cp orig.c a1.c` then `Edit` on a1.c. But Edit requires having Read a1.c in conversation. I could Read a1.c after cp. That's 2 calls. Fine.

Alternatively use `sed -i` — but that's editing, allowed? The brief allows writing under shard dir. sed is fine but "Read files with the Read tool or a ranged sed, not a bare cat chain" — that's about reading. Editing with sed is ok. But the launder line is unique; sed replace with multiline is awkward.

I'll write a generator script that produces candidates from orig.c with named transformations. Let me make `mk.py`:

```python
import sys, pathlib
orig = pathlib.Path(sys.argv[1]).read_text()
cand = sys.argv[2]
text = orig
# apply transformations keyed by name
...
```

Let me instead do direct python one-liner? "Scripts, not inline python -c". So write a script.

I'll write mk.py with a dict of named transformations, each a (old, new) pair list. Then call `python mk.py orig.c a1.c t1`.

Let me define candidates:
- t1: split vol:
  old: `vol = ((0xA0 - av) * 0x7F) / 0xA0;`
  new: `vol = (0xA0 - av) * 0x7F;\n            vol = vol / 0xA0;`
  and remove the launder line (replace launder with nothing).
- t2: `vol = vol & 0xFFFF;` replacing the launder.
- t3: `vol = vol | 0;` (likely folded).
- t4: dead-reset style: `vol = ((0xA0 - av) * 0x7F) / 0xA0; ... vol = vol;`? 

Hmm wait. Important subtlety: the launder must be removed AND its effect replaced. In t1, the launder is removed and vol gets a 2nd set earlier (the multiply). But the position matters: the second set (multiply) is BEFORE the division, and the launder was after the division. Let's think about what sched1 sees: the launder is a set of vol with an early LUID right before sx's division. The purpose: "sched1 otherwise hoists the PAN multiply ahead of this one". Hmm, "PAN multiply" = the vol multiply `(0xA0-av)*0x7F`? or the sx division? Actually vol is computed from av, and sx's `(sx+0xA0)/0x14` is the "pan" (sx reused as pan). The comment: "Both magic-multiplies write the same match_scratch, so sched1 ... always hoisted the PAN multiply first, inverting the whole tail schedule and losing the mfhi→mult hazard nop."

Two magic multiplies: vol's `(0xA0-av)*0x7F` — that's a constant multiply that may be a shift-sub, not magic. Hmm, `*0x7F` = `(x<<7)-x`, combine does that. And `/0xA0` is a magic multiply. And `/0x14` is a magic multiply. So "both magic-multiplies" = `/0xA0` (vol) and `/0x14` (pan/sx). sched1 hoisted the PAN (`/0x14`) multiply first. The launder (set of vol between) prevents that.

So the 2nd set must be at the launder position: after vol's division, before sx's division. t1 (splitting vol into mult then div) puts vol's second set at the division — which is at the same position as the original division (before sx). Does that demote the birth boost? The "birthing boost" in sched1 applies to an insn that sets a register that's live at block start? Let me look at sched.c:2469-2545.

Actually let me read the relevant gcc source to understand. sched.c priority computation.
