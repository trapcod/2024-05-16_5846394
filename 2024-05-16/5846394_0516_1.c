#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// 오류 처리 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert(ListNode* head, int value, int position) {
    int link = 1;
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) error("메모리 할당 에러");
    p->data = value;

    if (position == 0 || position == 1) { // 맨 앞에 삽입하는 경우를 0과 1 모두 처리
        p->link = head;
        head = p;
    }
    else {
        ListNode* temp = head;
        for (int i = 1; i < position - 1 && temp != NULL; i++) {
            temp = temp->link;
            link++;
        }
        if (temp != NULL) {
            p->link = temp->link;
            temp->link = p;
        }
        else {
            error("유효하지 않은 위치");
        }
    }
    printf("링크를 이동한 횟수 %d\n", link); //링크를 따라 이동한 횟수 출력
    return head;
}

ListNode* delete(ListNode* head, int position) {
    int link = 1;
    if (head == NULL) return NULL;

    ListNode* temp = head;
    if (position == 1) {
        head = temp->link;
        free(temp);
    }
    else {
        ListNode* prev = NULL;
        for (int i = 1; i < position && temp != NULL; i++) {
            prev = temp;
            temp = temp->link;
            link++;
        }
        if (temp != NULL) {
            prev->link = temp->link;
            free(temp);
        }
        else {
            error("유효하지 않은 위치");
        }
    }
    printf("링크를 이동한 횟수 %d\n", link); //링크를 따라 이동한 횟수 출력
    return head;
}


// 리스트를 출력하는 함수
void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

int main(void) {
    ListNode* head = NULL;
    int choice, item, position;

    while (1) {
        printf("\n메뉴 :\n");
        printf("1. 리스트에 추가 \n");
        printf("2. 리스트에서 삭제 \n");
        printf("3. 리스트 출력\n");
        printf("0. 프로그램 종료 \n");
        printf("선택 : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("추가할 항목의 값을 입력하세요: ");
            scanf("%d", &item);
            printf("추가할 위치를 입력하세요: ");
            scanf("%d", &position);
            head = insert(head, item, position);
            break;
        case 2:
            printf("삭제할 위치를 입력하세요: ");
            scanf("%d", &position);
            head = delete(head, position);
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            return 0;
        default:
            printf("잘못된 선택입니다.\n");
        }
    }
}
