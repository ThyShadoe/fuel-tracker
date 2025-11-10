# Fuel Efficiency Tracker

## Bug Tracker

### Syntax Errors

### Runtime Errors

#### 2025-11-07_RUNTIME_ERR_1

PRIORITY : High

STATUS   : Resolved

ERROR    : `/usr/include/c++/15.2.1/bits/stl_vector.h:1263: constexpr std::vector< <template-parameter-1-1>, <template-parameter-1-2> >::reference std::vector< <template-parameter-1-1>, <template-parameter-1-2> >::operator[](size_type) [with _Tp = FuelEntry; _Alloc = std::allocator<FuelEntry>; reference = FuelEntry&; size_type = long unsigned int]: Assertion '__n < this->size()' failed.`

FIX      : changed value in for loop from `int = 0` to `int = 1`

### Logical Errors

#### 2025-11-07_LOGIC_ERR_0

PRIORITY : High

STATUS   : Resolved

ERROR    : Date input is skipped whenever entering a new fuel entry.

FIX      : Added `cin.ignore` for main menu input.

#### 2025-11-07_LOGIC_ERR_1

PRIORITY : Medium

STATUS   : Unresolved

ERROR    : Loop error when you enter any letter to a double input (ex. Odometer Reading).

FIX      : N/A
