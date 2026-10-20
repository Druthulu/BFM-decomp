---
ts: 2026-10-17T17:24:30.229Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: af409a99e99c8a1de
model: claude-opus-5-5[1m]
effort: medium
turnId: c8240978-1a00-4d67-b18c-1013d63f9b42
---
I'm comparing the priority scores for w and ot based on their reference counts and lifetimes, trying to find a tweak to reference counts that would push ot's priority above w's.

Since w0 is copied into w, cse likely treats them as equivalent and may substitute w0 for w in later uses depending on which pseudo it picks as canonical—so shifting where the `w = w0` assignment happens, or increasing ot's reference count instead, could be the fix worth testing.
