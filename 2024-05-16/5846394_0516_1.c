#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

// ���� ó�� �Լ�
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

ListNode* insert(ListNode* head, int value, int position) {
    int link = 1;
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) error("�޸� �Ҵ� ����");
    p->data = value;

    if (position == 0 || position == 1) { // �� �տ� �����ϴ� ��츦 0�� 1 ��� ó��
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
            error("��ȿ���� ���� ��ġ");
        }
    }
    printf("��ũ�� �̵��� Ƚ�� %d\n", link); //��ũ�� ���� �̵��� Ƚ�� ���
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
            error("��ȿ���� ���� ��ġ");
        }
    }
    printf("��ũ�� �̵��� Ƚ�� %d\n", link); //��ũ�� ���� �̵��� Ƚ�� ���
    return head;
}


// ����Ʈ�� ����ϴ� �Լ�
void print_list(ListNode* head) {
    for (ListNode* p = head; p != NULL; p = p->link)
        printf("%d->", p->data);
    printf("NULL\n");
}

int main(void) {
    ListNode* head = NULL;
    int choice, item, position;

    while (1) {
        printf("\n�޴� :\n");
        printf("1. ����Ʈ�� �߰� \n");
        printf("2. ����Ʈ���� ���� \n");
        printf("3. ����Ʈ ���\n");
        printf("0. ���α׷� ���� \n");
        printf("���� : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("�߰��� �׸��� ���� �Է��ϼ���: ");
            scanf("%d", &item);
            printf("�߰��� ��ġ�� �Է��ϼ���: ");
            scanf("%d", &position);
            head = insert(head, item, position);
            break;
        case 2:
            printf("������ ��ġ�� �Է��ϼ���: ");
            scanf("%d", &position);
            head = delete(head, position);
            break;
        case 3:
            print_list(head);
            break;
        case 0:
            return 0;
        default:
            printf("�߸��� �����Դϴ�.\n");
        }
    }
}
