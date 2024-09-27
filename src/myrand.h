/**
   FAST Pseudo-random generator

* ESP32 performance benchmark
Float Random 	      49.442230 MOP/S   	CPI=1.048779        // XORSHIFT
Float Random 	      62.403713 MOP/S   	CPI=1.088256        // LFSR
Float Random 	      84.615791 MOP/S   	CPI=1.079679        // CONGRUENT
* compare
Integer Addition 	   237.953598 MOP/S   	CPI=1.007862
Integer Multiply 	   237.882843 MOP/S   	CPI=1.008086
Integer Division 	   119.087494 MOP/S   	CPI=2.012431
Float Addition  	   237.865158 MOP/S   	CPI=1.008107
Float Multiply  	   237.882843 MOP/S   	CPI=1.008095
Float Division 	     4.732930 MOP/S     CPI=1.442258
*/

#define XORSHIFT 1
#define LFSR 2
#define CONGRUENT 3

#define MYRAND_ALGO XORSHIFT
//#define MYRAND_ALGO LFSR
//#define MYRAND_ALGO CONGRUENT

#define MYRAND_TYPE uint32_t

class MyRand {

public:
  MyRand(){setSeed();};
  ~MyRand(){};
  
  inline MYRAND_TYPE getInt() {
    _myRandomState = next(_myRandomState);
    return _myRandomState;
  }

  inline MYRAND_TYPE getInt(MYRAND_TYPE max) {
    if (max==0) return 0;
    return getInt() % max;
  }

  inline float getFloat() {
    float y = getInt() ;
    return y * TO_FLOAT;
  }

  inline float getFloat(const float& upper_limit) {
    return ( upper_limit * TO_FLOAT * (float)(getInt() ) ) ;
  }
  
  inline float getFloatInRange(const float& lower_limit, const float& upper_limit) {
    return lower_limit + ( (upper_limit - lower_limit) * TO_FLOAT * (float)(getInt() ) ) ;
  }

  inline float getFloatSpread(const float& center_val, const float& variation) {
    return center_val - variation + ( variation * TO_FLOAT_2 * (float)(getInt() ) ) ;
  }
  
  inline void randomize(MYRAND_TYPE data) {
    _myRandomState = next((_myRandomState << 1) ^ data);
  }

  inline void setSeed() {
    randomize((MYRAND_TYPE)(micros() & MYRAND_MAX));
  }
  
  inline void setSeed(MYRAND_TYPE seed) {
    _myRandomState = seed;
  }
  
  inline bool tryChance(float chance_normalized) { // e.g. tryChance(0.3f) should return true ~30% times tried
    return (getFloat() < chance_normalized);
  }

  
  inline void init() {
    randomize(random(3, MYRAND_MAX));
  }
  

private:  
  const MYRAND_TYPE MYRAND_MAX = 0xFFFFFFFF;
  const MYRAND_TYPE MYRAND_MAGIC = 0xcf300000;
// const MYRAND_TYPE MYRAND_MAGIC = 0xBF000000;
  const float TO_FLOAT = 1.0f / MYRAND_MAX;
  const float TO_FLOAT_2 = 2.0f / MYRAND_MAX;

  const MYRAND_TYPE _a = 1664525UL ;
  const MYRAND_TYPE _c = 1013904223UL;
  
  MYRAND_TYPE _myRandomState = 1664525UL ;

#if (MYRAND_ALGO == LFSR)
// lfsr32
  inline MYRAND_TYPE next(MYRAND_TYPE x) {
    MYRAND_TYPE y ;
    y = x >> 1;
    if (x & 1) y ^= MYRAND_MAGIC;
    return y;
  }
#elif (MYRAND_ALGO == XORSHIFT)
// xorshift32
  inline MYRAND_TYPE next(MYRAND_TYPE x)
  {
      MYRAND_TYPE y = x;
      y ^= y << 13;
      y ^= y >> 17;
      y ^= y << 5;
   //   x = y;
      return y;
  }
#elif (MYRAND_ALGO == CONGRUENT)
// Linear Congruential Generator
  inline MYRAND_TYPE next(MYRAND_TYPE x)
  {
      MYRAND_TYPE y = _a * x + _c;      
      return y;
  }
#endif

};
