# Outreach: the tools announcement (post-flip)

> **Where:** the decomp community Discord's tools channel, and/or a row on the Decompedia (decomp.wiki) tools page.
> **When:** after the flip, once `github.com/Druthulu/xsig` has its topics and the README's "Tools from this project" section is
> live. **Who:** Drew, in his own voice; edit freely. Written the way a developer posts, no code spans, no AI acknowledgement
> (rule candidate (j), S89).

**Discord post:**

```
Made a small tool while doing the Brave Fencer Musashi decomp that might be useful to other PS1 projects: xsig
(https://github.com/Druthulu/xsig). It hashes functions with the relocated fields masked out, so the same function at
two different link addresses gets the same signature. We used it to find shared code across overlays (2,220 groups in
BFM) and to check other games: against Xenogears, Vagrant Story and Tomba it found 103 shared functions, all PsyQ
library code, so mostly it's good for spotting library functions and shared overlay code. Stdlib only, MIT, has tests.
The full decomp is at https://github.com/Druthulu/BFM-decomp if anyone's curious, everything's matched.

Next step for it is going past exact matches: try the 1:1 first, then widen to same-shape functions (registers and
immediates masked, then same structure) and report which tier matched and what differs, so it also finds near-copies
across overlays and across games, not just library code. That's the v2 I'm starting on.
```

**Decompedia tools-page row (if the page takes rows):** name xsig, language Python (stdlib), license MIT, platform MIPS /
PlayStation-era, one line: "relocation-masked function signatures for finding shared code across overlays and across games",
link to the repo.

**The v2 sentence rests on** `docs/gen3-handoff.md` §7 (xsig v2, recorded 2026-09-08): 1-to-1 first, then the sequence tier, the
structural family and atlas cousins, returning the matched tier and the difference — the in-tree pieces exist; the port is the work.
No date is promised in the post.

**Facts the post rests on:** `tools/xsig/README.md` (the worked example: 103 hits across three games, all library; 126 against
Tomba with one 19-instruction non-library HIGH), `config/dedup.us.yaml` (2,220 groups), the E4 log entry (8/8 tests).
