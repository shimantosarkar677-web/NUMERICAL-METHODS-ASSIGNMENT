# Van der Pol Oscillator: Implicit Numerical Solver

This C++ program implements a numerical solution for the **Van der Pol oscillator**, a non-conservative oscillator with non-linear damping. The system is a classic example of a "stiff" differential equation, particularly as the damping parameter $\mu$ increases.

## The Mathematical Model

The Van der Pol oscillator is governed by the second-order differential equation:

$$\frac{d^2x}{dt^2} - \mu(1 - x^2)\frac{dx}{dt} + x = 0$$

To solve this numerically, the code reduces it to a system of two first-order ODEs:
1.  $\frac{dy_1}{dt} = y_2$
2.  $\frac{dy_2}{dt} = \mu(1 - y_1^2)y_2 - y_1$



## Numerical Method

### Backward Euler (Implicit)
Because the parameter $\mu$ is set to $100$, the system exhibits high stiffness. Simple explicit methods (like Forward Euler) would require an impractically small time step to avoid divergence. This solver uses the **Backward Euler Method**, which is unconditionally stable:

$$y_{n+1} = y_n + h \cdot f(y_{n+1})$$

### Newton-Raphson Iteration
Since the method is implicit, $y_{n+1}$ is solved root-finding problem for each step:
$$G(y_{n+1}) = y_{n+1} - y_n - h \cdot f(y_{n+1}) = 0$$

The code calculates the **Jacobian Matrix** of the system to perform Newton-Raphson iterations, ensuring convergence even with the non-linear damping term.

## Code Components

| Component | Description |
| :--- | :--- |
| `Vector2` | Structure to store state variables $y_1$ (position) and $y_2$ (velocity). |
| `getJacobian` | Computes the partial derivatives of the system for the Newton solver. |
| `solveImplicitStep` | Performs the Newton-Raphson iteration until a tolerance of $10^{-8}$ is met. |
| `main` | Sets initial conditions $(2.0, 0.0)$ and iterates through time. |

## How to Build and Run

### Compilation
Use any standard C++ compiler (C++11 or later recommended):
```bash
g++ -O3 main.cpp -o vanderpol
```
## Configuration

The simulation parameters can be adjusted directly in the source code to observe different physical behaviors:

| Parameter | Default Value | Description |
| :--- | :--- | :--- |
| `MU` | `100.0` | The damping coefficient ($\mu$). Controls the non-linearity of the system. |
| `h` | `0.01` | The time step size. Smaller values increase precision but require more computation. |
| `t_end` | `1.0` | The total simulation duration (seconds). |
| `tol` | `1e-8` | The convergence tolerance for the Newton-Raphson iteration. |

### Understanding the Effect of $\mu$
The behavior of the Van der Pol oscillator changes drastically based on the value of `MU`:
* **Small $\mu$ ($\mu \approx 0$):** The system behaves like a simple harmonic oscillator (nearly sinusoidal).
* **Large $\mu$ ($\mu \gg 1$):** The system becomes "stiff" and exhibits **relaxation oscillations**, characterized by sudden jumps in state variables.



### Modifying the Solver
To change the initial state or simulation length, locate the following block in `main()`:

```cpp
double t = 0.0;
double t_end = 1.0; // Increase this to see more cycles
double h = 0.01;

Vector2 y = {2.0, 0.0}; // Initial position and velocity

```
## Output

The program generates a tab-separated data stream to the console. Each row represents a specific state of the oscillator in time.

| Column | Unit | Description |
| :--- | :--- | :--- |
| **Time** | seconds | The elapsed simulation time ($t$). |
| **Y1** | displacement | The position of the oscillator ($x$). |
| **Y2** | velocity | The first derivative of position ($\dot{x}$). |

### Sample Data Format
```text
Time            Y1              Y2
------------------------------------
0.000000        2.000000        0.000000
0.010000        1.999600        -0.039988
0.020000        1.998411        -0.079919
...
