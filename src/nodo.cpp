template<class T>
nodo<T>::nodo(const T& value){
    next_ = NULL;
    prev_ = NULL;
    value_ = value;
}
/*
template<class T>
nodo<T>::nodo(const T& value, nodo<T>* next, const nodo<T>* prev){
    next_ = next;
    prev_ = prev;
    value_ = value;
}
*/
template<class T>
nodo<T>::~nodo(void){
    next_ = NULL;
    prev_ = NULL;
}