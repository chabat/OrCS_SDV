#ifndef VRMT_LINE_H
#define VRMT_LINE_H

class VRMTLine_t{
    public:
        uint64_t pc;
        uint32_t offset;
        uint32_t srcOp1;
        uint32_t srcOp2;
        uint64_t value;
        bool valid;

        VRMTLine_t(){
            this->pc = -1;
            this->offset = -1;
            this->srcOp1 = -1;
            this->srcOp2 = -1;
            this->value = -1;
            this->valid = false;
        }
};

#endif
