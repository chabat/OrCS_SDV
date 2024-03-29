CC = gcc
CPP = g++
LD = g++
CFLAGS = $(FLAGS)
CPPFLAGS = $(FLAGS)
BIN_NAME = orcs
RM = rm -f

FLAGS =   -ggdb3 -g -Wall -Wextra -Werror -std=c++0x -lefence -O3 -pedantic
LDFLAGS = -ggdb3
########################################################################
##FOLDERS
FD_PACKAGE = package
FD_PROCESSOR = processor
FD_BRANCH_PREDICTOR = branch_predictor
FD_OTHER = utils
FD_CACHE = cache
FD_DIRECTORY = directory
FD_PREFETCHER = prefetcher
FD_MEMORY = main_memory
FD_HIVE = hive
FD_EMC = emc
FD_CONFIG = config
FD_DISAMBIGUATION = memory_disambiguation
FD_SDV = SDV

###
LIBRARY = -lz -lconfig++

SRC_PACKAGE = 		$(FD_PACKAGE)/opcode_package.cpp\
					$(FD_PACKAGE)/uop_package.cpp\
					$(FD_PACKAGE)/memory_package.cpp

SRC_TRACE_READER = 	trace_reader.cpp

SRC_MEMORY_DISAMBIGUATION = $(FD_PROCESSOR)/$(FD_DISAMBIGUATION)/disambiguation_hashed.cpp

SRC_PROCESSOR =		$(FD_PROCESSOR)/processor.cpp\
					$(FD_PROCESSOR)/reorder_buffer_line.cpp\
					$(FD_PROCESSOR)/memory_order_buffer_line.cpp\

SRC_BRANCH_PREDICTOR =	$(FD_BRANCH_PREDICTOR)/branch_predictor.cpp\
						$(FD_BRANCH_PREDICTOR)/piecewise.cpp
SRC_CACHE = $(FD_CACHE)/cache.cpp\
			$(FD_CACHE)/cache_manager.cpp\
			$(FD_CACHE)/mshr_entry.cpp

SRC_DIRECTORY = $(FD_DIRECTORY)/directory.cpp

SRC_OTHER = $(FD_OTHER)/utils.cpp\
			$(FD_OTHER)/enumerations.cpp

SRC_PREFETCHER = $(FD_PREFETCHER)/prefetcher.cpp\
				 $(FD_PREFETCHER)/stride_prefetcher.cpp

SRC_MEMORY = $(FD_MEMORY)/memory_channel.cpp\
			 $(FD_MEMORY)/memory_controller.cpp\
			 $(FD_MEMORY)/memory_request_client.cpp

SRC_HIVE = $(FD_HIVE)/hive_controller.cpp\
		   $(FD_HIVE)/hive_register.cpp

SRC_CONFIG = $(FD_CONFIG)/config.cpp

SRC_SDV = $(FD_SDV)/TL.cpp\
		  $(FD_SDV)/VRMT.cpp	

SRC_CORE =  simulator.cpp orcs_engine.cpp\
			$(SRC_TRACE_READER)\
			$(SRC_PACKAGE)\
			$(SRC_MEMORY_DISAMBIGUATION)\
			$(SRC_PROCESSOR)\
			$(SRC_OTHER)\
			$(SRC_BRANCH_PREDICTOR)\
			$(SRC_CACHE)\
			$(SRC_HIVE)\
			$(SRC_DIRECTORY)\
			$(SRC_PREFETCHER)\
			$(SRC_CONFIG)\
			$(SRC_MEMORY)\
			$(SRC_EMC)\
			$(SRC_SDV)\

########################################################
OBJS_CORE = ${SRC_CORE:.cpp=.o}
OBJS = $(OBJS_CORE)
########################################################
# implicit rules
%.o : %.cpp %.hpp
	$(CPP) -c $(CPPFLAGS) $< -o $@

########################################################

all: orcs

orcs: $(OBJS_CORE)
	$(LD) $(LDFLAGS) -o $(BIN_NAME) $(OBJS) $(LIBRARY)

clean:
	-$(RM) $(OBJS)
	-$(RM) $(BIN_NAME)
	@echo OrCS cleaned!
	@echo
