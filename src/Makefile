DIRETORIO = bin
FLAGS = -Wall -Wextra -Werror

# checando o sistema operacional
ifeq ($(OS),Windows_NT)                                     # windows
    MKDIR = if not exist $(DIRETORIO) mkdir $(DIRETORIO)
    RM = rmdir /S /Q $(DIRETORIO)
    EXE = $(DIRETORIO)/main.exe
    RUNCMD = .\\$(DIRETORIO)\\main.exe
else                                                        # linux ou mac 
    MKDIR = mkdir -p $(DIRETORIO)
    RM = rm -rf $(DIRETORIO)
    EXE = $(DIRETORIO)/main
    RUNCMD = ./$(DIRETORIO)/main
endif

# compilando o programa
all:
	$(MKDIR)
	g++ $(FLAGS) -o $(EXE) *.cpp 

# executando o programa
run:
	$(RUNCMD)

# limpando os arquivos
clean:
	$(RM)
