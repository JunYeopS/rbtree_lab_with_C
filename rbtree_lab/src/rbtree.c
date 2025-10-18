#include "rbtree.h"

#include <stdlib.h>

void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void insert_fixup(rbtree *t, node_t *z);

rbtree *new_rbtree(void) {
  // tree 생성  
  rbtree *p = (rbtree *)malloc(sizeof(rbtree));

  // TODO: initialize struct if needed

  // NIL node 생성 (root에 넣어야됌) 
  p->nil = (node_t *)malloc(sizeof(node_t));

  p->nil->color = RBTREE_BLACK;
  p->nil->key = 0;

  p->nil->left = p->nil->right = p->nil->parent = p->nil;

  // root에 nill 넣기 
  p->root =p->nil;

  return p;
}

void delete_rbtree_node(rbtree *t, node_t *n){
  //base case 
  if (n == t->nil) return;

  // 왼쪽 
  delete_rbtree_node(t, n->left);
  // 오른쪽 
  delete_rbtree_node(t, n->right);
  // node 삭제 
  free(n);
}

void delete_rbtree(rbtree *t) {
  
  if (t == NULL) return;

  // 초기값 check 
  if(t->root != t->nil){
    // sub tree 다 지우고 
    delete_rbtree_node(t, t->root);
  }
  // nil 지우고 
  free(t->nil);
  // tree도 지우고 
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  if (!t) return NULL;

  node_t *parent = t->nil;
  node_t *cur = t->root;

  // 삽입 위치 찾기  (첫 노드면 pass)
  while(cur != t->nil) {
    parent = cur;

    //중복 이면 기존 노드 return 
    if (key == cur->key) return cur;   

    // 크기 비교 ? 왼:오 (cur)
    cur = (key < cur->key) ? cur->left : cur->right;
  }

  // 삽입할 노드 만들기
  node_t *new = (node_t *)malloc(sizeof(node_t));
  // 할당 하고 성공됐는지 확인하기 


  if (!new) return NULL; 
  new->key =key;  
  new->color = RBTREE_RED;
  new->left = t->nil;
  new->right = t->nil;
  // parent 갱신 (첫 노드가 아닐때)
  new->parent = parent;

  // 삽입 , 부모 연결 
  if (parent == t->nil) { // 첫 노드 삽입 
    t->root = new;
  } else {
    if (key < parent->key){
      parent->left = new;
    } else parent->right = new;
    }
  insert_fixup(t, new);
  return new;

}

// z= 삽입된 노드 
void insert_fixup(rbtree *t, node_t *z){

// g를 red로 바꾸는 과정에서 g ->p가 red면 또 같은 문제가 일어남 위에서부터 고치기
// 부모가 RED일 때만 규칙 위반(RED-RED 연속) 가능 → 그 동안 반
  while (z->parent->color == RBTREE_RED){
    /* 부모가 조부모의 "왼쪽 자식"인 경우 */
    if (z->parent == z->parent->parent->left){
        // 삼촌(uncle)
        node_t *uncle = z->parent->parent->right;
          /* Case 1: 부모와 삼촌이 모두 RED 조부모 RED, z를 조부모로 올려 재검사 */
          if (z->parent->color == RBTREE_RED && uncle->color == RBTREE_RED){
              z->parent->color = RBTREE_BLACK;
              uncle->color = RBTREE_BLACK;
              uncle->parent->parent->color = RBTREE_RED;

              z = z->parent->parent;
          }
          /* Case 2/3: 삼촌이 BLACK */
          else {
              /* Case 2: z가 "부모의 오른쪽 자식" (지그재그) */
              if (z == z->parent->right){
                z = z->parent; // 이래야 일직선 모양 z가 삽입된 모양이 된다.  

                left_rotate(t,z);
              }
              /* Case 3: z가 "부모의 왼쪽 자식"*/
              z->parent->color = z->parent->parent->color;
              // 조부모 기준으로 우회전 
              right_rotate(t, z->parent->parent);
              // 여기서 보정 종료 지점으로 수렴
            }    
    }else{
      node_t *uncle = z->parent->parent->left;
      if(z->parent->color == RBTREE_RED && uncle->color == RBTREE_RED){
        z->parent->color = RBTREE_BLACK;
        uncle->color = RBTREE_BLACK;
        uncle->parent = RBTREE_RED;

        z = z->parent->parent;
      }
      else{
        if (z == z->parent->left){
          z = z->parent;

          right_rotate(t, z);
        }
        z->parent->color = z->parent->parent->color;
        left_rotate(t, z->parent->parent);
      }
    }
    
  }
  t->root->color = RBTREE_BLACK;
}


// rotate기준 노드 받을래요 
// 오른쪽 자식을 부모 자리로 올리고, 부모를 왼쪽으로 내려 중위 순서를 유지
void left_rotate(rbtree *t, node_t *x){
  if (x == t->nil) return;
  if (x->right == t->nil) return;

  //y : x의 오른쪽 자식
  node_t *y = x->right;
  //a : y의 왼쪽 자식
  node_t *a = y->left; 

  //a를 x의 오른쪽으로 이동
  x->right = a;
  if (a != t->nil) a->parent = x;

  //기존 tree랑 연결 (!기존 node에 부모를 확인해야함)
  y->parent = x->parent;
  //root에 자식이였는지 아닌지에 따라 부모에 자식이랑 재연결 
  if (x->parent == t->nil) {
    // root 였으면 root를 y로 
    t->root = y;
  } else if (x == x->parent->left){
    x->parent->left = y;
  } else{ 
    x->parent->right = y;
  }

  //x의 부모 는 y 
  x->parent = y;
  // x를 y의 왼쪽 자식 연결
  y->left = x;

}

void right_rotate(rbtree *t , node_t *x){
  if (x == t->nil) return;
  if (x->left == t->nil) return;

  node_t *y = x->left;
  node_t *a = y->right; 

  x->left = a;
  if (a != t->nil) a->parent = x;

  y->parent = x->parent;

  if (x->parent == t->nil) {
    t->root = y;
  } else if (x == x->parent->left){
    x->parent->left = y;
  } else{ 
    x->parent->right = y;
  }

  x->parent = y;
  y->right = x;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return t->root;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  // 왼쪽만 보면 된다
  return t->root;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  // 오른쪽만 보면 된다 
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p) {
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  return 0;
}