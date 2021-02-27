////////METODOS PUBLICOS////////

template<class T>
lista<T>::lista(void){
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

template<class T>
lista<T>::lista(const lista<T>& lista){
    size_ = 0;
    nodo<T>* nodo_aux = lista.head();
    while (nodo_aux != NULL ){
        insert_tail(nodo_aux->value());
        nodo_aux = nodo_aux->next();
    }
}

template<class T>
T lista<T>::operator[](int i)const{
  assert( (i >= 0) && ( i < size_ ) );
  nodo<T>* nodo_aux = head_;
  for (size_t j = 0; j < i; j++){
      nodo_aux = nodo_aux->next();
  }
  return nodo_aux->value();
}

template<class T>
lista<T>& lista<T>::operator=(const lista<T> lista){
    if (!empty()){
        clear();
    }
    nodo<T>* nodo_aux = lista.head();
    while (nodo_aux != NULL ){
        insert_tail(nodo_aux->value());
        nodo_aux = nodo_aux->next();
    }
}

template<class T>
bool lista<T>::operator==(const lista<T> lista)const{
    if(lista.size() != size_){
        return false;
    }
    for (size_t i = 0; i < size_; i++){
        if( get_value(i) != lista[i] ){
            return false;
        }
    }
    return true;
}

template<class T>
void lista<T>::pop_tail(void){
    assert(!empty());
    nodo<T>* nodo_aux = tail_;
    tail_ = tail_->prev();
    if (tail_ != NULL){//Si tail no apunta a null
        tail_->setnext(NULL);//el siguiente de ese nodo debe ser null
    }else{//si tail si apunta a null implica size_ = 1
        head_ = NULL;
    }
    nodo_aux->setnext(NULL);
    nodo_aux->setprev(NULL);
    delete nodo_aux;
    nodo_aux = NULL;
    size_--;
}

template<class T>
void lista<T>::pop_head(void){
    assert(!empty());
    nodo<T>* nodo_aux = head_;
    head_ = head_->next();
    if (head_){//Si head no apunta a null
        head_->setprev(NULL);//ese nodo debe ser el primero
    }else{//si head si apunta a null implica size_ = 1
        tail_ = NULL;
    }
    nodo_aux->setnext(NULL);
    nodo_aux->setprev(NULL);
    delete nodo_aux;
    nodo_aux = NULL;
    size_--;
}

template<class T>
void lista<T>::insert_tail( nodo<T>* nodo ){
    assert(nodo != NULL);
    nodo->setnext(NULL);
    if (empty()){
        nodo->setprev(NULL);
        head_ = nodo;
        tail_ = nodo;
    }else{
        tail_->setnext(nodo);
        nodo->setprev(tail_);
        tail_ = nodo;
    }
    size_++;
}

template<class T>
void lista<T>::insert_head( nodo<T>* nodo ){
    assert(nodo != NULL);
    nodo->setprev(NULL);
    if (empty()){
        nodo->setnext(NULL);
        head_ = nodo;
        tail_ = nodo;
    }else{
        head_->setprev(nodo);
        nodo->setnext(head_);
        head_ = nodo;
    }
    size_++;
}

template<class T>
nodo<T>* lista<T>::extract_head(void){
    assert(!empty());
    nodo<T>* nodo_aux = head_;
    head_ = head_->next();
    if (head_ != NULL){//Si head no apunta a null
        head_->setprev(NULL);//ese nodo debe ser el primero
    }else{//si head si apunta a null implica size_ = 1
        tail_ = NULL;
    }
    size_--;
    nodo_aux->setnext(NULL);
    nodo_aux->setprev(NULL);
    return nodo_aux;
}

template<class T>
nodo<T>* lista<T>::extract_tail(void){
    assert(!empty());
    nodo<T>* nodo_aux = tail_;
    tail_ = tail_->prev();
    if (tail_ != NULL){//Si tail no apunta a null
        tail_->setnext(NULL);//el siguiente de ese nodo debe ser null
    }else{//si tail si apunta a null implica size_ = 1
        head_ = NULL;
    }
    size_--;
    nodo_aux->setnext(NULL);
    nodo_aux->setprev(NULL);
    return nodo_aux;
}

template<class T>
void lista<T>::fill(T value){
    nodo<T>* nodo_aux = head_;
    while (nodo_aux != NULL){
        nodo_aux->setvalue(value);
        nodo_aux = nodo_aux->next();
    }
    
}

template<class T>
void lista<T>::set_value(T value,int i){
    assert( (i >= 0) && (i < size_) );
    nodo<T>* nodo_aux = head_;
    for (size_t j = 0; j < i; j++){
        nodo_aux = nodo_aux->next();
    }
    nodo_aux->setvalue(value);
}

template<class T>
T lista<T>::get_value(int i)const{
    assert( (i >= 0) && (i < size_) );
    nodo<T>* nodo_aux = head_;
    for (size_t j = 0; j < i; j++){
        nodo_aux=nodo_aux->next();
    }
    return nodo_aux->value();
}


template<class T>
nodo<T>* lista<T>::extract(int pos){
    assert( (pos >= 0) && (pos < size_) );
    nodo<T>* nodo_aux = head_;
    for (size_t i = 0; i < pos; i++){
        nodo_aux = nodo_aux->next();
    }
    if (nodo_aux->prev() != NULL){
        nodo_aux->prev()->setnext(nodo_aux->next());
    }else{
        head_ = nodo_aux->next();
    }
    if (nodo_aux->next() != NULL){
        nodo_aux->next()->setprev(nodo_aux->prev());
    }else{
        tail_ = nodo_aux->prev();
    }
    size_--;
    return nodo_aux;
}

template<class T>
void lista<T>::erase(int pos){
    delete extract(pos);
}

//es una funcion externa a la clase asi que debe recibir el objeto vector<T>
//es una sobrecarga al operador << de iostream
template<class T>
std::ostream& operator<<(std::ostream& os, const lista<T>& lista){
  nodo<T>* nodo_aux = lista.head();
  while(nodo_aux != NULL) {
    os  << nodo_aux->value();
    if ( nodo_aux->next() != NULL ){
      os << ", ";
    }
    nodo_aux = nodo_aux->next();
  }
  return os;
}

////////METODOS PRIVADOS////////

template<class T>
void lista<T>::destroy(void){
    nodo<T>* aux = NULL;
    while ( head_ != NULL ){
        aux = head_;
        head_ = head_->next();
        aux->setnext(NULL);
        aux->setprev(NULL);
        if (aux != NULL)
        {
            delete aux;
        }
        aux = NULL;
    }
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}