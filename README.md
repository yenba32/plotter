# plotter


## G Code documentation

- `G1 X<decimal> Y<decimal> A<int>`: Move the cursor to position `X`, `Y`. The `A` param can be ignored. The numbers are specified only up to 2 digits after decimal point. It might be better to represent them as integer.
- `G28`: Move to origin
- `M10`: Report initial status. The controller is supposed to reply with:

    `M10 XY 380 310 0.00 0.00 A0 B0 H0 S80 U160 D90`

  in which:

    - `XY`: name?
    - `380 310`: size of the printable area
    - `0.00 0.00`: XY origin (or current cursor position?)
    - `A0 B0 H0 S80`: **not sure**
    - `U160`: `M1` param for the up command
    - `D90`: `M1` param for the down command

- `M1 <int>`: Set pen position
    - `M1 90`: Pen down
    - `M1 160`: Pen up
- `M4 <byte>`: Set laser pointer power

References:

https://reprap.org/wiki/G-code
