import io
import sys
import unittest
from datetime import datetime
from pathlib import Path


PROJECT_ROOT = Path(__file__).resolve().parent.parent
AUTOMATION_DIR = PROJECT_ROOT / "automation"
REPORT_DIR = PROJECT_ROOT / "reports"
REPORT_FILE = REPORT_DIR / "test_report.txt"

def main():
    test_suite = unittest.defaultTestLoader.discover(
        start_dir=str(AUTOMATION_DIR),
        pattern="test_*.py",
    )

    output_buffer = io.StringIO()

    test_runner = unittest.TextTestRunner(
        stream=output_buffer,
        verbosity=2,
    )

    start_time = datetime.now()
    test_result = test_runner.run(test_suite)
    end_time = datetime.now()

    duration_seconds = (end_time - start_time).total_seconds()
    final_status = "PASS" if test_result.wasSuccessful() else "FAIL"

    REPORT_DIR.mkdir(parents=True, exist_ok=True)

    report_text = (
        "Embedded Sensor Automation Test Report\n"
        "======================================\n"
        f"Generated: {end_time.isoformat(timespec='seconds')}\n"
        f"Duration: {duration_seconds:.3f} seconds\n"
        f"Tests run: {test_result.testsRun}\n"
        f"Failures: {len(test_result.failures)}\n"
        f"Errors: {len(test_result.errors)}\n"
        f"Final result: {final_status}\n\n"
        f"{output_buffer.getvalue()}"
    )
    REPORT_FILE.write_text(report_text, encoding="utf-8")

    print(report_text)
    print(f"Report saved to: {REPORT_FILE}")

    return 0 if test_result.wasSuccessful() else 1

if __name__ == "__main__":
    sys.exit(main())