Pull-up and pull-down resistors are electronic components that help set the default state of an input pin on a circuit.
 They are not special types of resistors, but regular resistors used in a specific way.

Pull-up resistor: This one connects an input pin to the positive power supply (usually 3.3V or 5V) in a circuit.
* When no external signal is applied to the pin, the resistor provides a small current path that pulls the voltage on the pin up to a logical "high" level. This ensures the circuit has a defined state (high) when inactive.

Pull-down resistor: Works similarly to a pull-up resistor, but in the opposite direction.
* It connects the input pin to ground (0V). When no external signal is present, the resistor pulls the voltage on the pin down to a logical "low" 

INPUT\_PULLUP is an option used in programming microcontrollers, specifically in the pinMode function, to configure a digital pin as an input and activate an internal pull-up resistor on that pin.

Words of the smart Gemini.
