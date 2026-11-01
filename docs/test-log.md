# Test Log (fill in with your own measurements)

This table is a template. Record real results from your own circuit; do not copy numbers from elsewhere.

## Reference: typical HC-SR501 datasheet values

These are manufacturer-style typical figures for comparison, **not your measurements**. Check the datasheet of your own module.

| Parameter | Typical value |
|-----------|---------------|
| Supply voltage | 4.5V - 20V (5V on Arduino) |
| Detection range | about 3 - 7 m (adjustable with the sensitivity pot) |
| Detection angle | about 100 - 120 degrees |
| Output hold time | about 5 s - 300 s (adjustable with the time-delay pot) |
| Warm-up time | about 30 - 60 s after power-on |

## Setup

- Date:
- Arduino board:
- PIR module and sensitivity / time-delay knob positions:
- Power source:
- Location (indoor / outdoor, temperature, lighting):

## Detection range test

Walk toward the sensor at a normal pace from the given distance. Repeat each distance 5 times.

| Distance (m) | Trials | Detected | Not detected | Notes |
|--------------|--------|----------|--------------|-------|
| 1 | 5 | | | |
| 2 | 5 | | | |
| 3 | 5 | | | |
| 4 | 5 | | | |
| 5 | 5 | | | |
| 6 | 5 | | | |
| 7 | 5 | | | |

## Response time

Time from the start of movement in front of the sensor to the red LED turning on (use a phone video and count frames, or the Serial Monitor).

| Trial | Response time (s) |
|-------|-------------------|
| 1 | |
| 2 | |
| 3 | |
| 4 | |
| 5 | |
| Average | |

## False alarm check

Leave the system running with nobody in front of it.

| Duration | Condition (wind, sunlight, pets...) | False alarms |
|----------|--------------------------------------|--------------|
| | | |

## Conclusion

Write 2-3 sentences summarizing the maximum reliable range, the average response time, and what caused any false alarms.
