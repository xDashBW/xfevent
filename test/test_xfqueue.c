#include "../xf_queue.h"

#include <stdio.h>

typedef struct student {
    xf_queue_t head;
    int id;
} student_t;

int num = 0;

void init (student_t *stu) {
    stu->id = num++;
    xf_queue_init(&stu->head);
}

int main()
{
    student_t stu0;
    init(&stu0);
    student_t stu1;
    init(&stu1);
    student_t stu2;
    init(&stu2);
    student_t stu3;
    init(&stu3);
    student_t stu4;
    init(&stu4);
    student_t stu5;
    init(&stu5);
    
    xf_queue_t head;
    xf_queue_init(&head);
    xf_queue_push_back(&head, &stu0.head);
    xf_queue_push_back(&head, &stu1.head);
    xf_queue_push_back(&head, &stu2.head);
    xf_queue_push_back(&head, &stu3.head);
    xf_queue_push_back(&head, &stu4.head);
    xf_queue_push_back(&head, &stu5.head);
    
    printf("-==============foreach test======================\n");
    student_t *iter;
    xf_queue_foreach(&head, iter, student_t, head) {
        printf("id: %d\n", iter->id);
    }
    
    printf("-==============del test======================\n");
    xf_queue_del(&stu4.head);
    xf_queue_del(&stu0.head);
    xf_queue_del(&stu5.head);
    xf_queue_foreach(&head, iter, student_t, head) {
        printf("id: %d\n", iter->id);
    }
}
