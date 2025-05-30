# Test Suite Structure (PlatformIO compatible)

## Organization

All test files must be placed directly in the `test/` folder.
To categorize tests, use a naming convention such as:

* `test_unit_<feature>.cpp` : Unit tests for individual components/features
* `test_integration_<feature>.cpp` : Integration tests for system-level scenarios

**Do not use subfolders. PlatformIO will only discover and run tests in the `test/` directory.**

## Example

* `test_unit_boot_notification.cpp`    → Unit test for BootNotification feature
* `test_integration_system.cpp`        → System integration test

## Test File Guidelines

* Only one file (the test runner) in the `test/` folder should define `setup()` and `loop()` functions.
* All other test files must export only their test functions (e.g., `void test_<feature>()`).
* The test runner calls all relevant test functions via `RUN_TEST()` in `setup()`.

## How to Run Tests

```sh
pio test
```

> By default, `pio test` will run tests for all environments defined in `platformio.ini`.
> To run tests for a specific environment:
>
> ```sh
> pio test -e esp32doit-devkit-v1
> ```

## Adding a New Test

1. Create a new file in the `test/` folder using the appropriate naming convention.
2. Implement your test function(s) (do not add another `setup()` or `loop()`).
3. Add a `RUN_TEST()` call in the test runner to execute your new test.
4. Run all tests with `pio test`.

## Best Practices

* Keep test functions short and focused on a single behavior.
* Group related tests in the same file when relevant.
* Document any complex test logic inline for maintainability.
