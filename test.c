/*
  (c) 2005,2008-2009,2012 Coverity, Inc. All rights reserved worldwide.
  The information contained in this file is the proprietary and confidential
  information of Coverity, Inc. and its licensors, and is supplied subject to,
  and may be used only by Coverity customers in accordance with the terms and
  conditions of a previously executed license agreement between Coverity and that
  customer.
*/

#include "stdio.h"
#include "stdlib.h"

void forward_null(void)
        {
          char* p = 0;
          *p = 'a';
        }

void reverse_null(char* input)
    {
        *input = 12;
                if (input == NULL)
                        return;
    }

void resource_leak(void)
        {
                char *p = malloc(4);
                p[0] = 12;
        }

void resource_leak_2(void)
        {
                char *p = malloc(4);
                char *q = malloc(12);
                if (!p || !q)
                        return;
        }

void use_after_free(void)
        {
                char *p = malloc(4);
                *p = 'a';
                free(p);
        }

struct bigger_than_ptr { int a; int b; int c; int d; };

void size_check(void)
        {
                struct bigger_than_ptr *p;
                p = malloc(sizeof(struct bigger_than_ptr *));
        }

int some_func(void);

void dead_code(void)
        {
                int x = some_func();
                if (x) {
                        if (!x) {
                                x++;
                                return;
                        }
                }
        }

int read(int, char*, int);

void negative_returns(void)
        {
                char buf[10];
                int j = read(1, buf, 8);
                buf[j] = '\0';
        }

void reverse_negative(void)
        {
                int j = some_func();
                char buf[10];
                buf[j] = '\0';
                if (j < 0)
                        return;
        }

void uninit(void)
        {
                char* p = 0;
                *p = 'a';
        }

void overrun_static(void)
        {
                char buf[10];
                int i;
                for (i = 0; i < 10; i++)
                        buf[i] = '\0';
        }

#define NO_MEM -1
#define OK 0
#define OTHER_ERROR -2

int paths() {
  char *p = malloc(12);

  if (!p)
    return NO_MEM;

  if (!some_other_function()) {
    free(p);
    return OTHER_ERROR;
  }

  if (!yet_another_function()) {
    return OTHER_ERROR;
  }

  do_some_things(p);

  free(p);
  return OK;
}
