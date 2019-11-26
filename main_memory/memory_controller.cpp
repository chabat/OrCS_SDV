#include "./../simulator.hpp"
#include <string>
// ============================================================================
memory_controller_t::memory_controller_t(){
    this->requests_made = 0; //Data Requests made
    this->operations_executed = 0; // number of operations executed
    this->requests_llc = 0; //Data Requests made to LLC
    this->requests_prefetcher = 0; //Data Requests made by prefetcher
    this->row_buffer_miss = 0; //Counter row buffer misses
    this->row_buffer_hit = 0;
}
// ============================================================================
memory_controller_t::~memory_controller_t(){
    delete[] this->channels;
}
// ============================================================================

// ============================================================================
// @allocate objects to EMC
void memory_controller_t::allocate(){
    libconfig::Setting &cfg_root = orcs_engine.configuration->getConfig();
    libconfig::Setting &cfg_memory_ctrl = cfg_root["MEMORY_CONTROLLER"];
    libconfig::Setting &cfg_processor = cfg_root["PROCESSOR"][0];
    
    set_DEBUG (cfg_processor["DEBUG"]);
    set_CHANNEL (cfg_memory_ctrl["CHANNEL"]);
    set_LINE_SIZE (cfg_memory_ctrl["LINE_SIZE"]);
    set_WAIT_CYCLE (cfg_memory_ctrl["WAIT_CYCLE"]);
    set_CORE_TO_BUS_CLOCK_RATIO (cfg_memory_ctrl["CORE_TO_BUS_CLOCK_RATIO"]);

    set_TIMING_AL (cfg_memory_ctrl["TIMING_AL"]);     // Added Latency for column accesses
    set_TIMING_CAS (cfg_memory_ctrl["TIMING_CAS"]);    // Column Access Strobe (CL]) latency
    set_TIMING_CCD (cfg_memory_ctrl["TIMING_CCD"]);    // Column to Column Delay
    set_TIMING_CWD (cfg_memory_ctrl["TIMING_CWD"]);    // Column Write Delay (CWL]) or simply WL
    set_TIMING_FAW (cfg_memory_ctrl["TIMING_FAW"]);   // Four (row]) Activation Window
    set_TIMING_RAS (cfg_memory_ctrl["TIMING_RAS"]);   // Row Access Strobe
    set_TIMING_RC (cfg_memory_ctrl["TIMING_RC"]);    // Row Cycle
    set_TIMING_RCD (cfg_memory_ctrl["TIMING_RCD"]);    // Row to Column comand Delay
    set_TIMING_RP (cfg_memory_ctrl["TIMING_RP"]);     // Row Precharge
    set_TIMING_RRD (cfg_memory_ctrl["TIMING_RRD"]);    // Row activation to Row activation Delay
    set_TIMING_RTP (cfg_memory_ctrl["TIMING_RTP"]);    // Read To Precharge
    set_TIMING_WR (cfg_memory_ctrl["TIMING_WR"]);    // Write Recovery time
    set_TIMING_WTR (cfg_memory_ctrl["TIMING_WTR"]);
    
    this->channels = new memory_channel_t[CHANNEL];
    for (size_t i = 0; i < CHANNEL; i++){
        channels[i].set_TIMING_AL (ceil (this->TIMING_AL * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_CAS (ceil (this->TIMING_CAS * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_CCD (ceil (this->TIMING_CCD * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_CWD (ceil (this->TIMING_CWD * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_FAW (ceil (this->TIMING_FAW * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_RAS (ceil (this->TIMING_RAS * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_RC (ceil (this->TIMING_RC * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_RCD (ceil (this->TIMING_RCD * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_RP (ceil (this->TIMING_RP * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_RRD (ceil (this->TIMING_RRD * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_RTP (ceil (this->TIMING_RTP * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_WR (ceil (this->TIMING_WR * this->CORE_TO_BUS_CLOCK_RATIO));
        channels[i].set_TIMING_WTR (ceil (this->TIMING_WTR * this->CORE_TO_BUS_CLOCK_RATIO));
    }
    
    this->set_masks();
}
// ============================================================================
void memory_controller_t::statistics(){
    FILE *output = stdout;
    bool close = false;

    if(orcs_engine.output_file_name != NULL){
        close=true;
		output = fopen(orcs_engine.output_file_name,"a+");
    }
	if (output != NULL){
        utils_t::largestSeparator(output);
        fprintf(output,"#Memory Controller\n");
        utils_t::largestSeparator(output);
        fprintf(output,"Requests_Made:              %lu\n",this->get_requests_made());
        fprintf(output,"Requests_from_Prefetcher:   %lu\n",this->get_requests_prefetcher());
        fprintf(output,"Requests_from_LLC:          %lu\n",this->get_requests_llc());
        fprintf(output,"Requests_from_HIVE:         %lu\n",this->get_requests_hive());
        for (uint32_t i = 0; i < CHANNEL; i++){
            fprintf(output,"Row_Buffer_Hit, Channel %u:  %lu\n",i,this->channels[i].get_stat_row_buffer_hit());
            fprintf(output,"Row_Buffer_Miss, Channel %u: %lu\n",i,this->channels[i].get_stat_row_buffer_miss());
        }
        utils_t::largestSeparator(output);
        if(close) fclose(output);
    }
}
// ============================================================================
void memory_controller_t::clock(){
    for (uint32_t i = 0; i < this->CHANNEL; i++) this->channels[i].clock();
}
// ============================================================================
void memory_controller_t::set_masks(){
        
    ERROR_ASSERT_PRINTF(CHANNEL > 1 && utils_t::check_if_power_of_two(CHANNEL),"Wrong number of memory_channels (%u).\n",CHANNEL);
    uint64_t i;
    // =======================================================
    // Setting to zero
    // =======================================================
    this->channel_bits_shift = 0;
    this->channel_bits_mask = 0;
    // =======================================================
    this->channel_bits_shift = utils_t::get_power_of_two(LINE_SIZE);
    
    /// CHANNEL MASK
    for (i = 0; i < utils_t::get_power_of_two(CHANNEL); i++) {
        this->channel_bits_mask |= 1 << (i + this->channel_bits_shift);
    }
}
//=====================================================================
uint64_t memory_controller_t::requestDRAM (memory_package_t* request, uint64_t address){
    this->add_requests_made();
    if (request->is_hive) {
        request->printPackage();
        this->add_requests_hive();
    }
    if (request != NULL) {
        this->channels[get_channel (address)].addRequest (request);
        if (DEBUG) ORCS_PRINTF ("Memory Controller requestDRAM(): receiving memory request from uop %lu, %s.\n", request->uop_number, get_enum_memory_operation_char (request->memory_operation))
        return 0;
    }
    return 0;
}