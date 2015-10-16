#ifndef SRC_INFRA_BIT_INTRINSICS_HH
#define SRC_INFRA_BIT_INTRINSICS_HH

#include <inttypes.h>

/*
 * return the index of the highest bit set
 */

template<class Tuint>
inline uint32_t
idx_highest_bit_set(const Tuint x);


template<>
inline uint32_t
idx_highest_bit_set<uint32_t>(const uint32_t x) {
#if __ICC
  return (_bit_scan_reverse(x));
#elif __GNUG__
  return (31 - __builtin_clz(x));
#endif
}

template<>
inline uint32_t
idx_highest_bit_set<uint64_t>(const uint64_t x) {
#if __ICC
  return (63 - __builtin_clzll(x)); // gibt kein _bit_scan_reverse64
#elif __GNUG__
  return (63 - __builtin_clzll(x));
#endif
}



/*
 * return the index of the lowest bit set
 */

template<class Tuint>
inline uint32_t
idx_lowest_bit_set(const Tuint x);


template<>
inline uint32_t
idx_lowest_bit_set<uint32_t>(const uint32_t x) {
#if __ICC
  return (_bit_scan_forward(x));
#elif __GNUG__
  return (__builtin_ctz(x));
#endif
}


template<>
inline uint32_t
idx_lowest_bit_set<uint64_t>(const uint64_t x) {
#if __ICC
  return (__builtin_ctzll(x)); // gibt kein _bit_scan_forward64
#elif __GNUG__
  return (__builtin_ctzll(x));
#endif
}


/*
 * return the number of bits set
 */

template<class Tuint>
inline uint32_t 
number_of_bits_set(const Tuint);


template<>
inline uint32_t
number_of_bits_set<uint32_t>(const uint32_t x) {
#if __ICC
  return (_popcnt32(x));
#elif __GNUG__
  return (__builtin_popcount(x));
#endif
}


template<>
inline uint32_t
number_of_bits_set<uint64_t>(const uint64_t x) {
#if __ICC
  return (_popcnt64(x));
#elif __GNUG__
  return (__builtin_popcount(x));
#endif
}


/*
 * return true if X \subseteq Y
 */

template<class Tuint>
bool
isSubsetOf(const Tuint X, const Tuint Y) {
  return (Y == (X | Y));
}

/*
 * returns true if X \cap Y = \emptyset
 */

template<class Tuint>
bool
hasEmptyIntersection(const Tuint X, const Tuint Y) {
  return (0 == (X & Y));
}

/*
 * returns true if X \cap Y \neq \emptyset
 */

template<class Tuint>
bool
hasNonEmptyIntersection(const Tuint X, const Tuint Y) {
  return (0 != (X & Y));
}

/*
 *  calculates the set differentce X \setminus Y
 */

template<class Tuint>
Tuint
setDifference(const Tuint X, const Tuint Y) {
  return (X & (~Y));
}



#endif
