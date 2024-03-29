SRCS		= affichage.cpp balle.cpp coup.cpp format.cpp joueur.cpp main.cpp \
	score.cpp terrain.cpp texte.cpp vec2.cpp boundingbox.cpp
HEADERS		= src/includes
CXX			= g++
CXX_FLAGS	= -Wall -Werror -Wextra -g
LD_FLAGS	= -lSDL2 -lSDL2_ttf -lSDL2_image

OBJ_DIR = obj
BIN_DIR = bin
SRC_DIR = src

BUILD_NAME = ting-tong
OBJS = ${SRCS:%.cpp=$(OBJ_DIR)/%.o}
DEP = $(OBJS:%.o=%.d)

all: mkdir ${BUILD_NAME}

# affichage builds bin/affichage, and it's the same for all the others

ting-tong: ${BIN_DIR}/${BUILD_NAME}
${BIN_DIR}/${BUILD_NAME}: ${OBJS} # Build for affichage
	${CXX} ${CXX_FLAGS} -o $@ $^ ${LD_FLAGS} 

-include $(DEP)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	${CXX} ${CXX_FLAGS} -MMD -c $< -o $@ -I${HEADERS}

mkdir:
	mkdir -p $(BIN_DIR) $(OBJ_DIR)

clean: fclean
	rm -f ${BIN_DIR}/${BUILD_NAME}

fclean: # fclean only removes the .o files, while clean removes the .o AND the binaries
	rm -f ${OBJS} ${DEP}

re: fclean all

.PHONY: fclean clean all re mkdir
