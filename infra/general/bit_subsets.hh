#ifndef SRC_INFRA_BITSUBSETS_HH
#define SRC_INFRA_BITSUBSETS_HH

#include "bit_intrinsics.hh"
#include "bitvectorsmall.hh"

// this one generates S \subset X, S \neq \emptyset
template<class Tuint>
class BvTrueNonEmptySubsets {
  public:
    typedef Tuint bitvector_t;
  public:
    BvTrueNonEmptySubsets(const Tuint x) : _start(0), _current(0) { init(x); }
  public:
        inline void init(Tuint x) { _start = x; _current = (x & (-x)); }
        inline void reset() { _current = (_start & (-_start)); }
        inline BvTrueNonEmptySubsets& operator++() { advance(); return (*this); }
        inline bool isValid() const { return (_start != _current); }
        inline Tuint operator*() { return _current; }
        inline Tuint get() const { return _current; }
        inline Tuint getFullSet() const { return _start; }
  private:
        inline void advance() {
                      _current = (_start & (_current - _start));
                    }
  private:
    bitvector_t _start;
    bitvector_t _current;
};

template<class Tuint>
class BvNonEmptySubsets {
  public:
    typedef Tuint bitvector_t;
  public:
    BvNonEmptySubsets(const Tuint x) : _start(0), _current(0) { init(x); }
  public:
        inline void init(Tuint x) { _start = x; _current = (x & (-x)); }
        inline void reset() { _current = (_start & (-_start)); }
        inline BvNonEmptySubsets& operator++() { advance(); return (*this); }
        inline bool isValid() const { return (0 != _current); }
        inline Tuint operator*() { return _current; }
        inline Tuint get() const { return _current; }
        inline Tuint getFullSet() const { return _start; }
  private:
        inline void advance() {
                      _current = (_start & (_current - _start));
                    }
  private:
    bitvector_t _start;
    bitvector_t _current;
};

// this one generates S \subset X, S \neq X
template<class Tuint>
class BvTrueSubsets {
  public:
    typedef Tuint bitvector_t;
  public:
    BvTrueSubsets(const Tuint x) : _start(0), _current(0), _status(0) { init(x); }
  public:
        inline void init(Tuint  x) { _start = x; _current = (x & (-x)); _status = 0; }
        inline void reset() { _current = (_start & (-_start)); }
        inline BvTrueSubsets& operator++() { advance(); return (*this); }
        inline bool isValid() const { return ((0 == _status) || (_start != _current)); }
        inline Tuint get() const { return ((0 == _status) ? 0 : _current); }
        inline Tuint operator*() { return get(); }
        inline Tuint getFullSet() const { return _start; }
  private:
    inline void advance() {
                  if(0 != _status) { 
                    _current = (_start & (_current - _start)); 
                  }
                  ++_status;
                }
  private:
    bitvector_t _start;
    bitvector_t _current;
    int         _status;
};


// this one generates all subsets, including the full set and the empty set
template<class Tuint>
class BvAllSubsets {
  public:
    typedef Tuint bitvector_t;
  public:
    BvAllSubsets(const Tuint x) : _start(0), _current(0), _status(0) { init(x); }
  public:
        inline void init(Tuint  x) { _start = x; _current = (x & (-x)); _status = 0; }
        inline void reset() { _current = (_start & (-_start)); }
        inline BvAllSubsets& operator++() { advance(); return (*this); }
        inline bool isValid() const { return ((0 == _status) || (0 != _current)); }
        inline Tuint get() const { return ((0 == _status) ? 0 : _current); }
        inline Tuint operator*() { return get(); }
        inline Tuint getFullSet() const { return _start; }
  private:
    inline void advance() {
                  if(0 != _status) {
                    _current = (_start & (_current - _start));
                  }
                  ++_status;
                }
  private:
    bitvector_t _start;
    bitvector_t _current;
    int         _status;
};


// generate the index of all bits set
// this one starts with the lowest
// members are listed in ascending order
template<class Tuint>
class BvMemberIdxAsc {
  public:
    typedef Tuint bitvector_t;
  public:
    BvMemberIdxAsc(const Tuint x) : _curr(x), _idx(idx_lowest_bit_set(x)) {}
  public:
    inline void init(Tuint x) { _curr(x); }
    inline bool isValid() const { return (0 != _curr); }
    inline BvMemberIdxAsc& operator++() { advance(); return (*this); }
    inline uint32_t operator*() const { return _idx; }
  private:
    inline void advance() {
                  if(isValid()) {
                    _curr ^= ((Tuint) 1) << _idx;
                    _idx = idx_lowest_bit_set(_curr);
                  }
                }
  private:
    bitvector_t _curr;
    uint32_t    _idx;
};


// generate the index of all bits set
// this one starts with the lowest
// members are listed in descending order
template<class Tuint>
class BvMemberIdxDesc {
  public:
    typedef Tuint bitvector_t;
  public:
    BvMemberIdxDesc(const Tuint x) : _curr(x), _idx(idx_lowest_bit_set(x)) {}
  public:
    inline void init(Tuint x) { _curr(x); }
    inline bool isValid() const { return (0 != _curr); }
    inline BvMemberIdxDesc& operator++() { advance(); return (*this); }
    inline uint32_t operator*() const { return _idx; }
  private:
    inline void advance() {
                  if(isValid()) {
                    _curr ^= ((Tuint) 1) << _idx;
                    _idx = idx_highest_bit_set(_curr);
                  }
                }
  private:
    bitvector_t _curr;
    uint32_t    _idx;
};




#endif
