template<class T> struct DynamicArray {
    T *elements;
    int cnt, limit;
 
    DynamicArray() {
        elements = nullptr;
        cnt = limit = 0;
    }
 
    DynamicArray(int _limit) {
        limit = _limit; cnt = 0;
        elements = new T[limit];
    }
 
    void add(const T &t) {
        assert(++cnt < limit);
        elements[cnt - 1] = t;
    }
 
    T& operator [] (int x) {
        return elements[x];
    }
    T operator [] (int x) const {
        return elements[x];
    }
 
    void clear(void) {
        cnt = 0;
    }
};
