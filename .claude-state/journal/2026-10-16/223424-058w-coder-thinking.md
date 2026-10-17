---
ts: 2026-10-17T04:34:24.052Z
session: a4742bc1-12ac-4649-ab77-694e7315677f
agentId: a5605ba96cc5ff027
model: claude-opus-5-5[1m]
effort: medium
turnId: 0c792287-f11f-4848-8566-c39a9bb058a0
---
My plan is to first make all the ov_SC07 declaration and call edits, verifying each binary byte-for-byte, then commit and run share_body with apply, extend, and retry-excepted flags scoped to the specific target so it extends and drops the exception row if sharing succeeds. But I'm reconsidering since the brief calls for applying each item through restruct rung D, and the decl changes using restruct with callee and signature only cover declarations within the header's binaries.

Using restruct's --with flag to pass the four overlay files would let the tool rewrite their decls, but it would also rewrite decls across all 132 includer TUs' binaries, including ones with short calls that would break compilation and get refused -- unless I also fix calls in all those files, which spans way beyond the ov_SC07-only scope I'm constrained to. This means restruct would improperly touch non-SC07 files through the header's includer relationships, so I need to find a way to limit its reach, maybe through a per-TU flag.

So I'm concluding restruct isn't viable here within the given constraints -- I'll fall back to hand edits verified by make check per binary, treating it as rung-equivalent to the earlier precedent and flagging it as a deviation. Since the "one ANSI prototype everywhere" goal can't be fully satisfied within the ov_SC07_* constraint anyway (other overlays' K&R sites remain untouched), I'll scope the work to ov_SC07_* and report the rest as a finding, now inventorying which specific files across ov_SC07_000 through 011 and the shared headers are affected.

Those shared headers are included across multiple overlays, and since BCC0 is explicitly named in the brief, I need to check which K&R call sites live in ov_SC07_000's file versus in the headers' other includers before deciding how to proceed.
