#pragma comment(linker,"/STACK:2000000")
template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode{
        Comparable element;
        BinaryNode  *left;
        BinaryNode  *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
                    : element( theElement ), left( lt ), right( rt ) { }

friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree{

    public:
    explicit BinarySearchTree( const Comparable & notFound );
    BinarySearchTree( const BinarySearchTree & rhs );
    explicit BinarySearchTree( const Comparable & notFound ,BinaryNode<Comparable> *root);
    BinarySearchTree( const BinarySearchTree & rhs,BinaryNode<Comparable> *root);
    ~BinarySearchTree( );

    const Comparable & findMin( ) const;
    const Comparable & getRoot( ) const;
    const Comparable & findMax( ) const;
    const Comparable & find( const Comparable & x ) const;
    bool isEmpty();
    void printTree() const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );
    void update( const Comparable & x );

    const BinarySearchTree & operator=( const BinarySearchTree & rhs );
    BinaryNode<Comparable> * getRoot();    

    private:
    BinaryNode<Comparable> *root;    
    const Comparable ITEM_NOT_FOUND;

    const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

    void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * find( const Comparable & x,BinaryNode<Comparable> *t ) const;
    void update( const Comparable & x, BinaryNode<Comparable> * t ) const;
    void makeEmpty( BinaryNode<Comparable> * & t ) const;
    void printTree( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
};

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound )
    :ITEM_NOT_FOUND( notFound ), root( NULL )
{}

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound,BinaryNode<Comparable> *root)
    :ITEM_NOT_FOUND( notFound), root( root )
{}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t ) const{

    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> * t ) const{

    if ( t == NULL )
            return NULL;
        else if( x < t->element )
            return find( x, t->left );
        else if( t->element < x )
            return find( x, t->right );
        else
            return t;    // Match
}


template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const{
        return elementAt( find( x, root ) );
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t )  const{

    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::getRoot(){
    return root;
}


template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMin( ) const{

    return elementAt( findMin( root ) );
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t )  const{

    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const{
    return elementAt( findMax( root ) );
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode<Comparable> * & t ) const{

    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<Comparable>( x, NULL, NULL );
    else if( x < t->element )
        insert( x, t->left );  // insert at the left or
    else if( t->element < x )
        insert( x, t->right );  // right subtree
    else
        ;  // Duplicate; do nothing
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x ){

    insert( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );

    else if( t->left != NULL && t->right != NULL ) { //Two children
    t->element = findMin( t->right )->element;
    remove( t->element, t->right );
    }

    else {// one or no children
    BinaryNode<Comparable> *oldNode = t;
    t = ( t->left != NULL ) ? t->left : t->right;
    delete oldNode;
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x ){
        remove( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( ){
        makeEmpty( root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const{

    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

template <class Comparable>
void BinarySearchTree<Comparable>:: printTree( BinaryNode<Comparable> * t ) const{

        if ( t != NULL ){
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
}


template <class Comparable>
void BinarySearchTree<Comparable>::printTree( ) const{


//    if( isEmpty( ) )
//       cout << "Empty tree" << endl;
//    else
        printTree( root );
}

template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( ){
    makeEmpty( );
}


template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const{
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable> ( t->element, clone( t->left ),clone( t->right ));
}

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) :root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ){
    *this = rhs;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty(){
    return (root == NULL);
}

template <class Comparable>
void BinarySearchTree<Comparable>::update( const Comparable & x, BinaryNode<Comparable> * t ) const{

    if ( t != NULL ) {
        if( x < t->element )
            update( x, t->left );
        else if( t->element < x )
            update( x, t->right );
        else
            t->element = x;    // Match
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::update( const Comparable & x ){
        update( x, root );
}