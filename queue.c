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

int check(struct linked_list *list, struct game_state state){
    struct list_node *temp = list->head;
    while(temp != NULL){
        if(mod_serialize(state) == temp->value){
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

int correct_state(struct game_state *state){
    size_t correct_state = 81985526993846272;
    if(mod_serialize(*state) ==  correct_state){
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
    insert_at_head(&visited, serialize(start));

    enqueue(&q, start);

    struct game_state visited_node = start;
    struct game_state next_state;

    while(q.data.head != NULL){
        iter++;
        visited_node = dequeue(&q);
        //printf("%ld ", mod_serialize(visited_node));
        
        if(correct_state(&visited_node)){
            free_list(q.data);
            free_list(visited);
            printf("%d\n", iter);

            return visited_node.num_steps;
        }

        next_state = visited_node;

        move_up(&next_state);
        if(!check(&visited, next_state)){
            enqueue(&q, next_state);
            insert_at_head(&visited, mod_serialize(next_state));
        }
        next_state = visited_node;

        move_left(&next_state);
        if(!check(&visited, next_state)){
            enqueue(&q, next_state);
            insert_at_head(&visited, mod_serialize(next_state));
        }
        next_state = visited_node;

        move_right(&next_state);
        if(!check(&visited, next_state)){
            enqueue(&q, next_state);
            insert_at_head(&visited, mod_serialize(next_state));
        }
        next_state = visited_node;

        move_down(&next_state);
        if(!check(&visited, next_state)){
            enqueue(&q, next_state);
            insert_at_head(&visited, mod_serialize(next_state));
        }

    }

    return 0; 
}
