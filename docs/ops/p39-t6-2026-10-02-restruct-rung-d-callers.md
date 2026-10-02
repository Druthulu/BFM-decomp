# §P39 T6 — 2026-10-02: restruct rung D caller-only units, alias defs, shared-header scope

- `restruct.py --apply --rung D --callee <c> --signature "<sig>" [--all-defs] [--tu TU]`: finds alias definitions (`aF<addr> __asm__("func_<addr>")`) by their C name; a def or decl file already spelled with the signature is not edited or judged (caller-only unit: the definition stays, every lying caller declaration is redrawn to it, judged as one unit, C0508).
- A def in a shared header (`src/shared/**/*.h`) is scoped to its includers' full binary lists (`tu_aliases`: ov_SC01_005 sources also build ov_SC01_006), not the binaries named by includer paths.
- `decl_sites` skips asm-label declarations (`!FAKE` barrier decls of `aF8014C4AC` were respelled before the fix).
- Lying declarations that stay: `config/lying_exceptions.tsv` (callee, def_file, kind, cause, task), keyed as `type_census --check-casts` keys them.
