#include "queue.h"
#include "linked_list.h"
#include "tile_game.h"
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state) {
    size_t new_value = serialize(state);
    insert_at_tail(&q->data, new_value);
    return;
}

struct game_state dequeue(struct queue *q) {  
    size_t removed_value = remove_from_head(&q->data);
    return deserialize(removed_value); 
}

size_t mod_serialize(struct game_state state){
    state.num_steps = 0;
    return serialize(state);
}

int check(struct linked_list list, struct game_state state){
    struct list_node *temp = list.head;
    state.num_steps = 0;
    while(temp != NULL){
        if(serialize(state) == temp->value){
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

int correct_state(struct game_state state){
    size_t correct_state = 81985526993846272;
    state.num_steps = 0;
    if(serialize(state) ==  correct_state){
        return 1;
    }else{
        return 0;
    }
}

int number_of_moves(struct game_state start) { 
    struct queue q;
    q.data.head = NULL;
    struct linked_list visited;
    visited.head =  NULL;
    int iter = 0;
    insert_at_head(&visited, mod_serialize(start));

    enqueue(&q, start);

    struct game_state visited_node = start;

    while(q.data.head != NULL){
        iter++;
        visited_node = dequeue(&q);
        
        if(correct_state(visited_node)){
            free_list(q.data);
            free_list(visited);
            printf("%d\n", iter);

            return visited_node.num_steps;
        }
        
        struct game_state up = visited_node;
        struct game_state down = visited_node;
        struct game_state left = visited_node;
        struct game_state right = visited_node;

        move_up(&up);
        move_down(&down);
        move_left(&left);
        move_right(&right);

        if(up.num_steps != visited_node.num_steps && !check(visited, up)){
            enqueue(&q, up);
            up.num_steps = 0;
            insert_at_head(&visited, serialize(up));
        }

        if(down.num_steps != visited_node.num_steps && !check(visited, down)){
            enqueue(&q, down);
            down.num_steps = 0;
            insert_at_head(&visited, serialize(down));
        }

        if(left.num_steps != visited_node.num_steps && !check(visited, left)){
            enqueue(&q, left);
            left.num_steps = 0;
            insert_at_head(&visited, serialize(left));
        }

        if(right.num_steps != visited_node.num_steps && !check(visited, right)){
            enqueue(&q, right);
            right.num_steps = 0;
            insert_at_head(&visited, serialize(right));
        }

        /*next_state = visited_node;

        move_up(&next_state);
        if(visited_node.empty_row != 3 && !check(&visited, next_state)){
            insert_at_head(&visited, mod_serialize(next_state));
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_down(&next_state);
        if(visited_node.empty_row != 0 && !check(&visited, next_state)){
            insert_at_head(&visited, mod_serialize(next_state));
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_left(&next_state);
        if(visited_node.empty_col != 3 && !check(&visited, next_state)){
            insert_at_head(&visited, mod_serialize(next_state));
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_right(&next_state);
        if(visited_node.empty_col != 3 && !check(&visited, next_state)){
            insert_at_head(&visited, mod_serialize(next_state));
            enqueue(&q, next_state);
        }*/

    }

    return 0; 
}
