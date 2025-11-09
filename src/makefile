DIRETORIO = bin

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist $(DIRETORIO) mkdir $(DIRETORIO)
    RM = rmdir /S /Q $(DIRETORIO)
    RUNCMD = .\\$(DIRETORIO)\\main.exe
    EXE = $(DIRETORIO)/main.exe
else
    MKDIR = mkdir -p $(DIRETORIO)
    RM = rm -rf $(DIRETORIO)
    RUNCMD = ./$(DIRETORIO)/main.exe
    EXE = $(DIRETORIO)/main.exe
endif

all:
	$(MKDIR)
	g++ -o $(EXE) *.cpp

run:
	$(RUNCMD)

clean:
	$(RM)
