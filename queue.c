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

int check(struct linked_list list, struct game_state state){
    struct list_node *temp = list.head;
    while(temp != NULL){
        int match = 1;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(deserialize(temp->value).tiles[i][j] != state.tiles[i][j]){
                    match = 0;
                    break;
                }
            }
        }

        if(match == 1){
            return 1;
        }

        temp = temp->next;
    }

    return 0;
}

int correct_state(struct game_state *state){
    size_t correct_state = 81985526993846272;
    uint16_t moves = state->num_steps;

    state->num_steps = 0;
    //if(state->empty_col == 3 && state->empty_row == 3){
        if(correct_state == serialize(*state)){
            state->num_steps = moves;
            return 1;
        }else {
            state->num_steps = moves;
            return 0;
        }
    //}else{
        return 0;
    //}
}

int number_of_moves(struct game_state start) { 
    struct queue q;
    q.data.head = NULL;
    struct linked_list visited;
    visited.head = NULL;

    enqueue(&q, start);

    struct game_state visited_node = start;
    struct game_state next_state;

    while(q.data.head != NULL){
        visited_node = dequeue(&q);
        
        if(correct_state(&visited_node)){
            free_list(q.data);
            free_list(visited);

            return visited_node.num_steps;
        }

        next_state = visited_node;

        move_up(&next_state);
        if(serialize(next_state) != serialize(visited_node) && !check(visited, next_state)){
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_down(&next_state);
        if(serialize(next_state) != serialize(visited_node) && !check(visited, next_state)){
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_left(&next_state);
        if(serialize(next_state) != serialize(visited_node) && !check(visited, next_state)){
            enqueue(&q, next_state);
        }
        next_state = visited_node;

        move_right(&next_state);
        if(serialize(next_state) != serialize(visited_node) && !check(visited, next_state)){
            enqueue(&q, next_state);
        }
        
        insert_at_head(&visited, serialize(visited_node));
    
    }

    return 0; 
}
