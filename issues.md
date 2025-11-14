# BUG TRACKER - ThyShadoe/fuel-tracker

## SYNTAX ERROR

| CHECK | INFO |
| ------------- | -------------- |
| PRIORITY | Low |
| STATUS   | Fixed |
| ERROR    | Functions were unable to work as expected  |
| FIX      | Removed misplaced `}` symbol |

## RUNTIME ERROR

### 2025-11-07_RUNTIME_ERR_1

| CHECK | INFO |
| ------------- | -------------- |
| PRIORITY | High |
| STATUS   | Fixed |
| ERROR    | Crashed when going to `[3] Generate Report`  |
| FIX      | Changed incorrect value in for loop |


## LOGICAL ERROR

### 2025-11-07_LOGIC_ERR_0

| CHECK | INFO |
| ------------- | -------------- |
| PRIORITY | High |
| STATUS   | Fixed |
| ERROR    | Date input is skipped when entering new fuel entry |
| FIX      | Add `cin.ignore` in main menu input

### 2025-11-07_LOGIC_ERR_1

| CHECK | INFO |
| ------------- | -------------- |
| PRIORITY | High |
| STATUS   | Fixed |
| ERROR    | Permaloop when entering an invalid value in input field |
| FIX      | Add validation function in every input field.

### 2025-11-14_LOGIC_ERR_2

| CHECK | INFO |
| ------------- | -------------- |
| PRIORITY | High |
| STATUS   | Fixed |
| ERROR    | Date input would get stuck with incorrect value |
| FIX      | Removed `cin.clear()` and `cin.ignore()` in validation |

