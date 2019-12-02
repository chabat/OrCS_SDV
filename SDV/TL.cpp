#include "../simulator.hpp"

TL_t::TL_t(){
    this->sets = new TLSet_t[N_SETS];
}

int TL_t::tlFind(uint64_t pc){
    int i, set;
    //Calculate the set for that address
    set = pc & (this->N_SETS-1);
    //Iterate over the set lines searching for the pc
    for(i = 0; i < (int)this->N_WAYS; i++)
        if(this->sets[set].lines[i].valid == true && this->sets[set].lines[i].pc == pc)
            return i;
    //if not found
    return -1;
}

void TL_t::tlInsert(uint64_t pc, uint64_t last_address){
    int i, set, oldestPc_i;
    uint64_t oldestPc_v;

    //Calculate set
    set = pc & (this->N_SETS-1);

    //If there is no free lines, evict some entry (Oldest pc)
    if(this->sets[set].freeLines == 0){
        //Assume oldest pc is the first of the set
        oldestPc_v = this->sets[set].lines[0].pc;
        oldestPc_i = 0;
        //Check if any of the remaining pc's is older
        for(i = 1; i < (int)this->N_WAYS; i++)
            if(this->sets[set].lines[i].pc < oldestPc_v){
                oldestPc_v = this->sets[set].lines[i].pc;
                oldestPc_i = i;
            }
        //Evict the oldest pc
        this->sets[set].lines[oldestPc_i].valid = false;

        this->sets[set].freeLines++;
    }

    //Insert the new load on the first available line
    for(i = 0; i < (int)this->N_WAYS; i++)
        if(this->sets[set].lines[i].valid == false)
            break;
    this->sets[set].lines[i].pc = pc;
    this->sets[set].lines[i].last_address = last_address;
    this->sets[set].lines[i].stride = 0;
    this->sets[set].lines[i].confidence_counter = 0;
    this->sets[set].lines[i].valid = true;
    this->sets[set].freeLines--;
}

void TL_t::tlUpdate(uint32_t line, uint32_t readSize, uint64_t pc, uint64_t address){
    int set;
    TLLine_t *updated_line;
    uint64_t new_stride;

    //Calculate set
    set = pc & (this->N_SETS-1);
    //Obtain line to be updated
    updated_line = &(this->sets[set].lines[line]);

    //If the stride is negative, reset confidence counter and stride value
    if(address < updated_line->last_address){
        updated_line->confidence_counter = 0;
        updated_line->stride = 0;
    }
    else{
        //If is not, update confidence counter and stride, accordingly
        new_stride = address - updated_line->last_address;
        if(new_stride == updated_line->stride)
            updated_line->confidence_counter++;
        else{
            updated_line->confidence_counter = 0;
            updated_line->stride = new_stride;
        }
        //Add stride to the statistics
        printf("PC: %lu, NEW: %lu, OLD: %lu, Read size %d, STRIDE:%lu, confidence: %d\n", pc, address, updated_line->last_address, readSize, new_stride, updated_line->confidence_counter);
    }
    updated_line->last_address = address;
}
