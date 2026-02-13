# Arm Sequence & Armed-State Flow (State Diagram)

```mermaid
stateDiagram-v2
  [*] --> Manual

  Manual --> ArmRequest : arm cmd / switch ON
  ArmRequest --> ArmBlocked : safety enabled & manual pot >= threshold
  ArmBlocked --> Manual : arm fails

  ArmRequest --> Armed : safety OK
  Armed: set servo=pidStartPosition
  Armed: pid reset (integral/lastError)
  Armed: apply PID floor/ceiling
  Armed: start logging (50 Hz)
  Armed: BLE TX suppressed
  Armed: LED solid ON

  Armed --> OverridePending : manual pot >= threshold
  OverridePending --> Armed : pot still >= threshold
  OverridePending --> Manual : pot < recovery (disarm)

  Armed --> Manual : disarm cmd / switch OFF

  Manual: servo follows manual pot
  Manual: LED flashing
  Manual: logging stopped
```

---

# Armed Loop Timing (every 3 ms)

```mermaid
flowchart TD
  A[Tick @ 3ms] --> B[Read RPM + pots + arm switch]
  B --> C[Update safety state]
  C -->|override recovered| D[Disarm -> Manual]
  C -->|else| E[Fixed-step PID compute]
  E --> F[Clamp output, apply calibration]
  F --> G[Servo update]
  G --> H[Log sample if due (50 Hz)]
  H --> A
```
