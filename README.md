# Embedded Sensor Test Automation

[![Embedded Sensor CI](https://github.com/karanm2504/Embedded-sensor-Test-automation/actions/workflows/ci.yml/badge.svg)](https://github.com/karanm2504/Embedded-sensor-Test-automation/actions/workflows/ci.yml)

An embedded C sensor simulator with Python-based automated testing, fault injection, test reporting, and continuous integration using GitHub Actions.

## Project Overview

This project simulates an embedded temperature sensor in C. It produces sensor samples in CSV format and supports multiple operating and fault modes.

A Python automation framework executes the simulator, parses its output, validates the sensor behaviour, and generates a test report. GitHub Actions automatically builds and tests the project after every push or pull request.

## Features

- Embedded sensor simulation written in C
- Deterministic temperature sample generation
- CSV-formatted simulator output
- Command-line selection of operating modes
- Fault injection for abnormal sensor conditions
- Python-based process execution and output parsing
- Automated tests using Python `unittest`
- Text-based test report generation
- Build and test automation using Make
- Continuous integration using GitHub Actions

## Sensor Modes

| Mode | Description | Expected Result |
|------|-------------|-----------------|
| `normal` | Generates valid temperature samples | All samples have `OK` status |
| `range` | Injects an out-of-range temperature at sample 5 | Sample 5 reports `RANGE_FAULT` |
| `invalid` | Injects invalid sensor data at sample 5 | Sample 5 reports `INVALID_DATA` |
| `frozen` | Repeats the same temperature value | Automation detects frozen sensor behaviour |
| `timeout` | Simulates a sensor communication delay | Automation detects a timeout |


## Architecture

```text
C Sensor Simulator
        |
        | CSV output through stdout
        v
Python Sensor Runner
        |
        | Parsed sensor samples
        v
Automated Unit Tests
        |
        | Test results
        v
Text Test Report
        |
        v
GitHub Actions CI
```

The C application represents the embedded firmware component. Python acts as the external test system that executes the firmware simulator, reads its output, and verifies its behaviour.

## Project Structure

```text
embedded-sensor-test-automation/
├── .github/
│   └── workflows/
│       └── ci.yml
├── automation/
│   ├── run_tests.py
│   ├── sensor_runner.py
│   └── test_sensor.py
├── firmware_sim/
│   └── src/
│       └── sensor_simulator.c
├── .gitignore
├── Makefile
└── README.md
```

## Requirements

- Linux or Windows Subsystem for Linux (WSL)
- GCC compiler
- GNU Make
- Python 3
- Git

The Python automation uses only the Python standard library, so no additional packages need to be installed.

## Clone the Repository

```bash
git clone https://github.com/karanm2504/Embedded-sensor-Test-automation.git
cd Embedded-sensor-Test-automation
```

## Build the Simulator

```bash
make
```

This compiles the C source code and creates:

```text
build/sensor_simulator
```

## Run the Simulator

Run the normal operating mode:

```bash
make run
```

Run individual fault modes:

```bash
./build/sensor_simulator normal
./build/sensor_simulator range
./build/sensor_simulator invalid
./build/sensor_simulator frozen
./build/sensor_simulator timeout
```

Each mode produces CSV-formatted output containing a sample ID, sensor value, and status.

Example range-fault output:

```text
sample_id,temperature_c,status
...
5,85.00,RANGE_FAULT
...
```
## Run Automated Tests

```bash
make test
```

The automated test suite validates:

1. Normal sensor operation
2. Out-of-range fault detection
3. Invalid sensor data detection
4. Frozen sensor detection
5. Sensor timeout handling

## Generate a Test Report

```bash
make report
```

The generated report is stored at:

```text
reports/test_report.txt
```

View the report in the terminal:

```bash
cat reports/test_report.txt
```

## Clean Generated Files

```bash
make clean
```

This removes generated build files, Python cache files, and test reports.

## Continuous Integration

The GitHub Actions workflow automatically runs when code is:

- Pushed to the `main` branch
- Submitted through a pull request to the `main` branch

The CI pipeline performs the following steps:

1. Checks out the repository
2. Sets up Python
3. displays the tool versions
4. Builds the C simulator
5. Runs the Python test suite
6. Generates the test report
7. Uploads the report as a downloadable GitHub Actions artifact

The report-generation and artifact-upload steps use `if: always()`, allowing diagnostic test results to be preserved even when a test fails.

## Skills Demonstrated

- Embedded C development
- Command-line argument handling
- Sensor simulation and fault injection
- Defensive input and output handling
- Python test automation
- Process execution using `subprocess`
- CSV output parsing
- Unit testing with `unittest`
- Test report generation
- Makefile-based build automation
- Linux command-line development
- Git and GitHub version control
- Continuous integration with GitHub Actions

## Future Improvements

- Add configurable sample count and fault position
- Add more sensor types such as pressure and humidity
- Export test results in JSON or JUnit XML format
- Add code coverage reporting
- Add static analysis using tools such as `cppcheck`
- Add memory analysis using Valgrind
- Run tests with multiple compiler versions
- Connect the automation framework to real embedded hardware through UART
