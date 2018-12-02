/****************************
 * phases.c
 * Lionel Oh & Andrew Gross
 * COMP 40 Fall 2018
 * HW 5
 *
 * This file contains our interpretation of how each phase and their
 * non-obvious helper functions should appear in C.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef char *string;

extern int strings_not_equal(string s, string input);
extern void explode_bomb();
extern int read_six_numbers(string *input);
extern int string_length(string input);

void phase_1(string input)
{
        string s; 
        s = "Why waste those cute little tricks that the Army taught us?";
        if (strings_not_equal(s, input)) {
                return;
        } else {
                explode_bomb();
        }
}

void phase_2(string input)
{
        int result = 0;
        // read_six_numbers detonates the bomb if input numbers are not spaced
        // by one space
        read_six_numbers(&input); // Is this passed correctly?
        int x, y;
        for (int i = 0; i < 3; i++) {
                x = input[i];
                y = input[i + 3];
                
                if (x != y) {
                        explode_bomb();
                }

                result =+ x; 
        }

        if (result > 0) {
                return;
        } else {
                explode_bomb();
        }
}

void phase_3(string input)
{
        string template = "%d %c %d";
        int num1, num2, args;
        char value, comparison;

        args = sscanf(input, template, &num1, &value, &num2);

        if (args < 3) {
                explode_bomb();
        }

        if (num1 > 7) {
                explode_bomb();
        }

        switch (num1) {
                case 0:
                if (num2 == 929) {
                        comparison = 'e';
                        break;
                } else {
                        explode_bomb();
                }
                case 1:
                if (num2 == 268) {
                        comparison = 'k';
                        break;
                } else {
                        explode_bomb();
                }
                case 2:
                if (num2 == 876) {
                        comparison = 'i';
                        break;
                } else {
                        explode_bomb();
                }
                case 3:
                if (num2 == 295) {
                        comparison = 'v';
                        break;
                } else {
                        explode_bomb();
                }
                case 4:
                if (num2 == 773) {
                        comparison = 'd';
                        break;
                } else {
                        explode_bomb();
                }
                case 5:
                if (num2 == 320) {
                        comparison = 'd';
                        break;
                } else {
                        explode_bomb();
                }
                case 6:
                if (num2 == 645) {
                        comparison = 's';
                        break;
                } else {
                        explode_bomb();
                }
                case 7:
                if (num2 == 848) {
                        comparison = 'g';
                        break;
                } else {
                        explode_bomb();
                }
        }

        if (value == comparison) {
                return;
        } else {
                explode_bomb();
        }
}

int func4(int value)
{
        /* base case */
        if (value <= 1) {
                return value;
        }

        int new_value = value - 1;
        int result = func4(new_value);

        result = result * value;
        return result;
}

void phase_4(string input)
{
        string template = "%d";
        int value, result, args;

        args = sscanf(input, template, &value);

        if (args != 1) {
                explode_bomb();
        }

        if (value > 0) {
                result = func4(value);
                if (result == 5040) {
                        return;
                } else {
                        explode_bomb();
                }

        } else {
                explode_bomb();
        }
}

void phase_5(string input)
{
        int i = string_length(input);

        if (i == 6) {
                string ref_str = "isrveawhobpnutfg";
                string result = "titans";
                char output[6];
                int offset;

                for (i = 0; i < 6; i++) {
                        offset = input[i] & 0xf;
                        output[i] = ref_str[offset];
                }

                if (!strings_not_equal(output, result)) {
                        explode_bomb();
                } 

        } else {
                explode_bomb();
        }
}

struct node_t {
        const int value;
        struct node_t *next;
};

struct node_t *func6(struct node_t *root_ptr)
{
        struct node_t *x, *y, *e;

        x = root_ptr;
        root_ptr = NULL;

        while(x != NULL) {
                e = x;
                x = x->next;
                if (root_ptr != NULL) {
                        if(e->value > root_ptr->value) {
                                y = root_ptr;

                                while ((y->next != NULL) && 
                                        (e->value > y->next->value)) {
                                        y = y->next;
                                }

                                e->next = y->next;
                                y->next = e;
                        } else {
                                e->next = root_ptr;
                                root_ptr = e ;
                        }
                } else {
                        e->next = NULL;
                        root_ptr = e ;
                }
        }

        return root_ptr;
}

void phase_6(string input)
{
        char *ptr;
        long result;
        result = strtol(input, &ptr, 10);

        struct node_t root_ptr;
        struct node_t *node_ptr = func6(&root_ptr);

        for (int i = 8; i > 0; i--) {
                node_ptr = node_ptr->next;
        }

        if (result == (long)(node_ptr->value)) {
                return;
        } else {
                explode_bomb();
        }
}





