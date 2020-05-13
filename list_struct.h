//
// Created by dunka on 03.11.2019.
//

#ifndef UNTITLED1_LIST_STRUCT_H
#define UNTITLED1_LIST_STRUCT_H

#include <cstdlib>

struct elements {
    int data;
    struct elements* next;
    struct elements* prev;
};

struct s_list {
    struct elements* head;
    struct elements* tail;
    int size;
};

enum error{
    S_INCORRECT_COMMAND = -8,
    OK = 0,
};

struct s_list* S_ListInit ()
{
    struct s_list* List = (struct s_list*) calloc (1, sizeof (struct s_list));

    List->head = nullptr;
    List->tail = nullptr;
    List->size = 0;

    return List;
}


void S_Dump (struct s_list* List)
{
    FILE* out = fopen ("list.dot", "w");

    fprintf (out, "digraph structs {\nrankdir=LR;\n");

    struct elements* elem = List->head;

    int i = 0;
    while (i < List->size)
    {
        fprintf (out, "%d [shape=record,label=\"  <l%d> physics number = %d | value = %d | <p%d> prev = %d | next = %d  \"];\n"
                ,elem, elem, elem, elem->data, i, elem->prev, elem->next);
        i++;
        elem = elem->next;
    }

    elem = List->head;
    i = 0;
    while (i < List->size)
    {
        fprintf (out, "%d:<n%d> -> %d:<%d>;\n", elem, elem, elem->next, elem->next);
        i++;
        elem = elem->next;
    }

    fprintf (out, "\n}");

    fclose (out);

    system ("D:\\Graphiz\\bin\\dot.exe list.dot -T png -o list.png");
    system ("list.png");
}

void S_PushFront (int value, struct s_list* List)
{
    struct elements* element = (struct elements*) calloc (1, sizeof (struct elements));
    element->data = value;
    element->prev = nullptr;

    if (List->size == 0)
    {
        element->next = nullptr;
        List->tail = element;
    }
    else
    {
        element->next = List->head;
        List->head->prev = element;
    }

    List->head = element;
    List->size++;
}

void S_PushBack (int value, struct s_list* List)
{
    struct elements* element = (struct elements*) calloc (1, sizeof (struct elements));
    element->data = value;
    element->next = nullptr;

    if (List->size == 0)
    {
        element->prev = nullptr;
    }
    else
    {
        element->prev = List->tail;
        List->tail->next = element;
    }

    List->tail = element;
    List->size++;
}

struct elements* FindElementByPhysicsNumber (int physics_number, struct s_list* List)
{
    struct elements* res = List->head;

    for (int i = 1; i < physics_number; i++)
    {
        res = res->next;
    }

    return res;
}


int S_InsertAfter (int physics_number, int value, struct s_list* List)
{
    if (physics_number > List->size)
    {
        return S_INCORRECT_COMMAND;
    }

    if (List->size == 0)
    {
        if (physics_number == 0)
        {
            S_PushFront (value, List);
        }
        else
        {
            printf ("Incorrect command");
            return S_INCORRECT_COMMAND;
        }
    }
    else
    {
        struct elements* this_ = FindElementByPhysicsNumber (physics_number, List);
        if (this_ == List->tail)
        {
            S_PushBack (value, List);
        }
        else
        {
            struct elements* element = (struct elements*) calloc (1, sizeof (struct elements));

            element->data = value;
            element->next = this_->next;
            element->prev = this_;

            this_->next->prev = element;
            this_->next = element;

            List->size++;
        }
    }
    return OK;
}

int S_InsertBefore (int physics_number, int value, struct s_list* List)
{
    if (physics_number > List->size)
    {
        return S_INCORRECT_COMMAND;
    }

    if (List->size == 0)
    {
        if (physics_number == 0)
        {
            S_PushFront (value, List);
        }
        else
        {
            printf ("Incorrect command");
            return S_INCORRECT_COMMAND;
        }
    }
    else
    {
        struct elements* this_ = FindElementByPhysicsNumber (physics_number, List);
        if (this_ == List->head)
        {
            S_PushFront (value, List);
        }
        else
        {
            struct elements* element = (struct elements*) calloc (1, sizeof (struct elements));

            element->data = value;
            element->next = this_;
            element->prev = this_->prev;

            this_->prev->next = element;
            this_->prev = element;

            List->size++;
        }
    }
    return OK;
}

int S_Delete (int physics_number, struct s_list* List)
{
    if (physics_number > List->size)
    {
        return S_INCORRECT_COMMAND;
    }

    struct elements* this_ = FindElementByPhysicsNumber (physics_number, List);

    if (this_ == List->head)
    {
        this_->next->prev = nullptr;
        List->head = this_->next;
    }
    else
    {
        if (this_ == List->tail)
        {
            this_->prev->next = nullptr;
            List->tail = this_->next;
        }
        else
        {
            this_->prev->next = this_->next;
            this_->next->prev = this_->prev;
        }
    }

    List->size--;

    free (this_);

    return  OK;
}

void S_DeleteList (struct s_list* List)
{
    struct elements* elem = List->head;

    while (elem->next != nullptr)
    {
        struct elements* tmp = elem;
        elem = elem->next;
        free (tmp);
    }
    free (elem);
    free (List);
    List = nullptr;
}

#endif //UNTITLED1_LIST_STRUCT_H
