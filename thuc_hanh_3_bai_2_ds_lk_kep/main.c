#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char hoten[30];
    int masv;
    float diem1, diem2, diem3;
} SV;
typedef struct tagNode {
    SV infor;
    struct tagNode *prev;
    struct tagNode *next;
} Node;
typedef struct {
    Node *pHead;
    Node *pTail;
    int spt;
} LList;
void initList(LList *L) {
    L->pHead = NULL;
    L->pTail = NULL;
    L->spt = 0;
}
int EmptyList(LList L) {
    return L.spt == 0;
}
void Nhap(SV *sv) {
    printf("Ho ten: ");
    scanf(" %[^\n]", sv->hoten);
    printf("Ma sinh vien: ");
    scanf("%d", &sv->masv);

    printf("Diem 1: ");
    scanf("%f", &sv->diem1);

    printf("Diem 2: ");
    scanf("%f", &sv->diem2);

    printf("Diem 3: ");
    scanf("%f", &sv->diem3);
}
void Xuat(SV sv) {
    printf("Ho ten: %s\tMa sv: %d\tDiem 1: %.2f\tDiem 2: %.2f\tDiem 3: %.2f\n",
           sv.hoten, sv.masv, sv.diem1, sv.diem2, sv.diem3);
}
void insertHead(LList *L, SV sv) {
    Node *pp = (Node*)malloc(sizeof(Node));
    if (pp == NULL) {
        printf("Khong du bo nho!\n");
        return;
    }
    pp->infor = sv;
    pp->prev = NULL;
    pp->next = L->pHead;
    if (EmptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        L->pHead->prev = pp;
        L->pHead = pp;
    }
    L->spt++;
}
void insertTail(LList *L, SV sv) {
    Node *pp = (Node*)malloc(sizeof(Node));

    if (pp == NULL) {
        printf("Khong du bo nho!\n");
        return;
}
    pp->infor = sv;
    pp->next = NULL;
    pp->prev = L->pTail;
    if (EmptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        L->pTail->next = pp;
        L->pTail = pp;
    }
    L->spt++;
}
Node *findNode(LList L, int ma) {
    Node *q = L.pHead;
    while (q != NULL && q->infor.masv != ma) {
        q = q->next;
    }
    return q;
}
void insertAfter(LList *L, int ma, SV x) {
    Node *q = findNode(*L, ma);
    if (q == NULL) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
    Node *pp = (Node*)malloc(sizeof(Node));
    if (pp == NULL) {
        printf("Khong du bo nho!\n");
        return;
    }
    pp->infor = x;
    pp->prev = q;
    pp->next = q->next;
    if (q->next != NULL) {
        q->next->prev = pp;
    } else {
        L->pTail = pp;
    }
    q->next = pp;
    L->spt++;
}
void processList(LList L) {
    Node *pp = L.pHead;
    if (EmptyList(L)) {
        printf("Danh sach rong!\n");
        return;
    }
    while (pp != NULL) {
        Xuat(pp->infor);
        pp = pp->next;
    }
}
void processListReverse(LList L) {
    Node *pp = L.pTail;
    if (EmptyList(L)) {
        printf("Danh sach rong!\n");
        return;
    }
    while (pp != NULL) {
        Xuat(pp->infor);
        pp = pp->prev;
    }
}
void deleteByMa(LList *L, int ma) {
    Node *q = findNode(*L, ma);
    if (q == NULL) {
        printf("Khong tim thay sinh vien!\n");
        return;
    }
    if (q->prev != NULL) {
        q->prev->next = q->next;
    } else {
        L->pHead = q->next;
    }
    if (q->next != NULL) {
        q->next->prev = q->prev;
    } else {
        L->pTail = q->prev;
    }
    free(q);
    L->spt--;
    printf("Da xoa sinh vien thanh cong!\n");
}
void deleteByTen(LList *L, char ten[]) {
    Node *q = L->pHead;
    int dem = 0;
    while (q != NULL) {
        if (strcmp(q->infor.hoten, ten) == 0) {
            Node *temp = q;
            q = q->next;
            if (temp->prev != NULL) {
                temp->prev->next = temp->next;
            } else {
                L->pHead = temp->next;
            }
            if (temp->next != NULL) {
                temp->next->prev = temp->prev;
            } else {
                L->pTail = temp->prev;
            }
            free(temp);
            L->spt--;
            dem++;
        } else {
            q = q->next;
        }
    }
    if (dem == 0)
        printf("Khong tim thay sinh vien!\n");
    else
        printf("Da xoa %d sinh vien!\n", dem);
}
void findByTen(LList L, char ten[]) {
    Node *q = L.pHead;
    int dem = 0;
    while (q != NULL) {
        if (strcmp(q->infor.hoten, ten) == 0) {
            Xuat(q->infor);
            dem++;
        }
        q = q->next;
    }
    if (dem == 0)
        printf("Khong tim thay sinh vien!\n");
}
void sortByTen(LList *L) {
    Node *p, *q;
    SV temp;

    for (p = L->pHead; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {
            if (strcmp(p->infor.hoten, q->infor.hoten) > 0) {
                temp = p->infor;
                p->infor = q->infor;
                q->infor = temp;
            }
        }
    }

    printf("Da sap xep danh sach theo ten!\n");
}
void splitList(LList *L, LList *L1, LList *L2) {
    freeList(L1);
    freeList(L2);
    Node *q = L->pHead;
    while (q != NULL) {
        if (q->infor.masv % 2 == 0) {
            insertTail(L1, q->infor);
        } else {
            insertTail(L2, q->infor);
        }
        q = q->next;
    }
    printf("Da tach danh sach thanh cong!\n");
    printf("\nDanh sach ma chan:\n");
    processList(*L1);
    printf("\nDanh sach ma le:\n");
    processList(*L2);
}
void mergeList(LList *L, LList *L1, LList *L2) {
    freeList(L);

    Node *q = L1->pHead;

    while (q != NULL) {
        insertTail(L, q->infor);
        q = q->next;
    }

    q = L2->pHead;

    while (q != NULL) {
        insertTail(L, q->infor);
        q = q->next;
    }

    printf("Da ghep hai danh sach thanh cong!\n");
}
int main() {
    LList L, L1, L2;
    SV x;
    int chon, ma;
    char ten[30];

    initList(&L);
    initList(&L1);
    initList(&L2);

    do {
        printf("\n===== QUAN LY SINH VIEN =====\n");
        printf("1. Them vao dau danh sach\n");
        printf("2. Them vao cuoi danh sach\n");
        printf("3. Them vao sau mot nut khac\n");
        printf("4. Tim kiem sinh vien theo ma\n");
        printf("5. Xoa sinh vien theo ma\n");
        printf("6. Xoa sinh vien theo ten\n");
        printf("7. Tim kiem sinh vien theo ten\n");
        printf("8. Sap xep danh sach theo ten\n");
        printf("9. Tach danh sach\n");
        printf("10. Ghep danh sach\n");
        printf("11. Duyet danh sach\n");
        printf("12. Duyet danh sach nguoc\n");
        printf("0. Thoat\n");

        printf("Moi ban chon: ");
        scanf("%d", &chon);

        switch (chon) {

            case 1:
                Nhap(&x);
                if (x.masv > 0)
                    insertHead(&L, x);
                else
                    printf("Ma sinh vien phai lon hon 0!\n");
                break;

            case 2:
                Nhap(&x);
                if (x.masv > 0)
                    insertTail(&L, x);
                else
                    printf("Ma sinh vien phai lon hon 0!\n");
                break;

            case 3:
                printf("Nhap ma sinh vien can chen sau: ");
                scanf("%d", &ma);

                printf("Nhap thong tin sinh vien moi:\n");
                Nhap(&x);

                if (x.masv > 0)
                    insertAfter(&L, ma, x);
                else
                    printf("Ma sinh vien phai lon hon 0!\n");
                break;

            case 4: {
                printf("Nhap ma sinh vien can tim: ");
                scanf("%d", &ma);

                Node *q = findNode(L, ma);

                if (q == NULL) {
                    printf("Khong tim thay sinh vien!\n");
                } else {
                    Xuat(q->infor);
                }
                break;
            }

            case 5:
                printf("Nhap ma sinh vien can xoa: ");
                scanf("%d", &ma);
                deleteByMa(&L, ma);
                break;

            case 6:
                printf("Nhap ten sinh vien can xoa: ");
                scanf(" %29[^\n]", ten);
                deleteByTen(&L, ten);
                break;

            case 7:
                printf("Nhap ten sinh vien can tim: ");
                scanf(" %29[^\n]", ten);
                findByTen(L, ten);
                break;

            case 8:
                sortByTen(&L);
                break;

            case 9:
                splitList(&L, &L1, &L2);
                break;

            case 10:
                mergeList(&L, &L1, &L2);
                processList(L);
                break;

            case 11:
                processList(L);
                break;

            case 12:
                processListReverse(L);
                break;

            case 0:
                printf("Bye bye!\n");
                break;

            default:
                printf("Lua chon khong hop le!\n");
        }

    } while (chon != 0);

    freeList(&L);
    freeList(&L1);
    freeList(&L2);

    return 0;
}

