#ifndef TL_LINE_H
#define TL_LINE_H

class TLLine_t{
    public:
        uint64_t pc;
        uint64_t last_address;
        uint64_t stride;
        uint32_t confidence_counter;
        bool valid;

        TLLine_t(){
            this->pc = -1;
            this->last_address = -1;
            this->stride = -1;
            this->confidence_counter = -1;
            this->valid = false;
        }
};

#endif
