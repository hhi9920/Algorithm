//우선순위큐-<program 9.3- 히프트리 테스트 프로그램>
//최대 히프
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200	//배열 크기 200

//히프정의
typedef struct {	//히프의 각 요소들 구조체 element로 정의
	int key;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;	//현재 히프 안에 저장된 요소의 개수
}HeapType;

//생성함수-동적
HeapType * create() {
	return (HeapType *)malloc(sizeof(HeapType));
}

//초기화함수
void init(HeapType *h) {
	h->heap_size = 0;
}

//삽입함수: 현재 요소의 개수가 heap_size인 히프 h에 item 삽입
void insert_max_heap(HeapType *h, element item) {
	int i;
	i = ++(h->heap_size);	//삽입을 위해 히프h의 크기 1 증가 

	//트리 거슬러 올라가면서 부모노드와 비교
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		//i가 루트가 아니고 입력받은 item값이 i의 부모노드의 키값보다 크면
		//부모노드와 새로 삽입된 노드와 교환
		h->heap[i] = h->heap[i / 2];	//현재 노드를 부모노드로 설정
		i /= 2;	//i 인덱스를 부모노드의 인덱스로 설정
	}
	//while문 탈출했으므로 더이상 거슬러 올라갈 곳 없다는 의미
	//따라서 현재 인덱스의 위치(i)에 입력 받은 item 값 삽입
	h->heap[i] = item;	//새로운 노드 값 item 삽입
}

//삭제함수
element delete_max_heap(HeapType *h) {
	int parent, child;
	element item, temp;

	item = h->heap[1];	//반환할 루트 노드의 값을 item에 저장
	temp = h->heap[(h->heap_size)--];	//맨 마지막 노드의 값을 temp에 저장 후
										//루트 노드의 값을 위에서 뺐으므로 heap_size 1 감소

	//맨 마지막 노드값(temp)를 이용한 비교 과정 
	parent = 1;	//맨 첫 실행의 부모노드를 루트로 둠
	child = 2;	//루트의 왼쪽 자식부터 비교

	while (child <= h->heap_size) {//child가 힙사이즈보다 크면 힙을 벗어난 비교이므로 작거나 같을 경우 비교

		//현재 노드의 자식노드 중 값이 더 큰 자식노드 찾기
		if ((child < h->heap_size) && (h->heap[child].key) < (h->heap[child + 1].key))	//오른쪽 자식이 큰 경우
			child++;	//새로운 기준점 만들기 위해
		if (temp.key >= h->heap[child].key)	//비교대상(child)와 루트 노드에 위치 중인 temp와 비교
			break;	//temp 값이 더 큰 경우 히프 조건 만족하므로 반복문 탈출

		//temp의 자리 교환 필요(아래로 내려와야함)
		//temp가 있을 곳을 찾기 위해  비교대상(child)를 한 단계 아래로 이동
		h->heap[parent] = h->heap[child];	//자녀의 값이 새로운 비교 기준점됨
		child *= 2;	//child 값에 2를 곱하여 다음 자녀로 만들기

	}
	//반복문 탈출
	//parent가 temp가 위치할 곳이 되어 있음
	h->heap[parent] = temp;	
	return item;	//루트 노드 값(최댓값) 리턴
	
}

//메인함수
int main(void) {
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;
	HeapType *heap;	

	heap = create();	//히프생성
	init(heap);	//초기화

	//삽입
	insert_max_heap(heap, e1);	//10
	insert_max_heap(heap, e2);	//10 5
	insert_max_heap(heap, e3);	//30 5 10

	//삭제
	e4 = delete_max_heap(heap);
	printf("< %d >", e4.key);	//30 출력
	e5 = delete_max_heap(heap);
	printf("< %d >", e5.key);	//10 출력
	e6 = delete_max_heap(heap);
	printf("< %d >\n", e6.key);	//5 출력

	//
	free(heap);	// 동적 메모리 반환
	return 0;

}

