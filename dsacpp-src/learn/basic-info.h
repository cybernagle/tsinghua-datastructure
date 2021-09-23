// kinda pseudocode

/*
 * vector's metadata: size, capacity, data
 * vector's functions: Create, Read, Update, Delete
 *   Create: allocate.
 *   Read: Get from Rank, Find some value, terverse
 *   Update: insert, expand, shrink, sort, unsort
 *   Delete: delete by rank;
 */
template <typename T> class Vector {
 protected:
  int _capacity;
  int _size;
  T* data;
 public:
  Vector(int size, int capacity , T v = 0) {
    data = new T[capacity];
    for (int i = 0 ; i <= size; data[i++] = v);
  }

  void bubble() {};
  void fancyBubbleSort() {};
  void normalBubbleSort() {};

  void merge() {};
};
/*
 * normal code, and just for whole vector. it's bad.
 */
template <typename T> void Vector<T>::normalBubbleSort() {
  for(int j = 0 ; j <= _size; j++) {
    for(int i = 0; i <= _size; i++) {
      if (data[i] > data[i+1]){
        int tmp = data[i];
        data[i] = data[i+1];
        data[i+1] = tmp;
      }
    }
  }
}
/*
 * fancy code from , treat bubble as a single action, and if do not need bubble again, means all sorted.
 */
template <typename T> boolean Vector<T>::bubble() {
  boolean sorted = true;
  for (int i = 0 ; i <= _size; i++) {
    // if need sort , then means it's not sorted yet.
    sorted = false;
    swap(data[i] , data[i++]);
  }
}

template <typename T> void Vector<T>::fancyBubbleSort() {
  while (!bubble());
}

/*
 * have three part,
 *  A first : | lo --------- mi ---------- hi |
 *  B second: | lo --------- mi)
 *  C third : (mi ---------- hi |
 * what we need to do is take data[mi - lo], and data[hi - mi], merge them.
 * since B & C is sorted, our purpose is to merge B & C , then copy it to A. so we need to figure out several things:
 * 1. traverse B, if B is not traversed yet, and bigger then C(or C is all traversed), then put it into A.
 * 2. traverse C, if C is not traversed ye, and is bigger then B(or B is all traversed), then put it into A.
 */
template <typename T> void Vector<T>::merge(int lo, int hi, int mi) {
  // let A's location to be lo.
  T* A = data + lo;

  // copy mi - lo data to B.
  int left_side = mi - lo;
  T* B = new T[left_side];
  for (int i = 0; i < left_side; B[i] = A[i++]);

  int right_side = hi - mi;
  T* C = A[data + mi];

  // i for traverse A, j for B, k for C;
  for(int i,j,k = 0; j < left_side || k < right_side;) {
    // DO 1. merge B to A
    if (j < left_side && (!(k < right_side) || B[j] <= C[k] )){
      A[i++] = B[j++];
    }
    // DO 2. merge C to A
    if (k < right_side && (!(j<left_side) || C[k] <= B[j])){
      A[i++] = C[k++];
    }
  }

  delete [] B;
}

/*
 * List's metadata:
 *  List(data, headListNode, tailNode, size)
 *  ListNode(prev, next).
 * List's function: Create, Read, Update, Delete
 *   Create: allocate.
 *   Read: Get from Rank, Find some value, terverse
 *   Update: insert, sort, unsort
 *   Delete: delete by rank;
 */

template <typename T> struct ListNode;
template <typename T> using ListNodePosi() = ListNode();

template <typename T> struct ListNode {
  ListNode() {}
ListNode(T data, ListNodePosi<T> prev = null, ListNodePosi<T> next = null)
  : data(data), prev(prev), next(next) {}
  ListNodePosi<T> next;
  ListNodePosi<T> prev;
  T data;

  ListNodePosi<T> insertAsNext();
  ListNodePosi<T> insertAsPrev();
};

template <typename T> ListNodePosi<T> ListNode<T>::insertAsPrev(T const& data) {
  ListNodePosi<T> newNode = new ListNode(data, prev, this);
  prev.next = nowNode;
  prev = newNode;
  return newNode;
}

template <typename T> ListNodePosi<T> ListNode<T>::insertAsNext(T const& data) {
  ListNodePosi<T> newNode = new ListNode(data, this, next);
  next = newNode;
  next.prev = newNode;
  return newNode;
}

class List () {
 public:
  ListNode head, tail;
  int _size;
  insertAfterNode();
  insertBeforeNode();
}

/*
 * can implement by vector.
 */

template <typename T> class Stack: public Vector<T>{
  void push(T &const data){ insert(size(), data)};
  T pop() {
    return remove( size() - 1);
  };
  T& top() {
    return (*this)[size() - 1];
  };
};

/*
 * can implement by vector as well.
 */
template <typename T> class Queue: public Vector<T> {
  void enqueue( T const & data){
    insert(size(), data);
  };
  T* dequeue(){
    remove(first());
  };
};

/*
 * BinTree's metadata:
 *  BinNode/BinNodePosition : leftChild, rightChild, data, Parent, height
 *  BinTree: root, _size
 * BinTree's function: Create, Read, Update, Delete
 *  Create: allocate
 *  Read: 
 *  Update: 
 *  Delete: 
 */
template <typename T> struct BinNode{};

#define BinNodePosi(T) BinNode<T>*;

/*
 * as a node , this data should be able to:
 *  1. terverse
 *  2. find parent, left child , right child
 *  3. get current height.
 *  4. insert & remove node.
 */

template <typename T> struct BinNode {
  T data;
  BinNode(T) parent;
  BinNode(T) leftChild;
  BinNode(T) rightChild;
  int hight;

  BinNode(): parent(null), leftChild(null), rightChild(null),hight(0) { }
  BinNode(T e, BinNodePosi(T) parent, BinNodePosi(T) leftChild, BinNodePosi(T) rightChild , int height ) {
    data = e;
    parent = parent;
    leftChild = leftChild;
    rightChild = rightChild;
    hight = hight;
  }
};

/*
 * as a tree manager, this structure should be able to:
 *  1. get root node.
 *  2. CRUD tree, tree need to know where to insert & where to delete the node.
 */
class BinTree() {
 protected:
  int _size;
  BinNodePosi(T) root;

  updateHeight(BinNodePosi(T) x);
  // because Binary Node's child are not fixed. so it's hard to maintain it's height.
  // alternatively , just update all the height above. because binary tree's above is fixed.
  updateHeightAbove() {}
 public:
  BinTree(): _size(0), root(NULL) {}
  ~BinTree() {
    if (0 < _size) { remove(root);}
  }
  int size() {return _size;}

  template <typename T, typename VT> void trav_recur_preorder(BinNodePosi(T) node, VT& visit) {
    if (!x) return;
    visit(x -> data);
    trav_preorder(node -> lc, visit);
    trav_preorder(node -> rc, visit);
  }

  template <typename T, typename VT> void trav_recur_inorder(BinNodePosi(T) node, VT& visit) {
    if (!x) return;
    trav_preorder(node -> lc, visit);
    visit(x -> data);
    trav_preorder(node -> rc, visit);
  }

  template <typename T, typename VT> void trav_recur_postorder(BinNodePosi(T) node, VT& visit) {
    if (!x) return;
    trav_preorder(node -> lc, visit);
    trav_preorder(node -> rc, visit);
    visit(x -> data);
  }

  template <typename T, typename VT> static void visitAloneLeftBranch(BinNodePosi(T) leftNode, VT& visit, Stack<BinNodePosi(T)> & stack) {
    while(leftNode -> lc) {
      visit(x -> data);
      stack.push(x->rc);
      leftNode = leftNode -> lc;
    }
  }

  // because recursive version take to much space, so ,it's better change it to iteration version.
  template <typename T, typename VT> void trev_iter_preorder(BinNodePosi(T) node, VT& visit) {
    Stack<BinNodePosi(T)> stack;
    while( true ) {
      visitAloneLeftBranch(node, VT, stack);
      if (stack.empty()) {
        break;
      }
      node = stack.pop();
    }
  }

  template <typename T> void goAloneLeftBranch(BinNodePosi(T) inNode, Stack<BinNodePosi(T)> & stack) {
    while(x) {
      stack.push(x);
      x = x -> leftNode;
    }
  }

  template <typename T, typename VT> void trev_iter_inorder(BinNodePosi(T) node, VT& visit) {
    Stack<BinNodePosi(T)> stack;
    while (true) {
      goAloneLeftBranch(node, stack);
      if (stack.empty()){
        break;
      }
      node = stack.pop();
      visit(node -> data);
      node = node -> rightNode;
    }
  }

  template <typename T, typename VT> static void gotoHVFL(Stack<BinNodePosi(T)> & stack) {
    while(BinNodePosi(T) x = stack.top()) {
      if ( HasLChild( *x ) ) {
        if ( HasRChild( *x ) stack.push( x -> rightNode ));
        stack.push( x -> leftChild );
      } else {
        stack.push( x -> rightNode );
      }
    }
    stack.pop();
  }

  template <typename T, typename VT> void trev_iter_postorder(BinNodePosi(T) node, VT& visit) {
    Stack<BinNodePosi(T)> stack;
    if (x) stack.push( x );
    while( !stack.empty() ) {
      if ( stack.top() != x-> parent ){
        gotoHVFL( stack );
      }
    }

    x = s.pop();
    visit( x-> data );
  }

  template <typename T, typename VT> void trev_iter_postorder(BinNodePosi(T) node, VT& visit) {
    Queue<BinNodePosi(T)> queue;
    queue.enqueue(node);
    while(!queue.empty()) {
      BinNodePosi(T) x = queue.dequeue();
      visit(x->data);
      if (HasLChild( *x )) queue.enqueue(x->leftNode);
      if (HasRChild( *x )) queue.enqueue(x->rightNode);
    }
  }

};


struct GraphNode {};

class Graph() {};
