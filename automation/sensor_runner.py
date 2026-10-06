import csv
import subprocess
from pathlib import Path


PROJECT_ROOT = Path(__file__).resolve().parent.parent
SIMULATOR_PATH = PROJECT_ROOT / "build" / "sensor_simulator"


def run_simulator(mode: str) -> str:
    result = subprocess.run(
        [str(SIMULATOR_PATH), mode],
        capture_output=True,
        text=True,
        check=True,
        timeout=5,
    )

    return result.stdout

def parse_sensor_output(output: str) -> list[dict[str, str]]:
    reader = csv.DictReader(output.splitlines())
    return list(reader)


if __name__ == "__main__":
    output = run_simulator("normal")
    samples = parse_sensor_output(output)

    for sample in samples:
        print(sample)