---
ts: 2026-11-06T16:37:44Z
session: 252d32b5-eb3b-4ca8-9931-8e47bb99cd41
agentId: ext-T11.cO05x
model: deepseek/deepseek-v4.1-flash-1017
effort: high
turnId: msg_7f9jta2JyKTIUPEB8fNI
---
Now the dump matches the target (modulo maspsx's move vs addu — the build shows `move a1,a0` because maspsx converts `addu $5,$4,$0` to `move`? Actually the target object has `move a1,a0`; maspsx may canonicalize. Fine — instruction sequence is equivalent.)

Now dump c1 (pointer self, comment-free).
