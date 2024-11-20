# Assembly Project: Two-Pass Assembler

## Overview
This project implements a two-pass assembler for a simulated computer. The assembler processes assembly code in two main stages:
1. **Pre-Assembly**: Expands macros and checks syntax errors.
2. **Two-Pass Assembly**:
   - **First Pass**: Builds the symbol table.
   - **Second Pass**: Encodes instructions and generates output files.

---

## Pre-Assembly Stage
In this stage, the assembler:
1. **Expands Macros**:
   - Detects and replaces macro calls with their respective definitions.
   - Stores the expanded code in a new source file (file.am).
2. **Error Checking**:
   - Ensures macros are properly defined and terminated.
   - Validates that no macro name conflicts with operation codes or labels.

### Errors Detected:
- Missing macro termination (`endmacr`).
- Redefinition of an existing macro.
- Misuse of reserved names as macro identifiers.

### Output:
- **Expanded Source File**: Contains the assembly code with all macros expanded and ready for the next stage.

---

## First Pass
The first pass processes the expanded source file to:
1. **Identify Symbols**:
   - Recognizes labels and stores them with their memory addresses in a **symbol table**.
2. **Allocate Memory**:
   - Calculates memory requirements for data and instructions.

### Tasks:
- Validates the syntax of all labels and directives.
- Updates instruction and data counters (`IC` and `DC`).
- Detects undefined or duplicate labels.

### Errors Detected:
- Undefined labels.
- Duplicate label definitions.

### Output:
- **Symbol Table**: A mapping of labels to memory addresses.
- **Intermediate Data**: Instruction and data counters for the second pass.

---

## Second Pass
The second pass uses the symbol table to:
1. **Generate Machine Code**:
   - Encodes instructions into binary format.
   - Resolves label references to memory addresses.
2. **Handle Errors**:
   - Flags unresolved labels or invalid operands.

### Tasks:
- Replaces symbolic labels with their respective memory addresses.
- Generates binary code for all instructions and directives.

### Errors Detected:
- Invalid addressing modes.
- Unresolved external references.

---

## Output Files
The assembler generates the following files:

1. **Machine Code File (`.ob`)**:
   - Contains binary machine code for the program.
   - Includes both instructions and data.

2. **External Labels File (`.ext`)**:
   - Lists all external labels referenced in the code, along with their addresses.

3. **Entry Points File (`.ent`)**:
   - Lists all entry labels and their addresses.

4. **Error Logs**:
   - If errors are detected, detailed error messages are provided instead of output files.
