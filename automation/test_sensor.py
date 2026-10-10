import unittest

from sensor_runner import parse_sensor_output, run_simulator


class SensorSimulatorTests(unittest.TestCase):
    def test_normal_mode(self):
        output = run_simulator("normal")
        samples = parse_sensor_output(output)

        self.assertEqual(len(samples), 10)

        expected_ids = [
            str(sample_id)
            for sample_id in range(1, 11)
        ]

        actual_ids = [
            sample["sample_id"]
            for sample in samples
        ]

        self.assertEqual(actual_ids, expected_ids)

        for sample in samples:
            self.assertEqual(sample["status"], "OK")

            temperature_c = float(sample["temperature_c"])

            self.assertGreaterEqual(temperature_c, 20.0)
            self.assertLessEqual(temperature_c, 30.0)

    def test_range_mode(self):
        output = run_simulator("range")
        samples = parse_sensor_output(output)

        self.assertEqual(len(samples), 10)

        fault_samples = [
            sample
            for sample in samples
            if sample["status"] == "RANGE_FAULT"
        ]

        self.assertEqual(len(fault_samples), 1)

        fault = fault_samples[0]

        self.assertEqual(fault["sample_id"], "5")
        self.assertEqual(float(fault["temperature_c"]), 85.0)

    def test_invalid_mode(self):
        output = run_simulator("invalid")
        samples = parse_sensor_output(output)

        self.assertEqual(len(samples), 10)

        invalid_samples = [
            sample
            for sample in samples
            if sample["status"] == "INVALID_DATA"
        ]

        self.assertEqual(len(invalid_samples), 1)

        invalid_sample = invalid_samples[0]

        self.assertEqual(invalid_sample["sample_id"], "5")
        self.assertEqual(invalid_sample["temperature_c"], "INVALID")


    def test_frozen_mode(self):
        output = run_simulator("frozen")
        samples = parse_sensor_output(output)

        self.assertEqual(len(samples), 10)

        frozen_samples = [
            sample
            for sample in samples
            if sample["status"] == "FROZEN_FAULT"
        ]

        frozen_ids = [
            sample["sample_id"]
            for sample in frozen_samples
        ]

        frozen_temperatures = [
            float(sample["temperature_c"])
            for sample in frozen_samples
        ]

        self.assertEqual(frozen_ids, ["5", "6", "7"])
        self.assertEqual(frozen_temperatures, [25.0, 25.0, 25.0])

    def test_timeout_mode(self):
        output = run_simulator("timeout")
        samples = parse_sensor_output(output)

        self.assertEqual(len(samples), 9)

        actual_ids = [
            sample["sample_id"]
            for sample in samples
        ]

        expected_ids = [
            "1", "2", "3", "4",
            "6", "7", "8", "9", "10",
        ]

        self.assertNotIn("5", actual_ids)
        self.assertEqual(actual_ids, expected_ids)


if __name__ == "__main__":
    unittest.main()