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

int check(struct linked_list list, size_t value){
    struct list_node *temp = list.head;
    while(temp != NULL){
        if(temp->value == value){
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

int correct_state(struct game_state *state){
    size_t correct_state = 81985526993846272;
    uint16_t moves = state->num_steps;

    state->num_steps  = 0;

    if(correct_state == serialize(*state)){
        state->num_steps = moves;
        return 1;
    }else {
        state->num_steps = moves;
        return 0;
    }
}

int number_of_moves(struct game_state start) { 
    struct queue q;
    q.data.head = NULL;
    struct linked_list visited;

    enqueue(&q, start);

    struct game_state visited_node = start;
    struct game_state next_state;
    size_t next_value;

    while(q.data.head != NULL){
        visited_node = dequeue(&q);
        
        if(correct_state(&visited_node)){
            return visited_node.num_steps;
        }

        next_state = visited_node;

        move_up(&next_state);
        next_value = serialize(next_state);
        if(next_value != serialize(visited_node) && !check(visited, next_value)){
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_down(&next_state);
        next_value = serialize(next_state);
        if(next_value != serialize(visited_node) && !check(visited, next_value)){
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_left(&next_state);
        next_value = serialize(next_state);
        if(next_value != serialize(visited_node) && !check(visited, next_value)){
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_right(&next_state);
        next_value = serialize(next_state);
        if(next_value != serialize(visited_node) && !check(visited, next_value)){
            enqueue(&q, next_state);
        }
        
        insert_at_head(&visited, serialize(visited_node));
    
    }

    return 0; 
}
