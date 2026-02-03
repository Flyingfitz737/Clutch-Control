# Feed-Forward Feature Implementation Details

## Non-Volatile Memory Implementation
The feed-forward feature utilizes non-volatile memory through the `Preferences` class to persist settings across sessions. This allows parameters to be saved and retrieved, ensuring user-specified values remain intact even after the device is powered off.

## Commands to Control Feed-Forward
1. **Enable/Disable Feed-Forward:**  Use the command `setFeedForwardEnabled(true)` to enable the feature or `setFeedForwardEnabled(false)` to disable it.
2. **Set Fixed Value:** To set the fixed value for feed-forward, use the command `setFeedForwardValue(value)`, where `value` is a float representing the desired feed-forward term.
3. **Query State:** To check the current state of the feed-forward feature, use `isFeedForwardEnabled()`, which returns a boolean indicating whether the feature is active.
4. **Get Fixed Value:** To retrieve the fixed value for feed-forward, use the command `getFeedForwardValue()`, returning the currently set float value.

## Saving and Reading Feed-Forward Parameters in `setup()`
In the `setup()` function, parameters for feed-forward can be saved and retrieved as follows:
1. **Saving Parameters:**  Use `Preferences preferences; preferences.begin("feedForward", false); preferences.putFloat("fixedValue", feedForwardValue); preferences.end();` to save the desired fixed value.
2. **Reading Parameters:** To read the parameters, use `Preferences preferences; preferences.begin("feedForward", true); feedForwardValue = preferences.getFloat("fixedValue", defaultValue); preferences.end();`. This reads the fixed value, with `defaultValue` being returned if the value is not previously set.

## Integration into the PID Control Loop
The feed-forward feature is integrated into the PID control loop by adding the fixed-value term to the output. This can be implemented as follows:  
```cpp
float feedForwardOutput = getFeedForwardValue();
float pidOutput = pidController.update();  
output = pidOutput + feedForwardOutput;
```  This modification ensures that the feed-forward term is consistently applied as an additive component of the PID output, enhancing the responsiveness of the control system based on predefined conditions.