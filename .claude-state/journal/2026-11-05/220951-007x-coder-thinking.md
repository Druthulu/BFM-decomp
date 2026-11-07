---
ts: 2026-11-06T05:09:51Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cG22
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_v56C8FuiJadtU5p9JWPz
---
Now I understand the item. Kinds: launder,pin. Need to remove the pin ($3 raw, $2 t) and the launder asm, and get score 0.

Wait: the pin is `register s32 raw __asm__("$3")` and `register s32 t __asm__("$2")` — these are the row kinds. Also "levers of other kinds the def already had (pins under other causes) may stay, never added". Hmm, these are the row kinds, so they must go.

Also CAST_SIGN — is that a lever? Let me check what CAST_SIGN does. It's probably a macro in include/. Let me check.

Let me first set up the item dir: copy orig.c, and figure out what the base body scores with levers intact.

Steps:
1. Copy src function to orig.c.
2. Run dt.sh on orig.c to see baseline score (should be 0 presumably since src is matched... actually src body presumably scores 0 with levers).
3. Write win.c lever-free and iterate.

Let me check CAST_SIGN definition.
