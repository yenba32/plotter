# plotter


## G Code documentation

- `G1 X<decimal> Y<decimal> A<int>`: Move the cursor to position `X`, `Y`. The `A` param can be ignored. The numbers are specified only up to 2 digits after decimal point. It might be better to represent them as integer.
- `G28`: Move to origin
- `M10`: **Unknown**
- `M1 <int>`: custom command
    - `M1 90`: Pen down
    - `M1 160`: Pen up
- `M4 <byte>`: Set laser pointer power

References:

https://reprap.org/wiki/G-code
