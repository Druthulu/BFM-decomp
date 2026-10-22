---
ts: 2026-10-22T12:38:55.277Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: a16908c7d82609ecc
model: claude-opus-5-5[1m]
effort: medium
turnId: 4e94d3b6-b649-4184-9959-2cdd8b2eb53d
usage: {input: 12, cacheRead: 474062, cacheWrite: 98695, output: 2074}
---

T11 needs your decision. MiniMax is still limited to one coder at a time, and the expert wants it opened up to 4. I can't do that the way the expert asked.

**What the expert reports.** MiniMax has had 6 runs in this project, and every one hit some friction:
- commands that were refused;
- a false "outside the project" refusal on relative paths;
- blocks for reading a large file whole;
- in one run, 23 refusals from the judge while it was hitting a usage limit.

So T11 runs one coder instead of up to 10. There are 47 shards left at about 45 to 90 minutes each, which comes to about 35 to 70 hours.

**There's no switch for learning mode.** I checked the launcher (`tools/pa_ext.py`). Learning mode ends only when a model's latest finished run comes back clean, and no setting overrides that. The only other way would be to edit the run records so a run looks clean. That would hide the friction instead of fixing it, so I won't do it.

**Why it keeps resetting.** A run doesn't count as clean if it hits any friction, if the judge learns any new rule during it, or if the expert adds a note after it. The expert has added a note after almost every run, so its own fixes keep MiniMax in learning mode. The 3 notes so far already cover the main causes: scratch files in `/tmp`, absolute paths, and whole reads of large files. The usage-limit refusals came from a spell on the subscription side, not from MiniMax.

**My recommendation.** Keep the one lane, and tell the expert to add a note only for a genuinely new lesson. Small friction would go in its log instead. Then the next well-behaved run counts as clean and MiniMax gets its lanes on its own. I'd also report two things as PA3 bugs: the false refusal on relative paths, and the fact that the expert's own notes reset learning mode.

The other route is to add in-house Opus coders beside MiniMax. That's faster, but it breaks your MiniMax-only rule for cracking. Pick an option in the picker.
