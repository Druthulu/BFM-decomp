// ApplySymbols.java — MIRROR the curated symbol file INTO Ghidra (rule R15 / G6), headless.
//
// WHY (P31 S78): 47 renames made through the headless MCP server (batch_rename / rename_symbol)
// did NOT survive the sentinel stop — "Save succeeded", the DB grew, the names were gone (R9 caught
// it). The curated text file `config/symbols.us.txt` is the source of truth anyway (R15), so the
// mirror is now a deterministic headless postScript: read `name = 0xADDR; // func|data`, and for every
// address inside program memory set the function's name (or create/primary a label) to the curated
// name. analyzeHeadless commits + saves on exit (the DefineFunctions.java precedent). Idempotent.
//
// Name collisions: a curated name currently held by ANOTHER address is moved first — to that
// address's own curated name when it has one (firstfile/firstfile2 4.0-vs-4.2), else to
// `<name>__at_<addr>` so nothing is silently dropped. Prints BFMAPPLY counts; verify with
// tools/ghidra_mcp_verify.sh <addr> <name> (R9).
//
// Args: <symbols file> [<symbols file> ...]   (paths relative to the CWD analyzeHeadless ran from)
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.SourceType;
import ghidra.util.exception.DuplicateNameException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.regex.*;

public class ApplySymbols extends GhidraScript {
    private final Map<Long, String> want = new TreeMap<>();
    private int renamedFn = 0, labels = 0, unchanged = 0, skipped = 0, failed = 0, moved = 0;

    @Override
    protected void run() throws Exception {
        String[] args = getScriptArgs();
        if (args == null || args.length < 1) { println("BFMAPPLY ERROR: no symbols file given"); return; }
        Pattern p = Pattern.compile("^\\s*([A-Za-z_]\\w*)\\s*=\\s*0x([0-9A-Fa-f]+)\\s*;");
        for (String path : args) {
            for (String ln : Files.readAllLines(Paths.get(path))) {
                Matcher m = p.matcher(ln);
                if (m.find()) want.put(Long.parseLong(m.group(2), 16), m.group(1));
            }
        }
        for (Map.Entry<Long, String> e : want.entrySet()) apply(e.getKey(), e.getValue(), 0);
        println("BFMAPPLY renamed_funcs=" + renamedFn + " labels=" + labels + " unchanged=" + unchanged
                + " moved_holders=" + moved + " skipped_outside_memory=" + skipped + " failed=" + failed
                + " wanted=" + want.size());
    }

    private Address addrOf(long off) {
        return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(off);
    }

    private void apply(long off, String name, int depth) {
        Address a = addrOf(off);
        if (!currentProgram.getMemory().contains(a)) { skipped++; return; }
        SymbolTable st = currentProgram.getSymbolTable();
        Function f = currentProgram.getFunctionManager().getFunctionAt(a);
        Symbol cur = f != null ? f.getSymbol() : st.getPrimarySymbol(a);
        if (cur != null && name.equals(cur.getName())) { unchanged++; return; }
        try {
            if (f != null) { f.setName(name, SourceType.USER_DEFINED); renamedFn++; }
            else { st.createLabel(a, name, SourceType.USER_DEFINED).setPrimary(); labels++; }
        } catch (DuplicateNameException dup) {
            if (depth > 3) { failed++; println("  fail @0x" + Long.toHexString(off) + " " + name + ": " + dup.getMessage()); return; }
            // the name is held elsewhere: move the holder out of the way, then retry
            for (Symbol h : st.getSymbols(name)) {
                long hoff = h.getAddress().getOffset();
                if (hoff == off) continue;
                String hwant = want.get(hoff);
                String to = (hwant != null && !hwant.equals(name)) ? hwant : name + "__at_" + Long.toHexString(hoff);
                try {
                    Function hf = currentProgram.getFunctionManager().getFunctionAt(h.getAddress());
                    if (hf != null) hf.setName(to, SourceType.USER_DEFINED); else h.setName(to, SourceType.USER_DEFINED);
                    moved++;
                    println("  moved holder of '" + name + "' @0x" + Long.toHexString(hoff) + " -> " + to);
                } catch (Exception ex) { failed++; println("  fail moving holder @0x" + Long.toHexString(hoff) + ": " + ex.getMessage()); return; }
            }
            apply(off, name, depth + 1);
        } catch (Exception ex) {
            failed++; println("  fail @0x" + Long.toHexString(off) + " " + name + ": " + ex.getMessage());
        }
    }
}
