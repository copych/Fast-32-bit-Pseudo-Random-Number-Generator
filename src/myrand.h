/*
   FAST Pseudo-random generator
*/

 

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

  const MYRAND_TYPE a = 1664525UL ;
  const MYRAND_TYPE c = 1013904223UL;
  
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
