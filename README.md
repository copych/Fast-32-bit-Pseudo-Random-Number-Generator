# Fast-32-bit-Pseudo-Random-Number-Generator
Fast 32 bit Pseudo Random Number Generator (PRNG) implements XORSHIFT, LCG (Linear congruential generator) and LFSR(Linear-feedback shift register) algorithms
The code is adapted to Arduino, but can easily ported to any platform, using specific functions instead of micros() etc. (non-critical).

Usage:
```
MyRand Rnd;

uint32_t i1 = Rnd.getInt(); // random [0, 4294967295]
uint32_t i2 = Rnd.getInt(4096); // random integer [0, 4095)

float r1 = Rnd.getFloat(); // random float (0.0, 1.0)
float r2 = Rnd.getFloat(2.0f); // random float (0.0, 2.0)

float r3 = Rnd.getFloatInRange(1.0f, 2.0f); //random float belonging (1.0, 2.0)
float r4 = Rnd.getFloatSpread(1.0f, 0.5f); // random spread 1.0 +/- 0.5  (0.5, 1.5) 

bool succsess = Rnd.tryChance(0.3f); // 30% success

```
